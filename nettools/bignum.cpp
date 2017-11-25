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
#include "bignum.h"
#include <random>
#include "standard.h"


namespace nettools
{
    bignum::bignum(u32 len)
    {
        m_len = max(sizeof(BIGNUM_VAL), len);
        m_value = new u8[m_len];
        memset(m_value, 0, m_len);
    }

    bignum::bignum(u32 len, void *data)
    {
        m_len = max(sizeof(BIGNUM_VAL), len);
        m_value = new u8[m_len];
        memcpy(m_value, data, len);
    }

    bignum::bignum(const bignum &o)
    {
        m_len = o.m_len;
        m_value = new u8[m_len];
        memcpy(m_value, o.m_value, m_len);
    }

    bignum::~bignum()
    { delete[] m_value; }

    bignum &bignum::operator=(BIGNUM_VAL val)
    {
        memset(m_value, 0, m_len);
#if BIGNUM_VAL_LEN == 8
        m_value[0] = val;
#elif BIGNUM_VAL_LEN == 16
        m_value[0] = static_cast<u8>(val & 0xff);
            m_value[1] = static_cast<u8>((val >> 8) & 0xff);
#elif BIGNUM_VAL_LEN == 32
        m_value[0] = static_cast<u8>(val & 0xff);
        m_value[1] = static_cast<u8>((val >> 8) & 0xff);
        m_value[2] = static_cast<u8>((val >> 16) & 0xff);
        m_value[3] = static_cast<u8>((val >> 24) & 0xff);
#elif BIGNUM_VAL_LEN == 64
        m_value[0] = static_cast<u8>(val & 0xff);
        m_value[1] = static_cast<u8>((val >> 8) & 0xff);
        m_value[2] = static_cast<u8>((val >> 16) & 0xff);
        m_value[3] = static_cast<u8>((val >> 24) & 0xff);
        m_value[4] = static_cast<u8>((val >> 32) & 0xff);
        m_value[5] = static_cast<u8>((val >> 40) & 0xff);
        m_value[6] = static_cast<u8>((val >> 48) & 0xff);
        m_value[7] = static_cast<u8>((val >> 56) & 0xff);
#endif
    }

    bignum &bignum::operator=(const bignum &o)
    {
        if (m_len != o.m_len)
        {
            delete[] m_value;

            m_len = o.m_len;
            m_value = new u8[m_len];
        }
        memcpy(m_value, o.m_value, m_len);
    }

    void bignum::randomize(std::mt19937 &engine)
    {
        std::uniform_int_distribution<u8> dist;
        for (u32 i = 0; i < m_len; i++)
            m_value[i] = dist(engine);
    }

    void bignum::to_string(u32 len, char *s) const
    {
        if (len == 0) return;

        bignum n(*this);
        u32 i = 0;
        do
        {
            s[i++] = static_cast<char>(n.remainder(10) + '0');
        } while ((n != 0) && (i < (len - 1)));
        s[i] = 0;

        for (u32 j = 0; --i > j; j++)
        {
            char c = s[i];
            s[i] = s[j];
            s[j] = c;
        }
    }

    BIGNUM_VAL bignum::to_int() const
    {
#if BIGNUM_VAL_LEN == 8
        return static_cast<u8>(a.m_value[0] & 0xff);
#elif BIGNUM_VAL_LEN == 16
        return static_cast<u16>((a.m_value[0] & 0xff) | ((a.m_value[1] & 0xff) << 8));
#elif BIGNUM_VAL_LEN == 32
        return static_cast<u32>((m_value[0] & 0xff) | ((m_value[1] & 0xff) << 8) | ((m_value[2] & 0xff) << 16) | ((m_value[3] & 0xff) << 24));
#elif BIGNUM_VAL_LEN == 64
        return static_cast<u64>(m_value[0] & 0xff) |
               (static_cast<u64>(m_value[1] & 0xff) << 8) |
               (static_cast<u64>(m_value[2] & 0xff) << 16) |
               (static_cast<u64>(m_value[3] & 0xff) << 24) |
               (static_cast<u64>(m_value[4] & 0xff) << 32) |
               (static_cast<u64>(m_value[5] & 0xff) << 40) |
               (static_cast<u64>(m_value[6] & 0xff) << 48) |
               (static_cast<u64>(m_value[7] & 0xff) << 56);
#endif
    }

