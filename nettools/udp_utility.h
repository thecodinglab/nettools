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
#include "socket.h"
#include "interface.h"

namespace nettools
{
    NETTOOLS_EXPORT void socket_udp_broadcast_method_allatonce(sock_t, byte_buffer *, network_interface *, u16);
    NETTOOLS_EXPORT void socket_udp_broadcast_method_oneatime(sock_t, byte_buffer *, network_interface *, u16);
}