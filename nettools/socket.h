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
#pragma once

#include "defines.h"
#include "buffer.h"
#include <sstream>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <fcntl.h>
#endif

namespace nettools
{
#ifdef _WIN32
    typedef SOCKET sock_t;
#else
    typedef int sock_t;
#endif

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

        std::string to_string() const
        {
            std::ostringstream stream;
            stream << (m_b1 & 0xff) << '.';
            stream << (m_b2 & 0xff) << '.';
            stream << (m_b3 & 0xff) << '.';
            stream << (m_b4 & 0xff);
            return stream.str();
        }
    };

    struct hardware_address
    {
        union
        {
            u8 m_address[6];
            struct
            {
                u8 m_b1;
                u8 m_b2;
                u8 m_b3;
                u8 m_b4;
                u8 m_b5;
                u8 m_b6;
            };
        };

        std::string to_string() const
        {
            std::ostringstream stream;
            stream << std::hex << (m_b1 & 0xff) << ':';
            stream << std::hex << (m_b2 & 0xff) << ':';
            stream << std::hex << (m_b3 & 0xff) << ':';
            stream << std::hex << (m_b4 & 0xff) << ':';
            stream << std::hex << (m_b5 & 0xff) << ':';
            stream << std::hex << (m_b6 & 0xff);
            return stream.str();
        }
    };

    struct socket_address
    {
        inet_address m_addr;
        u16 m_port;

        std::string to_string() const
        {
            std::ostringstream stream;
            stream << m_addr.to_string() << ':' << m_port;
            return stream.str();
        }

        bool operator<(const socket_address &other) const
        {
            if (m_addr.m_address == other.m_addr.m_address) return m_port < other.m_port;
            return m_addr.m_address < other.m_addr.m_address;
        }

        bool operator>(const socket_address &other) const
        {
            if (m_addr.m_address == other.m_addr.m_address) return m_port > other.m_port;
            return m_addr.m_address > other.m_addr.m_address;
        }
    };

    typedef inet_address *inet_address_t;
    typedef hardware_address *hardware_address_t;
    typedef socket_address *socket_address_t;

    NETTOOLS_EXPORT void socket_init();
    NETTOOLS_EXPORT void socket_cleanup();

    NETTOOLS_EXPORT sock_t socket_create(int, int, int);
    NETTOOLS_EXPORT void socket_bind(sock_t, socket_address_t);
    NETTOOLS_EXPORT void socket_connect(sock_t, socket_address_t);
    NETTOOLS_EXPORT void socket_listen(sock_t);
    NETTOOLS_EXPORT sock_t socket_accept(sock_t, socket_address_t);
    NETTOOLS_EXPORT void socket_send(sock_t, const byte_buffer_t);
    NETTOOLS_EXPORT i32 socket_read(sock_t, byte_buffer_t);
    NETTOOLS_EXPORT void socket_sendto(sock_t, const byte_buffer_t, socket_address_t);
    NETTOOLS_EXPORT i32 socket_readfrom(sock_t, byte_buffer_t, socket_address_t);
    NETTOOLS_EXPORT void socket_close(sock_t);

    NETTOOLS_EXPORT void socket_configure_blocking(sock_t, bool);
    NETTOOLS_EXPORT void socket_configure_broadcast(sock_t, bool);
    NETTOOLS_EXPORT void socket_configure_send_timeout(sock_t, size_t);
    NETTOOLS_EXPORT void socket_configure_read_timeout(sock_t, size_t);
}