    void bignum::operator<<=(BIGNUM_VAL bits)
    {
        const BIGNUM_VAL bytes = bits / 8 + 1;
        const BIGNUM_VAL bits_per_byte = bits % 8;

        u8 tmp[m_len];
        for (u32 i = 0; i < m_len; i++)
        {
            tmp[i] = m_value[i];
            m_value[i] = 0;
        }

        BIGNUM_VAL idx = bytes;
        for (u32 i = 0; i < m_len; i++, idx++)
        {
            u16 val = tmp[i] << static_cast<u16>(bits_per_byte);
            if (idx < m_len) m_value[idx] |= static_cast<u8>(val >> 8);
            if ((idx - 1) < m_len) m_value[idx - 1] |= static_cast<u8>(val & 0xff);
        }
    }

    void bignum::operator>>=(BIGNUM_VAL bits)
    {
        const BIGNUM_VAL bytes = bits / 8 + 1;
        const BIGNUM_VAL bits_per_byte = bits % 8;

        u8 tmp[m_len];
        for (u32 i = 0; i < m_len; i++)
        {
            tmp[i] = m_value[i];
            m_value[i] = 0;
        }

        u32 i = m_len;
        while (i--)
        {
            u16 val = (tmp[i] << 8) >> static_cast<u16>(bits_per_byte);
            if (i >= bytes) m_value[i - bytes] = static_cast<u8>(val & 0xff);
            if ((i + 1) >= bytes) m_value[(i + 1) - bytes] = static_cast<u8>(val >> 8);
        }
    }

    bignum operator<<(const bignum &a, BIGNUM_VAL bits)
    {
        bignum r(a);
        r <<= bits;
        return r;
    }

    bignum operator>>(const bignum &a, BIGNUM_VAL bits)
    {
        bignum r(a);
        r >>= bits;
        return r;
    }

    void bignum::div_lshift(u8 bit)
    {
        for (u32 i = 0; i < m_len; i++)
        {
            u16 x = static_cast<u16>((m_value[i] << 1) | bit);
            m_value[i] = static_cast<u8>(x & 0xff);
            bit = static_cast<u8>(x >> 8);
        }
    }

    void divide(const bignum &numerator, const bignum &divisor, bignum &quotient, bignum &remainder)
    {
        if (divisor == 0) return;
        quotient = 0;
        remainder = 0;
        u32 i = numerator.m_len;
        while (i--)
        {
            u8 bit = 8;
            while (bit--)
            {
                remainder.div_lshift(static_cast<u8>(numerator.m_value[i] >> bit & 0x01));
                if (divisor <= remainder)
                {
                    quotient.div_lshift(1);
                    remainder -= divisor;
                }
                else quotient.div_lshift(0);
            }
        }
    }

    void bignum::operator+=(const bignum &o)
    {
        u8 carry = 0;
        for (u32 i = 0; i < m_len; i++)
        {
            u16 sum = static_cast<u16>(m_value[i] + ((i < o.m_len) ? o.m_value[i] : 0) + carry);
            m_value[i] = static_cast<u8>(sum & 0xff);
            carry = static_cast<u8>(sum >> 8);
        }
    }

    void bignum::operator-=(const bignum &o)
    {
        u8 borrow = 0;
        for (u32 i = 0; i < m_len; i++)
        {
            u16 subtrahend = static_cast<u16>(((i < o.m_len) ? o.m_value[i] : 0) + borrow);
            borrow = static_cast<u8>(m_value[i] < subtrahend);
            m_value[i] -= static_cast<u8>(subtrahend & 0xff);
        }
    }

    void bignum::operator*=(const bignum &o)
    {
        u8 multiplier[m_len];
        for (u32 i = 0; i < m_len; i++)
        {
            multiplier[i] = m_value[i];
            m_value[i] = 0;
        }
        for (u32 i = 0; i < m_len; i++)
        {
            for (u32 j = 0; j < o.m_len; j++)
            {
                u16 product = multiplier[i] * o.m_value[j];
                u32 k = i + j;
                while (product != 0)
                {
                    if (k >= m_len) break;
                    product += m_value[k];
                    m_value[k] = static_cast<u8>(product & 0xff);
                    product >>= 8;
                    k++;
                }
            }
        }
    }

    void bignum::operator/=(const bignum &divisor)
    {
        bignum numerator(*this), remainder(divisor.m_len);
        divide(numerator, divisor, *this, remainder);
    }

    void bignum::operator%=(const bignum &divisor)
    {
        bignum numerator(*this), quotient(m_len);
        divide(numerator, divisor, quotient, *this);
    }

    bignum operator+(const bignum &a, const bignum &b)
    {
        bignum r(a);
        r += b;
        return r;
    }

    bignum operator-(const bignum &a, const bignum &b)
    {
        bignum r(a);
        r -= b;
        return r;
    }

