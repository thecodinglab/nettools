add_executable(nettools-test main.cpp)
target_link_libraries(nettools-test nettools)

add_executable(nettools-icmp-test icmp_test.cpp)
target_link_libraries(nettools-icmp-test nettools)

add_executable(nettools-udp-socket-test udp_socket_test.cpp)
target_link_libraries(nettools-udp-socket-test nettools)