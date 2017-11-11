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
#pragma once

#include "defines.h"
#include "buffer.h"
#include <WinSock2.h>
#include <iostream>

namespace nettools
{
    typedef SOCKET sock_t;

    struct inet_address
    {
        union
        {
            u32 m_address;
            struct
            {
                u8 m_b1;
                u8 m_b2;
                u8 m_b3;
                u8 m_b4;
            };
        };

        void print()
        {
            std::cout << (m_b1 & 0xff) << "." << (m_b2 & 0xff) << "." << (m_b3 & 0xff) << "." << (m_b4 & 0xff) << std::endl;
        }
    };

    struct socket_address
    {
        inet_address m_addr;
        u16 m_port;
    };

    NETTOOLS_EXPORT void socket_init();
    NETTOOLS_EXPORT void socket_cleanup();

    NETTOOLS_EXPORT sock_t socket_create(int, int, int);
    NETTOOLS_EXPORT void socket_bind(sock_t, socket_address*);
    NETTOOLS_EXPORT void socket_connect(sock_t, socket_address*);
    NETTOOLS_EXPORT void socket_listen(sock_t);
    NETTOOLS_EXPORT sock_t socket_accept(sock_t, socket_address*);
    NETTOOLS_EXPORT void socket_send(sock_t, byte_buffer*);
    NETTOOLS_EXPORT i32 socket_read(sock_t, byte_buffer*);
    NETTOOLS_EXPORT void socket_sendto(sock_t, byte_buffer*, socket_address*);
    NETTOOLS_EXPORT i32 socket_readfrom(sock_t, byte_buffer*, socket_address*);
    NETTOOLS_EXPORT void socket_close(sock_t);

    NETTOOLS_EXPORT void socket_configure_blocking(sock_t, bool);
    NETTOOLS_EXPORT void socket_configure_broadcast(sock_t, bool);
    NETTOOLS_EXPORT void socket_configure_send_timeout(sock_t, size_t);
    NETTOOLS_EXPORT void socket_configure_read_timeout(sock_t, size_t);
}
