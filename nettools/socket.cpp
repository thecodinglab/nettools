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
#include "socket.h"
#include "udp_utility.h"
#include <sstream>

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

    sock_t socket_create(const int af, const int type, const int protocol)
    {
        return socket(af, type, protocol);
    }

    void socket_bind(const sock_t socket, const socket_address_ptr address)
    {
        sockaddr_in addr;
        addr.sin_port = htons(address->m_port);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = address->m_addr.m_address;
        bind(socket, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
    }

    sock_t socket_accept(const sock_t socket, const socket_address_ptr address)
    {
        sockaddr_in addr;
#ifdef _WIN32
        i32 addr_size = sizeof(sockaddr_in);
        const sock_t client = accept(socket, reinterpret_cast<sockaddr *>(&addr), &addr_size);
#else
        u32 addr_size = sizeof(sockaddr_in);
        sock_t client = accept(socket, reinterpret_cast<sockaddr *>(&addr), &addr_size);
#endif

        if (addr_size != sizeof(sockaddr_in)) throw std::runtime_error("Invalid address size.");

        address->m_port = ntohs(addr.sin_port);
        address->m_addr.m_address = addr.sin_addr.s_addr;
        return client;
    }

    void socket_connect(const sock_t socket, const socket_address_ptr address)
    {
        sockaddr_in addr;
        addr.sin_port = htons(address->m_port);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = address->m_addr.m_address;
        connect(socket, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
    }

    void socket_listen(const sock_t socket)
    {
        listen(socket, SOMAXCONN);
    }

    void socket_send(const sock_t socket, const byte_buffer_ptr buffer)
    {
        send(socket, reinterpret_cast<const char *>(buffer->get_buffer_at_offset()), buffer->get_limit(), 0);
    }

    i32 socket_read(const sock_t socket, byte_buffer_ptr buffer)
    {
        const size_t position = buffer->get_offset();
        const i32 read = recv(socket, reinterpret_cast<char *>(buffer->get_buffer_at_offset()), buffer->get_limit(), 0);
        if (read > 0) buffer->set_offset(position + read);
        return read;
    }

    void socket_sendto(const sock_t socket, const byte_buffer_ptr buffer, const socket_address_ptr address)
    {
        sockaddr_in addr;
        addr.sin_port = htons(address->m_port);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = address->m_addr.m_address;
        sendto(socket, reinterpret_cast<const char *>(buffer->get_buffer_at_offset()), buffer->get_limit(), 0, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
    }

    i32 socket_readfrom(const sock_t socket, byte_buffer_ptr buffer, const socket_address_ptr address)
    {
        sockaddr_in addr;
        const size_t position = buffer->get_offset();

#ifdef _WIN32
        i32 addr_size = sizeof(sockaddr_in);
        const i32 read = recvfrom(socket, reinterpret_cast<char *>(buffer->get_buffer_at_offset()), buffer->get_limit(), 0, reinterpret_cast<sockaddr *>(&addr), &addr_size);
#else
        u32 addr_size = sizeof(sockaddr_in);
        i32 read = recvfrom(socket, reinterpret_cast<char *>(buffer->get_buffer_at_offset()), buffer->get_limit(), 0, reinterpret_cast<sockaddr *>(&addr), &addr_size);
#endif

        if (addr_size != sizeof(sockaddr_in)) throw std::runtime_error("Invalid address size.");

        address->m_port = ntohs(addr.sin_port);
        address->m_addr.m_address = addr.sin_addr.s_addr;

        if (read > 0) buffer->set_offset(position + read);
        return read;
    }

    void socket_close(const sock_t socket)
    {
#ifdef _WIN32
        closesocket(socket);
#else
        close(socket);
#endif
    }

    void socket_configure_blocking(const sock_t socket, const bool blocking)
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

    void socket_configure_broadcast(const sock_t socket, const bool broadcast)
    {
        setsockopt(socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&broadcast), sizeof(bool));
    }

    void socket_configure_send_timeout(const sock_t socket, const size_t timeout)
    {
        setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(size_t));
    }

    void socket_configure_read_timeout(const sock_t socket, const size_t timeout)
    {
        setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(size_t));
    }

    void socket_udp_broadcast_method_allatonce(const sock_t socket, const byte_buffer_ptr data, const network_interface_ptr iface, const u16 port)
    {
        socket_address addr;
        addr.m_addr = iface->m_broadcast_addr;
        addr.m_port = port;
        socket_sendto(socket, data, &addr);
    }

    void socket_udp_broadcast_method_oneatime(const sock_t socket, const byte_buffer_ptr data, const network_interface_ptr iface, const u16 port)
    {
        socket_address addr;
        addr.m_addr = iface->m_network_addr;
        addr.m_addr.m_b4++;
        addr.m_port = port;

        u32 address = ntohl(addr.m_addr.m_address);
        while (addr.m_addr.m_address != iface->m_broadcast_addr.m_address)
        {
            socket_sendto(socket, data, &addr);
            addr.m_addr.m_address = htonl(++address);
            if (addr.m_addr.m_address == iface->m_unicast_addr.m_address) addr.m_addr.m_address = htonl(++address);
        }
    }
}