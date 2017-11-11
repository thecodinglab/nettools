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
#include <iostream>

namespace nettools
{
    static sock_t discovery_socket;

    void discovery_init(u16 port) { discovery_socket = socket_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP); }
    void discovery_close() { socket_close(discovery_socket); }

    void discovery_search()
    {
        network_interface iface = interface_query();
        inet_address broadcast = iface.m_broadcast_addr;

        broadcast.print();

        socket_address address;
        address.m_addr = iface.m_unicast_addr;
        address.m_port = 12345;

        socket_address multicast_address;
        multicast_address.m_addr = broadcast;
        multicast_address.m_port = 12346;

        sock_t socket = socket_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        socket_bind(socket, &address);
        socket_configure_broadcast(socket, true);

        byte_buffer packet(1024);
        packet.put_i32(1234);
        packet.flip();

        socket_sendto(socket, &packet, &multicast_address);

        std::cout << "SEND" << std::endl;

        packet.reset();
        socket_address sender;
        socket_readfrom(socket, &packet, &sender);
        packet.flip();

        std::cout << packet.get_i32() << std::endl;

        socket_close(socket);
    }
}
