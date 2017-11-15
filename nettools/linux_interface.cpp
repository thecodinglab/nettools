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
#include "interface.h"
#include <ifaddrs.h>
#include <net/if.h>

namespace nettools
{
    network_interface interface_query()
    {
        ifaddrs *addrs;
        int code = getifaddrs(&addrs);
        if (code != 0) exit(-1);

        network_interface iface = {0};

        ifaddrs *current = addrs;
        while (current)
        {
            if (current->ifa_flags & IFF_UP && current->ifa_flags & IFF_BROADCAST)
            {
                sockaddr *unicast = current->ifa_addr;
                if (unicast->sa_family == AF_INET)
                {
                    iface.m_unicast_addr.m_b1 = static_cast<u8>(unicast->sa_data[2] & 0xff);
                    iface.m_unicast_addr.m_b2 = static_cast<u8>(unicast->sa_data[3] & 0xff);
                    iface.m_unicast_addr.m_b3 = static_cast<u8>(unicast->sa_data[4] & 0xff);
                    iface.m_unicast_addr.m_b4 = static_cast<u8>(unicast->sa_data[5] & 0xff);

                    sockaddr *netmask = current->ifa_netmask;
                    iface.m_subnet_addr.m_b1 = static_cast<u8>(netmask->sa_data[2] & 0xff);
                    iface.m_subnet_addr.m_b2 = static_cast<u8>(netmask->sa_data[3] & 0xff);
                    iface.m_subnet_addr.m_b3 = static_cast<u8>(netmask->sa_data[4] & 0xff);
                    iface.m_subnet_addr.m_b4 = static_cast<u8>(netmask->sa_data[5] & 0xff);

                    iface.m_network_addr.m_address = iface.m_unicast_addr.m_address & iface.m_subnet_addr.m_address;
                    iface.m_broadcast_addr.m_address = iface.m_network_addr.m_address | ~iface.m_subnet_addr.m_address;
                }
            }
            current = current->ifa_next;
        }

        freeifaddrs(addrs);
        return iface;
    }
}