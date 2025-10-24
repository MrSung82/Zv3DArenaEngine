/*
-----------------
 Persistent info
-----------------

This file is part of the "Zv3D" project.

MIT License

Copyright (c) 2012-2099 Marat Sungatullin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

......
 Web:
......

 + https:// (for questions and help)

-------------
 Description
-------------
Purpose: blank file for headers.

----------------------
 For developers notes
----------------------

*/

#pragma once

#if defined(__x86_64__) || defined(_M_AMD64)
#	define ZVD_ARCH_X86_64 1
#elif defined(__i386__) || defined(_M_IX86)
#	define ZVD_ARCH_X86 1
#elif defined(__arm__) || defined(_M_ARM)
#	define ZVD_ARCH_ARM32 1
#elif defined(__aarch64__) || defined(_M_ARM64)
#	define ZVD_ARCH_ARM64 1
#else
#	error "Unsupported architecture"
#endif

#if defined(ZVD_ARCH_X86_64) || defined(ZVD_ARCH_X86) || defined(ZVD_ARCH_ARM32) || defined(ZVD_ARCH_ARM64)
#	define ZVD_LITTLE_ENDIAN 1
#else
#	error "Big endianness is not supported"
#endif

#if defined(__CYGWIN__)
#error "Cygwin is obsolete. Use WSL or MinGW-w64."
#endif


#if defined(_WIN32)
#	define ZVD_PLATFORM_WINDOWS 1
#	define ZVD_PLATFORM_STRINGA "Windows"
#	define ZVD_PLATFORM_STRINGW L"Windows"
#	define ZVD_PLATFORM_DESKTOP 1
// _WIN64 is defined by MSVC, GCC, and Clang when targeting 64-bit Windows.
// It is only set in 64-bit builds (x64 or ARM64), never in 32-bit.
// Always check _WIN32 first — _WIN64 implies _WIN32.
#	ifdef _WIN64
#		define ZVD_PLATFORM_WINDOWS64 1
#	else
#		define ZVD_PLATFORM_WINDOWS32 1
#	endif

// MinGW (Minimalist GNU for Windows) — GCC-based toolchain targeting native Windows.
// Treated as a desktop environment since it produces standard Windows executables.
#	if defined(__MINGW32__) || defined(__MINGW64__)
#		define ZVD_PLATFORM_MINGW 1
#	endif

#	if defined(ZVD_ARCH_X86_64)
#		define ZVD_PLATFORM_ARCH_STRINGA "Windows-x64"
#		define ZVD_PLATFORM_ARCH_STRINGW L"Windows-x64"
#	elif defined(ZVD_ARCH_X86)
#		define ZVD_PLATFORM_ARCH_STRINGA "Windows-x86"
#		define ZVD_PLATFORM_ARCH_STRINGW L"Windows-x86"
#	endif

#elif defined(__linux) || defined(__linux__)
#	define ZVD_PLATFORM_LINUX 1
#	define ZVD_PLATFORM_STRINGA "Linux"
#	define ZVD_PLATFORM_STRINGW L"Linux"
#	define ZVD_PLATFORM_DESKTOP 1
#	if defined(ZVD_ARCH_X86_64)
#		define ZVD_PLATFORM_ARCH_STRINGA "Linux-x64"
#		define ZVD_PLATFORM_ARCH_STRINGW L"Linux-x64"
#	elif defined(ZVD_ARCH_X86)
#		define ZVD_PLATFORM_ARCH_STRINGA "Linux-x86"
#		define ZVD_PLATFORM_ARCH_STRINGW L"Linux-x86"
#	endif

#else
#	error "Unsupported platform"

#endif // eof Platform OS


#if defined(_WIN64) || defined(__LP64__)
#define ZVD_PTR_SIZE 8
#else
#define ZVD_PTR_SIZE 4
#endif

#if defined(ZVD_ARCH_X86_64) || defined(ZVD_ARCH_X86) || defined(ZVD_ARCH_ARM32) || defined(ZVD_ARCH_ARM64)
#define ZVD_WORD_SIZE ZVD_PTR_SIZE
#endif

#if defined(ZVD_PLATFORM_WINDOWS) || defined(ZVD_PLATFORM_LINUX)
#define ZVD_MIN_MALLOC_ALIGNMENT (ZVD_PTR_SIZE * 2)
#endif


// Cache line (conservative)
#if defined(ZVD_ARCH_X86_64) || defined(ZVD_ARCH_ARM64)
#	define ZVD_CACHE_LINE_SIZE 64
#else
#	define ZVD_CACHE_LINE_SIZE 32
#endif