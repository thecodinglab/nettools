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
#include "interface.h"
#include "standard.h"
#include <ifaddrs.h>
#include <net/if.h>
#include <cstring>

namespace nettools
{
    struct network_interface_list
    {
        ifaddrs *m_list;
        ifaddrs *m_current;
        network_interface *m_last;
    };

    network_interface_list_t interface_query_list()
    {
        ifaddrs *addrs;
        int code = getifaddrs(&addrs);
        if (code != 0) exit(-1);

        network_interface_list_t list = NULL;
        if (addrs)
        {
            list = new network_interface_list;
            list->m_list = addrs;
            list->m_current = addrs;
            list->m_last = NULL;
        }

        return list;
    }

    network_interface_t interface_query_next(network_interface_list_t list)
    {
        if (!list || !list->m_current) return NULL;

        while (list->m_current->ifa_addr->sa_family != AF_INET) {
            list->m_current = list->m_current->ifa_next;
            if (!list->m_current) return NULL;
        }

        network_interface_t iface = new network_interface;
        memset(iface, 0, sizeof(network_interface));

        if (list->m_last) delete list->m_last;
        list->m_last = iface;

        char* name = list->m_current->ifa_name;
        size_t len = min(strlen(name), MAX_NAME_LENGTH - 1);
        memcpy(iface->m_name, name, len);
        iface->m_name[len] = 0;

        sockaddr *unicast = list->m_current->ifa_addr;
        if (unicast && unicast->sa_family == AF_INET)
        {
            iface->m_unicast_addr.m_b1 = static_cast<u8>(unicast->sa_data[2] & 0xff);
            iface->m_unicast_addr.m_b2 = static_cast<u8>(unicast->sa_data[3] & 0xff);
            iface->m_unicast_addr.m_b3 = static_cast<u8>(unicast->sa_data[4] & 0xff);
            iface->m_unicast_addr.m_b4 = static_cast<u8>(unicast->sa_data[5] & 0xff);
        }

        sockaddr *netmask = list->m_current->ifa_netmask;
        if (netmask && netmask->sa_family == AF_INET)
        {
            iface->m_subnet_addr.m_b1 = static_cast<u8>(netmask->sa_data[2] & 0xff);
            iface->m_subnet_addr.m_b2 = static_cast<u8>(netmask->sa_data[3] & 0xff);
            iface->m_subnet_addr.m_b3 = static_cast<u8>(netmask->sa_data[4] & 0xff);
            iface->m_subnet_addr.m_b4 = static_cast<u8>(netmask->sa_data[5] & 0xff);

            iface->m_network_addr.m_address = iface->m_unicast_addr.m_address & iface->m_subnet_addr.m_address;
            iface->m_broadcast_addr.m_address = iface->m_network_addr.m_address | ~iface->m_subnet_addr.m_address;
        }

        list->m_current = list->m_current->ifa_next;
        return iface;
    }

    void interface_query_close(network_interface_list_t list)
    {
        if (!list) return;
        if (list->m_list) freeifaddrs(list->m_list);
        if (list->m_last) delete list->m_last;
        delete list;
    }

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