    bignum operator*(const bignum &a, const bignum &b)
    {
        bignum r(a);
        r *= b;
        return r;
    }

    bignum operator/(const bignum &a, const bignum &b)
    {
        bignum r(a);
        r /= b;
        return r;
    }

    bignum operator%(const bignum &a, const bignum &b)
    {
        bignum r(a);
        r %= b;
        return r;
    }

    void modpow(const bignum &base, const bignum &exponent, const bignum &modulus, bignum &result)
    {
        bignum r(2 * base.m_len + 1);
        r = 1;
        bool one = true;
        u32 i = exponent.m_len;
        while (i--)
        {
            u8 bit = 1 << 7;
            do
            {
                if (!one)
                {
                    bignum n(r);
                    r *= n;
                    r %= modulus;
                }
                if (exponent.m_value[i] & bit)
                {
                    r *= base;
                    r %= modulus;
                    one = false;
                }
                bit >>= 1;
            } while (bit);
        }
        result = r;
    }

    i8 compare(const bignum &a, BIGNUM_VAL b)
    {
        for (u32 i = sizeof(BIGNUM_VAL); i < a.m_len; i++)
            if (a.m_value[i]) return 1;

        BIGNUM_VAL val = a.to_int();
        if (val > b) return 1;
        else if (val < b) return -1;
        return 0;
    }

    i8 compare(const bignum &a, const bignum &b)
    {
        u32 i;
        if (a.m_len > b.m_len)
        {
            for (i = a.m_len - 1; i >= b.m_len; i--)
            {
                if (a.m_value[i]) return 1;
            }
        }
        else if (a.m_len < b.m_len)
        {
            for (i = b.m_len - 1; i >= a.m_len; i--)
            {
                if (b.m_value[i]) return -1;
            }
        }
        else i = a.m_len - 1;

        while (true)
        {
            if (a.m_value[i] > b.m_value[i]) return 1;
            if (a.m_value[i] < b.m_value[i]) return -1;
            if (i == 0) return 0;
            i--;
        }
    }

    bool operator==(const bignum &a, BIGNUM_VAL b)
    { return compare(a, b) == 0; }

    bool operator==(const bignum &a, const bignum &b)
    { return compare(a, b) == 0; }

    bool operator!=(const bignum &a, BIGNUM_VAL b)
    { return compare(a, b) != 0; }

    bool operator!=(const bignum &a, const bignum &b)
    { return compare(a, b) != 0; }

    bool operator>(const bignum &a, BIGNUM_VAL b)
    { return compare(a, b) > 0; }

    bool operator>(const bignum &a, const bignum &b)
    { return compare(a, b) > 0; }

    bool operator>=(const bignum &a, BIGNUM_VAL b)
    { return compare(a, b) >= 0; }

    bool operator>=(const bignum &a, const bignum &b)
    { return compare(a, b) >= 0; }

    bool operator<(const bignum &a, BIGNUM_VAL b)
    { return compare(a, b) < 0; }

    bool operator<(const bignum &a, const bignum &b)
    { return compare(a, b) < 0; }

    bool operator<=(const bignum &a, BIGNUM_VAL b)
    { return compare(a, b) <= 0; }

    bool operator<=(const bignum &a, const bignum &b)
    { return compare(a, b) <= 0; }

    BIGNUM_VAL bignum::remainder(BIGNUM_VAL divisor)
    {
        u32 i = m_len;
        u8 rem = 0;
        while (i--)
        {
            u16 dividend = (rem << 8) | m_value[i];
            m_value[i] = static_cast<u8>(dividend / divisor);
            rem = static_cast<u8>(dividend % divisor);
        }
        return rem;
    }

    void gcd_euclid(const bignum &x, const bignum &y, bignum &a, bignum &b, bignum &g)
    {
        u32 length = x.m_len;
        if (y.m_len > length) length = y.m_len;

        if (x <= y)
        {
            bignum q(length), r(length);
            divide(y, x, q, r);
            if (r == 0)
            {
                a = 1;
                b = 0;
                g = x;
            }
            else
            {
                bignum ap(length);
                gcd_euclid(x, r, ap, b, g);
                a = ap + b * q;
            }
        }
        else
        {
            bignum ap(length), bp(length);
            gcd_euclid(y, x, bp, ap, g);
            a = y - ap;
            b = x - bp;
        }
    }

    void gcd(const bignum &x, const bignum &y, bignum &g)
    {
        if (x <= y)
        {
            bignum r = y % x;
            if (r == 0) g = x;
            else gcd(x, r, g);
        }
        else gcd(y, x, g);
    }
}