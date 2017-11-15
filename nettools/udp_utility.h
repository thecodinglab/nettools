
#pragma once

#include "defines.h"
#include "socket.h"
#include "interface.h"

namespace nettools
{
    NETTOOLS_EXPORT void socket_udp_broadcast_method_allatonce(sock_t, byte_buffer *, network_interface *, u16);
    NETTOOLS_EXPORT void socket_udp_broadcast_method_oneatime(sock_t, byte_buffer *, network_interface *, u16);
}