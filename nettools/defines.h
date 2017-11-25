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

#include <cstdint>
#include <string>

#define OS_WIN 1
#define OS_LINUX 2

#define ARCH_x32 1
#define ARCH_x64 2

#ifdef _WIN32
#define OS OS_WIN
#ifdef _WIN64
#define ARCH ARCH_x64
#else
#define ARCH ARCH_x32
#endif

#ifdef NETTOOLS_BUILD
#define NETTOOLS_EXPORT __declspec(dllexport)
#else
#define NETTOOLS_EXPORT __declspec(dllimport)
#endif
#elif defined(linux) || defined(__linux__) || defined(__linux)
#define OS OS_LINUX
#if defined(__x86_64__) || defined(__ppc64__)
#define ARCH ARCH_x64
#else
#define ARCH ARCH_x32
#endif

#define NETTOOLS_EXPORT
#else
#error unsupported operating system
#endif

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define i8_MAX_VAL 0x7f
#define i16_MAX_VAL 0x7fff
#define i32_MAX_VAL 0x7fffffff
#define i64_MAX_VAL 0x7fffffffffffffff

#define u8_MAX_VAL 0xff
#define u16_MAX_VAL 0xffff
#define u32_MAX_VAL 0xffffffff
#define u64_MAX_VAL 0xffffffffffffffff

#define i8_BITS 8
#define i16_BITS 16
#define i32_BITS 32
#define i64_BITS 64

#define u8_BITS 8
#define u16_BITS 16
#define u32_BITS 32
#define u64_BITS 64
