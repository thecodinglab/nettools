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
#include <iostream>
#include <ws2ipdef.h>
#include <WS2tcpip.h>

#define MAX_TRIES 2

namespace nettools
{
    network_interface interface_query()
    {
        PIP_ADAPTER_ADDRESSES addresses;
        u32 iterations = 0, out_buffer_length = 15 * 1024;
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

        network_interface result;
        memset(&result, 0, sizeof(network_interface));

        if (retval == NO_ERROR)
        {
            PIP_ADAPTER_ADDRESSES current = addresses;
            while (current)
            {
                PIP_ADAPTER_UNICAST_ADDRESS unicast = current->FirstUnicastAddress;
                if (unicast)
                {
                    PIP_ADAPTER_DNS_SERVER_ADDRESS dns_server = current->FirstDnsServerAddress;
                    if (dns_server)
                    {
                        PIP_ADAPTER_GATEWAY_ADDRESS gateway = current->FirstGatewayAddress;
                        if (gateway)
                        {
                            LPSOCKADDR unicast_address = unicast->Address.lpSockaddr;
                            LPSOCKADDR dns_server_address = dns_server->Address.lpSockaddr;
                            LPSOCKADDR gateway_address = gateway->Address.lpSockaddr;

                            result.m_unicast_addr.m_b1 = unicast_address->sa_data[2];
                            result.m_unicast_addr.m_b2 = unicast_address->sa_data[3];
                            result.m_unicast_addr.m_b3 = unicast_address->sa_data[4];
                            result.m_unicast_addr.m_b4 = unicast_address->sa_data[5];

                            result.m_dns_server_addr.m_b1 = dns_server_address->sa_data[2];
                            result.m_dns_server_addr.m_b2 = dns_server_address->sa_data[3];
                            result.m_dns_server_addr.m_b3 = dns_server_address->sa_data[4];
                            result.m_dns_server_addr.m_b4 = dns_server_address->sa_data[5];

                            result.m_gateway_addr.m_b1 = gateway_address->sa_data[2];
                            result.m_gateway_addr.m_b2 = gateway_address->sa_data[3];
                            result.m_gateway_addr.m_b3 = gateway_address->sa_data[4];
                            result.m_gateway_addr.m_b4 = gateway_address->sa_data[5];

                            result.m_subnet_prefix = unicast->OnLinkPrefixLength;

                            u32 subnet = (1 << result.m_subnet_prefix) - 1;
                            result.m_network_addr.m_address = result.m_unicast_addr.m_address & subnet;
                            result.m_broadcast_addr.m_address = result.m_network_addr.m_address | ~subnet;
                            break;
                        }
                    }
                }
                current = current->Next;
            }
        }

        if (addresses) free(addresses);
        return result;
    }
}
