#include <socket.h>
#include <iostream>
#include "buffer.h"
#include <WS2tcpip.h>
#include <thread>
#include "interface.h"

nettools::socket_address server_address;
nettools::socket_address client_address;
bool running = false;

void srv_thread()
{
    nettools::sock_t server = nettools::socket_create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    nettools::socket_configure_blocking(server, true);
    nettools::socket_bind(server, &server_address);
    nettools::socket_listen(server);

    nettools::socket_address client_addr;
    nettools::sock_t client = nettools::socket_accept(server, &client_addr);

    nettools::byte_buffer buffer(1024);
    nettools::socket_read(client, &buffer);
    buffer.flip();

    std::cout << "INT VAL: " << buffer.get_i32() << std::endl;

    nettools::socket_close(server);
}

int main()
{
    nettools::socket_init();

    nettools::network_interface network_interface = nettools::interface_query();
    
    server_address.m_addr = network_interface.m_unicast_addr;
    server_address.m_port = 6654;

    client_address.m_addr = network_interface.m_unicast_addr;
    client_address.m_port = 6655;

    std::thread server_thread(srv_thread);

    nettools::sock_t client = nettools::socket_create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    nettools::socket_connect(client, &server_address);

    nettools::byte_buffer buffer(1024);
    buffer.put_i32(123098);
    buffer.flip();

    nettools::socket_send(client, &buffer);

    nettools::socket_close(client);

    server_thread.join();

    nettools::socket_cleanup();
    std::cin.get();
    return 0;
}
