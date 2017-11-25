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
#include "icmp.h"

namespace nettools
{
    u16 icmp_calculate_checksum(icmp_header *header)
    {
        u32 sum = (header->m_type << 8) | header->m_code;
        for (u32 i = 0; i < header->m_data_length; i++)
            sum += (header->m_data[i++] << 8) | (i < header->m_data_length ? header->m_data[i] : 0);
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);
        return static_cast<u16>(~sum);
    }
};