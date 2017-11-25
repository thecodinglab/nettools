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
#include <nettools/bignum.h>
#include <iostream>

int main()
{
    nettools::bignum base(4);
    nettools::bignum exponent(4);
    nettools::bignum modulus(4);
    nettools::bignum result(1);

    base = 7;
    exponent = 2;
    modulus = 5;

    modpow(base, exponent, modulus, result);

    BIGNUM_VAL r = result.to_int();
    std::cout << r << std::endl;
    return 0;
}
