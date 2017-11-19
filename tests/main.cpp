#include <nettools/buffer.h>
#include <nettools/socket.h>
#include <nettools/interface.h>
#include <nettools/discovery.h>

#include <thread>

static bool foundAClient = false;

bool request(nettools::socket_address* client)
{
    return true;
}

void found(nettools::socket_address* client)
{
    std::cout << "Found: ";
    client->m_addr.print();

    nettools::discovery_ping(client);
    client->m_port = 12;
    nettools::discovery_ping(client);
}

void ping(nettools::socket_address* client, u32 time, bool reachable)
{
    if (reachable)
    {
        std::cout << "PING: ";
        client->m_addr.print();
        std::cout << "\t" << time << "ms" << std::endl;
    }
    else
    {
        std::cout << "PING: ";
        client->m_addr.print();
        std::cout << "\ttimedout" << std::endl;
        foundAClient = true;
    }
}

int main()
{
    nettools::socket_init();

    nettools::interface_query().m_unicast_addr.print();

    nettools::discovery_init(12345);
    nettools::discovery_set_handlers(request, found, ping);
    nettools::discovery_search(12346, true);

    while (!foundAClient)
    {
        nettools::discovery_update();
    }

    nettools::discovery_close();

    nettools::socket_cleanup();
    std::cin.get();
    return 0;
}
