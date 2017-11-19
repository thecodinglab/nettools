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
#pragma once

#include "defines.h"

namespace nettools
{
    struct NETTOOLS_EXPORT byte_buffer
    {
        explicit byte_buffer(size_t);
        ~byte_buffer();

        u8 *get_buffer_at_offset();
        const u8 *get_const_buffer_at_offset() const;

        size_t get_capacity() const;
        size_t get_limit() const;
        size_t get_offset() const;

        void set_limit(const size_t);
        void set_offset(const size_t);
        void flip();
        void reset();

        void get(size_t, void *, size_t) const;

        i8 get_i8(size_t) const;
        i16 get_i16(size_t) const;
        i32 get_i32(size_t) const;
        i64 get_i64(size_t) const;

        u8 get_u8(size_t) const;
        u16 get_u16(size_t) const;
        u32 get_u32(size_t) const;
        u64 get_u64(size_t) const;

        void put(size_t, void *, size_t);

        void put_i8(size_t, i8);
        void put_i16(size_t, i16);
        void put_i32(size_t, i32);
        void put_i64(size_t, i64);

        void put_u8(size_t, u8);
        void put_u16(size_t, u16);
        void put_u32(size_t, u32);
        void put_u64(size_t, u64);

        void get(void *, size_t);

        i8 get_i8();
        i16 get_i16();
        i32 get_i32();
        i64 get_i64();

        u8 get_u8();
        u16 get_u16();
        u32 get_u32();
        u64 get_u64();

        void put(void *, size_t);

        void put_i8(i8);
        void put_i16(i16);
        void put_i32(i32);
        void put_i64(i64);

        void put_u8(u8);
        void put_u16(u16);
        void put_u32(u32);
        void put_u64(u64);
    private:
        u8 *m_buf;
        size_t m_cap;
        size_t m_lim;
        size_t m_off;
    };
}