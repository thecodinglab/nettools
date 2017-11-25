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

#include <cstring>
#include "defines.h"

#define BIGNUM_VAL u32
#define BIGNUM_VAL_LEN 32

namespace nettools
{
    struct NETTOOLS_EXPORT bignum
    {
        explicit bignum(u32);
        explicit bignum(u32, void *);
        bignum(const bignum &);
        ~bignum();

        bignum &operator=(BIGNUM_VAL);
        bignum &operator=(const bignum &);

        void to_string(u32, char *);

        BIGNUM_VAL to_int() const;

        void operator<<=(BIGNUM_VAL);
        void operator>>=(BIGNUM_VAL);

        friend bignum operator<<(const bignum &, BIGNUM_VAL);
        friend bignum operator>>(const bignum &, BIGNUM_VAL);

        void div_lshift(u8 bit);
        friend void divide(const bignum &, const bignum &, bignum &, bignum &);

        void operator+=(const bignum &);
        void operator-=(const bignum &);
        void operator*=(const bignum &);
        void operator/=(const bignum &);
        void operator%=(const bignum &);

        friend bignum operator+(const bignum &, const bignum &);
        friend bignum operator-(const bignum &, const bignum &);
        friend bignum operator*(const bignum &, const bignum &);
        friend bignum operator/(const bignum &, const bignum &);
        friend bignum operator%(const bignum &, const bignum &);

        friend void modpow(const bignum &, const bignum &, const bignum &, bignum &);

        friend i8 compare(const bignum &, BIGNUM_VAL);
        friend i8 compare(const bignum &, const bignum &);

        friend bool operator==(const bignum &, BIGNUM_VAL);
        friend bool operator==(const bignum &, const bignum &);
        friend bool operator!=(const bignum &, BIGNUM_VAL);
        friend bool operator!=(const bignum &, const bignum &);
        friend bool operator>(const bignum &, BIGNUM_VAL);
        friend bool operator>(const bignum &, const bignum &);
        friend bool operator>=(const bignum &, BIGNUM_VAL);
        friend bool operator>=(const bignum &, const bignum &);
        friend bool operator<(const bignum &, BIGNUM_VAL);
        friend bool operator<(const bignum &, const bignum &);
        friend bool operator<=(const bignum &, BIGNUM_VAL);
        friend bool operator<=(const bignum &, const bignum &);

        friend void gcd_euclid(const bignum &, const bignum &, bignum &, bignum &, bignum &);
        friend void gcd(const bignum &, const bignum &, bignum &);
    private:
        u32 m_len;
        u8 *m_value;

        BIGNUM_VAL remainder(BIGNUM_VAL);
    };
}