/*
* nettols is a library for comonly used network stuff for windows and linux
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
#include <nettools/udp_socket.h>
#include <iostream>
#include <cstring>

int main()
{
    nettools::network_interface iface = nettools::interface_query();
    nettools::udp_sock_t socket = nettools::socket_udp_create(&iface, 1234);

    nettools::socket_address addr;
    addr.m_addr.m_address = iface.m_unicast_addr.m_address;
    //addr.m_addr.m_address = iface.m_network_addr.m_address + 1;
    addr.m_port = 1234;

    u32 data_len = 1024;
    u8 *data = new u8[data_len];
    memset(data, 0, data_len);

    nettools::sock_sequence_t sequence = nettools::socket_udp_sequence_new(socket, &addr);
    nettools::socket_udp_sequence_attach(socket, sequence, data, data_len);
    nettools::socket_udp_sequence_attach(socket, sequence, data, data_len);
    nettools::socket_udp_sequence_end(sequence);

    while (1) {
        nettools::socket_udp_update(socket);
    }
}