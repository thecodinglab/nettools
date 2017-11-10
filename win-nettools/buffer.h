/*
* win-nettols is a library for comonly used network stuff for windows
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
        explicit byte_buffer(size_t capacity);
        ~byte_buffer();

        u8* get_buffer_at_offset();
        const u8* get_const_buffer_at_offset() const;

        size_t get_capacity() const;
        size_t get_limit() const;
        size_t get_offset() const;

        void set_limit(const size_t lim);
        void set_offset(const size_t off);
        void flip();
        
        i8 get_i8(size_t off) const;
        i16 get_i16(size_t off) const;
        i32 get_i32(size_t off) const;
        i64 get_i64(size_t off) const;

        u8 get_u8(size_t off) const;
        u16 get_u16(size_t off) const;
        u32 get_u32(size_t off) const;
        u64 get_u64(size_t off) const;

        void put_i8(size_t off, const i8 val) const;
        void put_i16(size_t off, const i16 val) const;
        void put_i32(size_t off, const i32 val) const;
        void put_i64(size_t off, const i64 val) const;

        void put_u8(size_t off, const u8 val) const;
        void put_u16(size_t off, const u16 val) const;
        void put_u32(size_t off, const u32 val) const;
        void put_u64(size_t off, const u64 val) const;

        i8 get_i8();
        i16 get_i16();
        i32 get_i32();
        i64 get_i64();

        u8 get_u8();
        u16 get_u16();
        u32 get_u32();
        u64 get_u64();

        void put_i8(const i8 val);
        void put_i16(const i16 val);
        void put_i32(const i32 val);
        void put_i64(const i64 val);

        void put_u8(const u8 val);
        void put_u16(const u16 val);
        void put_u32(const u32 val);
        void put_u64(const u64 val);
    private:
        u8* m_buf;
        size_t m_cap;
        size_t m_lim;
        size_t m_off;
    };
}