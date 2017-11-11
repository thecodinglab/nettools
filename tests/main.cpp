#include <socket.h>
#include <iostream>
#include "buffer.h"
#include <WS2tcpip.h>
#include <thread>
#include "interface.h"
#include "discovery.h"

static bool foundAClient = false;

bool request(nettools::socket_address* client)
{
    return true;
}

void found(nettools::socket_address* client)
{
    std::cout << "Found: ";
    client->m_addr.print();
    foundAClient = true;
}

int main()
{
    nettools::socket_init();

    nettools::discovery_init(12345);
    nettools::discovery_set_handlers(request, found);
    nettools::discovery_search(12346);
    
    while (!foundAClient)
    {
        nettools::discovery_update();
    }

    nettools::discovery_close();

    nettools::socket_cleanup();
    std::cin.get();
    return 0;
}
