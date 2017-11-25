add_executable(nettools-test main.cpp)
target_link_libraries(nettools-test nettools)

add_executable(nettools-icmp-test icmp_test.cpp)
target_link_libraries(nettools-icmp-test nettools)

add_executable(nettools-u4096-test bignum_test.cpp)
target_link_libraries(nettools-u4096-test nettools)