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
#include "udp_socket.h"
#include <cstring>
#include <chrono>
#include "standard.h"

#define POLY 0x82f63b78

#define MAX_PACKET_LENGTH 1024
#define PACKET_RESEND 1000000000
#define PACKET_ACK_RESPONSE 0x80000000
#define PACKET_DONT_ACK 0x40000000
#define PACKET_ID_MASK 0x0fffffff

#define SEQUENCE_END 0x80000000
#define SEQUENCE_ID_MASK 0x0ffff000
#define SEQUENCE_IDX_MASK 0x00000fff

#define PUT_U32(buf, idx, x) \
    (buf)[(idx)    ] = ((x) >> 24) & 0xff; \
    (buf)[(idx) + 1] = ((x) >> 16) & 0xff; \
    (buf)[(idx) + 2] = ((x) >> 8) & 0xff; \
    (buf)[(idx) + 3] = (x) & 0xff;

#define GET_U32(buf, idx, x) \
    (x)  = ((buf)[(idx)    ] & 0xff) << 24; \
    (x) |= ((buf)[(idx) + 1] & 0xff) << 16; \
    (x) |= ((buf)[(idx) + 2] & 0xff) << 8; \
    (x) |=  (buf)[(idx) + 3] & 0xff;

namespace nettools
{
    struct packet
    {
        u32 m_packet_id;
        u32 m_sequence_id;
        u32 m_checksum;

        u32 m_size;
        u8 *m_data;
    };

    uint32_t crc32_calculate(u32 crc, const u8 *buf, size_t len)
    {
        u32 k;
        crc = ~crc;
        while (len--)
        {
            crc ^= *buf++;
            for (k = 0; k < 8; k++)
                crc = crc & 0x01 ? (crc >> 1) ^ POLY : crc >> 1;
        }
        return ~crc;
    }

    struct packet_sequence_item
    {
        packet m_packet;
        u64 m_last_send;
        packet_sequence_item *m_next;
    };

    struct packet_sequence
    {
        u16 m_sequence_id;
        u16 m_next_packet;
        socket_address m_receiver;

        packet_sequence_item *m_first;
        packet_sequence_item *m_last;
        packet_sequence_item *m_next;

        packet_sequence *m_next_sequence;
    };


    struct udp_sock
    {
        sock_t m_socket;

        u8 m_read_buffer[2 * MAX_PACKET_LENGTH];

        u32 m_next_packet_id;
        u16 m_next_sequence_id;

        packet_sequence *m_current_sequence;
        packet_sequence *m_last_sequence;
    };

    udp_sock_t socket_udp_create(network_interface_t iface, u16 port)
    {
        sock_t socket = socket_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (!socket) return NULL;

        socket_address address{iface->m_unicast_addr, port};
        socket_bind(socket, &address);

        udp_sock_t udp_socket = new udp_sock;
        udp_socket->m_socket = socket;

        udp_socket->m_next_packet_id = 1;
        udp_socket->m_next_sequence_id = 1;
        udp_socket->m_current_sequence = NULL;
        udp_socket->m_last_sequence = NULL;
        return udp_socket;
    }

    sock_sequence_t socket_udp_sequence_new(udp_sock_t socket, socket_address_t receiver)
    {
        packet_sequence *sequence = new packet_sequence;
        sequence->m_sequence_id = socket->m_next_sequence_id++;
        sequence->m_next_packet = 1;
        sequence->m_receiver = *receiver;
        sequence->m_first = NULL;
        sequence->m_last = NULL;
        sequence->m_next = NULL;
        sequence->m_next_sequence = NULL;

        if (socket->m_last_sequence != NULL) socket->m_last_sequence->m_next_sequence = sequence;
        else if (socket->m_current_sequence == NULL) socket->m_current_sequence = sequence;
        socket->m_last_sequence = sequence;
        return sequence;
    }

    void socket_udp_sequence_attach(udp_sock_t socket, sock_sequence_t ptr, const void *data, u32 len)
    {
        packet_sequence *sequence = static_cast<packet_sequence *>(ptr);

        while (len != 0)
        {
            u32 plen = min(len, MAX_PACKET_LENGTH);
            u8 *pdata = new u8[plen];
            memcpy(pdata, data, plen);

            data += plen;
            len -= plen;

            packet_sequence_item *item = new packet_sequence_item;
            item->m_next = NULL;
            item->m_last_send = static_cast<u64>(std::chrono::milliseconds(0).count());

            item->m_packet.m_packet_id = socket->m_next_packet_id++;
            item->m_packet.m_sequence_id = (static_cast<u32>(sequence->m_sequence_id) << 12) | (static_cast<u32>(sequence->m_next_packet++) & 0xfff);
            item->m_packet.m_checksum = 0;
            item->m_packet.m_size = plen;
            item->m_packet.m_data = pdata;

            if (sequence->m_first == NULL)
            {
                sequence->m_first = item;
                sequence->m_last = item;
            }
            else
            {
                sequence->m_last->m_next = item;
                sequence->m_last = item;
            }
        }
    }

