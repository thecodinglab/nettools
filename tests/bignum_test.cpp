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
#include <chrono>

void print_bignum(const nettools::bignum &num)
{
    char string[8192];
    num.to_string(sizeof(string), string);
    std::cout << string << std::endl;
}

int main()
{
    nettools::bignum x(512);
    nettools::bignum y(512);
    nettools::bignum a(512);
    nettools::bignum b(512);
    nettools::bignum g(512);

    std::mt19937 engine(static_cast<unsigned long>(time(NULL)));

    x.randomize(engine);
    print_bignum(x);
    y.randomize(engine);
    print_bignum(y);

    auto started = std::chrono::high_resolution_clock::now();
    gcd_euclid(x, y, a, b, g);
    auto needed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - started);
    std::cout << "Needed " << needed.count() << "ms for gcd_euclid" << std::endl;

    started = std::chrono::high_resolution_clock::now();
    //gcd_euclid(x, y, a, b, g);
    gcd(x, y, g);
    needed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - started);
    std::cout << "Needed " << needed.count() << "ms for gcd" << std::endl;

    print_bignum(g);
    return 0;
}
