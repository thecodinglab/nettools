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
#include <nettools/icmp.h>
#include <cstring>
#include <iostream>

#include <nettools/socket.h>

int main()
{
    nettools::icmp_header header;
    header.m_type = ICMP_TYPE_ECHO_REQUEST;
    header.m_code = ICMP_CODE_ECHO_REQUEST;

    header.m_data_length = 60;
    header.m_data = static_cast<u8 *>(malloc(header.m_data_length));

    u8 identifier[] = {0x1b, 0xd8};
    u8 sequence[] = {0x00, 0x01};
    u8 timestamp[] = {0x0e, 0xd9, 0x15, 0x5a, 0x00, 0x00, 0x00, 0x00};
    u8 data[] = {
            0x14, 0xc3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
            0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
            0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
    };

    memcpy(header.m_data, identifier, 2);
    memcpy(header.m_data + 2, sequence, 2);
    memcpy(header.m_data + 4, timestamp, 8);
    memcpy(header.m_data + 12, data, 48);

    u16 checksum = nettools::icmp_calculate_checksum(&header);

    std::cout << "Checksum:    " << std::hex << checksum << std::endl;
    std::cout << "Expectation: e35d" << std::endl;

    free(header.m_data);
    return 0;
}