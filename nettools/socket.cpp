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
#include "socket.h"
#include "udp_utility.h"

namespace nettools
{
#ifdef _WIN32
    WSADATA wsadata;
#endif

    void socket_init()
    {
#ifdef _WIN32
        if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
        {
            fprintf(stderr, "ERROR: WSAStartup failed");
            exit(1);
        }
#endif
    }

    void socket_cleanup()
    {
#ifdef _WIN32
        WSACleanup();
#endif
    }

    sock_t socket_create(int af, int type, int protocol)
    { return socket(af, type, protocol); }

    void socket_bind(sock_t socket, socket_address *address)
    {
        sockaddr_in addr;
        addr.sin_port = htons(address->m_port);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = address->m_addr.m_address;
        bind(socket, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
    }

    sock_t socket_accept(sock_t socket, socket_address *address)
    {
        sockaddr_in addr;
        u32 addr_size = sizeof(sockaddr_in);
        sock_t client = accept(socket, reinterpret_cast<sockaddr *>(&addr), &addr_size);

        if (addr_size != sizeof(sockaddr_in)) throw std::runtime_error("Invalid address size.");

        address->m_port = ntohs(addr.sin_port);
        address->m_addr.m_address = addr.sin_addr.s_addr;
        return client;
    }

    void socket_connect(sock_t socket, socket_address *address)
    {
        sockaddr_in addr;
        addr.sin_port = htons(address->m_port);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = address->m_addr.m_address;
        connect(socket, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
    }

    void socket_listen(sock_t socket)
    { listen(socket, SOMAXCONN); }

    void socket_send(sock_t socket, byte_buffer *buffer)
    { send(socket, reinterpret_cast<const char *>(buffer->get_const_buffer_at_offset()), buffer->get_limit(), 0); }

    i32 socket_read(sock_t socket, byte_buffer *buffer)
    {
        size_t position = buffer->get_offset();
        i32 read = recv(socket, reinterpret_cast<char *>(buffer->get_buffer_at_offset()), buffer->get_limit(), 0);
        if (read > 0) buffer->set_offset(position + read);
        return read;
    }

    void socket_sendto(sock_t socket, byte_buffer *buffer, socket_address *address)
    {
        sockaddr_in addr;
        addr.sin_port = htons(address->m_port);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = address->m_addr.m_address;
        sendto(socket, reinterpret_cast<const char *>(buffer->get_const_buffer_at_offset()), buffer->get_limit(), 0, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
    }

    i32 socket_readfrom(sock_t socket, byte_buffer *buffer, socket_address *address)
    {
        sockaddr_in addr;
        u32 addr_size = sizeof(sockaddr_in);

        size_t position = buffer->get_offset();
        i32 read = recvfrom(socket, reinterpret_cast<char *>(buffer->get_buffer_at_offset()), buffer->get_limit(), 0, reinterpret_cast<sockaddr *>(&addr), &addr_size);

        if (addr_size != sizeof(sockaddr_in)) throw std::runtime_error("Invalid address size.");

        address->m_port = ntohs(addr.sin_port);
        address->m_addr.m_address = addr.sin_addr.s_addr;

        if (read > 0) buffer->set_offset(position + read);
        return read;
    }

    void socket_close(sock_t socket)
    {
#ifdef _WIN32
        closesocket(socket);
#else
        close(socket);
#endif
    }

    void socket_configure_blocking(sock_t socket, bool blocking)
    {
#ifdef _WIN32
        u32 inonblock = blocking ? 0 : 1;
        ioctlsocket(socket, FIONBIO, reinterpret_cast<u_long *>(&inonblock));
#else
        int flags = fcntl(socket, F_GETFL) & ~(O_NONBLOCK);
        if (!blocking) flags |= O_NONBLOCK;
        fcntl(socket, F_SETFL, flags);
#endif
    }

    void socket_configure_broadcast(sock_t socket, bool broadcast)
    {
        setsockopt(socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&broadcast), sizeof(bool));
    }

    void socket_configure_send_timeout(sock_t socket, size_t timeout)
    {
        setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(size_t));
    }

    void socket_configure_read_timeout(sock_t socket, size_t timeout)
    {
        setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(size_t));
    }

    void socket_udp_broadcast_method_allatonce(sock_t socket, byte_buffer *data, network_interface *iface, u16 port)
    {
        socket_address addr;
        addr.m_addr = iface->m_broadcast_addr;
        addr.m_port = port;
        socket_sendto(socket, data, &addr);
    }

    void socket_udp_broadcast_method_oneatime(sock_t socket, byte_buffer *data, network_interface *iface, u16 port)
    {
        socket_address addr;
        addr.m_addr = iface->m_network_addr;
        addr.m_addr.m_b4++;
        addr.m_port = port;

        while (addr.m_addr.m_address != iface->m_broadcast_addr.m_address)
        {
            socket_sendto(socket, data, &addr);

            addr.m_addr.m_b4++;
            if (addr.m_addr.m_b4 == 0)
            {
                addr.m_addr.m_b3++;
                if (addr.m_addr.m_b3 == 0)
                {
                    addr.m_addr.m_b2++;
                    if (addr.m_addr.m_b2 == 0)
                    {
                        addr.m_addr.m_b1++;
                        if (addr.m_addr.m_b1 == 0)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}