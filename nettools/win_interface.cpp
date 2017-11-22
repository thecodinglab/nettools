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
#include <Iphlpapi.h>
#include <WS2tcpip.h>
#include <comutil.h>

#define MAX_TRIES 2

namespace nettools
{
    struct network_interface_list
    {
        PIP_ADAPTER_ADDRESSES list;
        PIP_ADAPTER_ADDRESSES current;
        network_interface* last;
    };

    network_interface_list_ptr interface_query_list()
    {
        PIP_ADAPTER_ADDRESSES addresses;
        u32 iterations = 0, out_buffer_length = 16 * 1024;
        i32 retval = 0;

        do
        {
            addresses = static_cast<IP_ADAPTER_ADDRESSES*>(malloc(out_buffer_length));
            retval = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_GATEWAYS, NULL, addresses, PULONG(&out_buffer_length));
            if (retval == ERROR_BUFFER_OVERFLOW)
            {
                free(addresses);
                addresses = NULL;
            }
            else break;
            iterations++;
        } while ((retval == ERROR_BUFFER_OVERFLOW) && (iterations < MAX_TRIES));

        network_interface_list_ptr list = NULL;

        if (retval == NO_ERROR)
        {
            list = new network_interface_list;
            list->list = addresses;
            list->current = addresses;
            list->last = NULL;
        }

        return list;
    }

    network_interface_ptr interface_query_next(network_interface_list_ptr list)
    {
        if (!list->current) return NULL;

        network_interface_ptr iface = new network_interface;
        memset(iface, 0, sizeof(network_interface));

        if (list->last) delete list->last;
        list->last = iface;

        PWCHAR wchar_description = list->current->Description;
        _bstr_t tmp(wchar_description);

        PCHAR description = tmp;

        u32 len = min(strlen(description), (MAX_NAME_LENGTH - 1));
        memcpy(iface->m_name, description, len);
        iface->m_name[len] = 0;

        PIP_ADAPTER_UNICAST_ADDRESS unicast = list->current->FirstUnicastAddress;
        if (unicast)
        {
            LPSOCKADDR unicast_address = unicast->Address.lpSockaddr;
            iface->m_unicast_addr.m_b1 = unicast_address->sa_data[2];
            iface->m_unicast_addr.m_b2 = unicast_address->sa_data[3];
            iface->m_unicast_addr.m_b3 = unicast_address->sa_data[4];
            iface->m_unicast_addr.m_b4 = unicast_address->sa_data[5];

            iface->m_subnet_addr.m_address = (1 << unicast->OnLinkPrefixLength) - 1;
            iface->m_network_addr.m_address = iface->m_unicast_addr.m_address & iface->m_subnet_addr.m_address;
            iface->m_broadcast_addr.m_address = iface->m_network_addr.m_address | ~iface->m_subnet_addr.m_address;
        }

        if (list->current->PhysicalAddressLength == 6) {
            memcpy(iface->m_mac_address.m_address, list->current->PhysicalAddress, 6);
        }

        list->current = list->current->Next;
        return iface;
    }

    void interface_query_close(network_interface_list_ptr list)
    {
        free(list->list);
        delete list->last;
        delete list;
    }

    network_interface interface_query()
    {
        network_interface_list_ptr list = interface_query_list();

        network_interface_ptr current;
        while (current = interface_query_next(list)) {
            if (current->m_mac_address.m_address && current->m_unicast_addr.m_address && current->m_subnet_addr.m_address) {
                return *current;
            }
        }

        return { 0 };
    }
}
