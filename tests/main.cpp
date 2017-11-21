#include <nettools/buffer.h>
#include <nettools/socket.h>
#include <nettools/interface.h>
#include <nettools/discovery.h>

#include <iostream>
#include <thread>

static bool foundAClient = false;

bool request(const nettools::socket_address_ptr client)
{
    return true;
}

void found(const nettools::socket_address_ptr client)
{
    std::cout << "Found: " << client->m_addr.to_string() << std::endl;

    nettools::discovery_ping(client);
    client->m_port = 12;
    nettools::discovery_ping(client);
}

void ping(const nettools::socket_address_ptr client, const u32 time, const bool reachable)
{
    if (reachable)
    {
        std::cout << "PING: " << client->m_addr.to_string() << std::endl;
        std::cout << "\t" << time << "ms" << std::endl;
    }
    else
    {
        std::cout << "PING: " << client->m_addr.to_string() << std::endl;
        std::cout << "\ttimedout" << std::endl;
        foundAClient = true;
    }
}

int main()
{
    nettools::socket_init();

    nettools::network_interface iface = nettools::interface_query();
    std::cout << "IP-Address: " << iface.m_mac_address.to_string() << std::endl;

    nettools::discovery_init(12345);
    nettools::discovery_set_handlers(request, found, ping);
    nettools::discovery_search(12345, false);

    std::cout << "Send" << std::endl;

    while (!foundAClient)
    {
        nettools::discovery_update();
    }

    nettools::discovery_close();

    nettools::socket_cleanup();
    std::cin.get();
    return 0;
}
