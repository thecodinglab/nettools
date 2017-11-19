/*
* win-nettols is a library for comonly used network stuff for windows
* Copyright (C) 2017  TheCodingLab
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "discovery.h"
#include <chrono>
#include <map>

#define DISCOVERY_ID            0xe3f7
#define DISCOVERY_VERSION       0x0102
#define DISCOVERY_TYPE_REQUEST  0x0001
#define DISCOVERY_TYPE_ANSWER   0x0002
#define DISCOVERY_TYPE_PING     0x0003

#define DISCOVERY_PING_DURATION 5000

namespace nettools
{
    static byte_buffer discovery_read_buffer = byte_buffer(6);
    static byte_buffer discovery_write_buffer = byte_buffer(6);

    static sock_t discovery_socket = 0;
    static network_interface discovery_iface;
    static callback_discovery_request discovery_request = NULL;
    static callback_discovery_found discovery_found = NULL;
    static callback_discovery_ping_result discovery_ping_result = NULL;

#ifdef _WIN32
    static std::map<socket_address, std::chrono::time_point<std::chrono::steady_clock>> discovery_ping_table;
#else
    static std::map<socket_address, std::chrono::system_clock::time_point> discovery_ping_table;
#endif

    void discovery_init(u16 port)
    {
        if (discovery_socket != 0) return;

        discovery_socket = socket_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        discovery_iface = interface_query();

        socket_address addr;
        addr.m_addr = discovery_iface.m_unicast_addr;
        addr.m_port = port;
        socket_bind(discovery_socket, &addr);

        socket_configure_blocking(discovery_socket, false);
        socket_configure_broadcast(discovery_socket, true);
    }

    void discovery_set_handlers(callback_discovery_request cdr, callback_discovery_found cdf, callback_discovery_ping_result cdpr)
    {
        discovery_request = cdr;
        discovery_found = cdf;
        discovery_ping_result = cdpr;
    }

    void discovery_search(u16 port, bool allatonce)
    {
        socket_configure_blocking(discovery_socket, true);

        discovery_write_buffer.reset();
        discovery_write_buffer.put_i16(DISCOVERY_ID);
        discovery_write_buffer.put_i16(DISCOVERY_VERSION);
        discovery_write_buffer.put_i16(DISCOVERY_TYPE_REQUEST);
        discovery_write_buffer.flip();

        if (allatonce) socket_udp_broadcast_method_allatonce(discovery_socket, &discovery_write_buffer, &discovery_iface, port);
        else socket_udp_broadcast_method_oneatime(discovery_socket, &discovery_write_buffer, &discovery_iface, port);

        socket_configure_blocking(discovery_socket, false);
    }

    void discovery_update()
    {
        socket_address client;
        discovery_read_buffer.reset();
        i32 read = socket_readfrom(discovery_socket, &discovery_read_buffer, &client);

        if (read > 0)
        {
            discovery_read_buffer.flip();

            u16 id = discovery_read_buffer.get_u16();
            if (id == DISCOVERY_ID)
            {
                u16 version = discovery_read_buffer.get_u16();
                if (version == DISCOVERY_VERSION)
                {
                    u16 type = discovery_read_buffer.get_u16();
                    if (type == DISCOVERY_TYPE_REQUEST)
                    {
                        if (discovery_request == NULL || discovery_request(&client))
                        {
                            discovery_write_buffer.reset();
                            discovery_write_buffer.put_i16(DISCOVERY_ID);
                            discovery_write_buffer.put_i16(DISCOVERY_VERSION);
                            discovery_write_buffer.put_i16(DISCOVERY_TYPE_ANSWER);
                            discovery_write_buffer.flip();

                            socket_sendto(discovery_socket, &discovery_write_buffer, &client);

                            if (discovery_found != NULL) discovery_found(&client);
                        }
                    } else if (type == DISCOVERY_TYPE_ANSWER)
                    {
                        if (discovery_found != NULL) discovery_found(&client);
                    } else if (type == DISCOVERY_TYPE_PING)
                    {
                        auto received = std::chrono::high_resolution_clock::now();
                        auto itr = discovery_ping_table.find(client);
                        if (itr == discovery_ping_table.end())
                        {
                            discovery_write_buffer.reset();
                            discovery_write_buffer.put_i16(DISCOVERY_ID);
                            discovery_write_buffer.put_i16(DISCOVERY_VERSION);
                            discovery_write_buffer.put_i16(DISCOVERY_TYPE_PING);
                            discovery_write_buffer.flip();

                            socket_sendto(discovery_socket, &discovery_write_buffer, &client);
                        } else
                        {
                            auto send = itr->second;
                            if (discovery_ping_result)
                            {
                                u32 needed = static_cast<u32>(std::chrono::duration_cast<std::chrono::milliseconds>(received.time_since_epoch() - send.time_since_epoch()).count());
                                discovery_ping_result(&client, needed, true);
                            }
                            discovery_ping_table.erase(itr);
                        }
                    }
                }
            }
        }

        auto now = std::chrono::high_resolution_clock::now();
        auto itr = discovery_ping_table.begin();
        while (itr != discovery_ping_table.end())
        {
            socket_address addr = itr->first;
            auto send = itr->second;

            if ((now.time_since_epoch() - send.time_since_epoch()) > std::chrono::milliseconds(DISCOVERY_PING_DURATION))
            {
                if (discovery_ping_result) discovery_ping_result(&addr, 0, false);
                itr = discovery_ping_table.erase(itr);
            } else ++itr;
        }
    }

    void discovery_ping(socket_address *addr)
    {
        discovery_write_buffer.reset();
        discovery_write_buffer.put_i16(DISCOVERY_ID);
        discovery_write_buffer.put_i16(DISCOVERY_VERSION);
        discovery_write_buffer.put_i16(DISCOVERY_TYPE_PING);
        discovery_write_buffer.flip();

        socket_sendto(discovery_socket, &discovery_write_buffer, addr);
        discovery_ping_table[*addr] = std::chrono::high_resolution_clock::now();
    }

    void discovery_close()
    {
        socket_close(discovery_socket);
        discovery_socket = 0;
    }
}