    void socket_udp_sequence_end(sock_sequence_t ptr)
    {
        packet_sequence *sequence = static_cast<packet_sequence *>(ptr);
        sequence->m_last->m_packet.m_sequence_id |= SEQUENCE_END;
    }

    void socket_udp_update(udp_sock_t socket)
    {
        socket_configure_blocking(socket->m_socket, true);
        packet_sequence *sequence = socket->m_current_sequence;
        packet_sequence *previous = NULL;
        while (sequence != NULL)
        {
            sockaddr_in addr;
            addr.sin_port = htons(sequence->m_receiver.m_port);
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = sequence->m_receiver.m_addr.m_address;

            packet_sequence_item *item = sequence->m_next;
            if (item == NULL) sequence->m_next = sequence->m_first;
            item = sequence->m_next;
            if (item == NULL)
            {
                if (previous == NULL) socket->m_current_sequence = sequence->m_next_sequence;
                else if (previous != NULL) previous->m_next_sequence = sequence->m_next_sequence;
            }
            else
            {
                previous = sequence;

                u64 now = static_cast<u64>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
                u64 elapsed = now - item->m_last_send;
                if (elapsed >= PACKET_RESEND)
                {
                    packet *p = &item->m_packet;

                    u32 data_len = 16 + p->m_size;
                    u8 *data = new u8[data_len];
                    if (p->m_checksum == 0)
                    {
                        PUT_U32(data, 0, p->m_packet_id);
                        PUT_U32(data, 4, p->m_sequence_id);
                        PUT_U32(data, 12, p->m_size);
                        memcpy(data + 16, p->m_data, p->m_size);

                        u32 crc = crc32_calculate(0, data, 8);
                        crc = crc32_calculate(crc, data + 12, data_len - 12);
                        p->m_checksum = crc;

                        PUT_U32(data, 8, p->m_checksum);
                    }
                    else
                    {
                        PUT_U32(data, 0, p->m_packet_id);
                        PUT_U32(data, 4, p->m_sequence_id);
                        PUT_U32(data, 8, p->m_checksum);
                        PUT_U32(data, 12, p->m_size);
                        memcpy(data + 16, p->m_data, p->m_size);
                    }
                    printf("PacketID: %u, SequenceID: %u, Size: %u, Checksum: %x\n", p->m_packet_id, p->m_sequence_id, p->m_size, p->m_checksum);

                    sendto(socket->m_socket, data, data_len, 0, reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_in));
                    item->m_last_send = now;
                }
            }

            sequence = sequence->m_next_sequence;
        }
        socket_configure_blocking(socket->m_socket, false);

        sockaddr_in recv_addr;
        u32 recv_addr_len = sizeof(sockaddr_in);
        i32 read = static_cast<i32>(recvfrom(socket->m_socket, socket->m_read_buffer, 2 * MAX_PACKET_LENGTH, 0, reinterpret_cast<sockaddr *>(&recv_addr), &recv_addr_len));
        if (read >= 16)
        {
            u32 packet_id, sequence_id, checksum, size;
            GET_U32(socket->m_read_buffer, 0, packet_id);
            GET_U32(socket->m_read_buffer, 4, sequence_id);
            GET_U32(socket->m_read_buffer, 8, checksum);
            GET_U32(socket->m_read_buffer, 12, size);

            u32 crc = crc32_calculate(0, socket->m_read_buffer, 8);
            crc = crc32_calculate(crc, socket->m_read_buffer + 12, 4 + size);

            if (crc != checksum)
            {
                // TODO request resend packet
            }
            else
            {
                if (packet_id & PACKET_ACK_RESPONSE)
                {
                    printf("ANSWER RECEIVED!\n");
                }
                else if ((packet_id & PACKET_DONT_ACK) == 0)
                {
                    u8 response[16];
                    PUT_U32(response, 0, packet_id | PACKET_ACK_RESPONSE);
                    PUT_U32(response, 4, sequence_id);
                    PUT_U32(response, 12, 0);

                    u32 response_crc = crc32_calculate(0, response, 8);
                    response_crc = crc32_calculate(response_crc, response + 12, 4);
                    PUT_U32(response, 8, response_crc);

                    sendto(socket->m_socket, response, 16, 0, reinterpret_cast<const sockaddr *>(&recv_addr), recv_addr_len);
                    printf("ANSWERED\n");
                }
                else
                {
                    printf("ERROR\n");
                    // TODO request resend packet
                }
            }
        }
    }

    void socket_udp_close(udp_sock_t socket)
    {
        socket_close(socket->m_socket);
        delete socket;
    }

}