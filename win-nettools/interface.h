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
#include "socket.h"
#include <Iphlpapi.h>

namespace nettools
{
    struct network_interface
    {
        inet_address m_unicast_addr;
        inet_address m_multicast_addr;
        inet_address m_dns_server_addr;
        inet_address m_gateway_addr;
        u8 m_subnet_prefix;
    };

    NETTOOLS_EXPORT network_interface interface_query();
}