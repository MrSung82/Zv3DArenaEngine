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

#include "base/zvdbasedefs.h"

// ============================================================================
// BYTE UTILITIES (little-endian only)
// ============================================================================

namespace zvd
{

    // Always true for your targets
    static constexpr bool kIsLittleEndian = true;

    // ------------------------------------------------------------------------
    // Low-level byte access via union (safe, no UB for trivial types)
    // ------------------------------------------------------------------------

    template<typename T>
    union ByteAccess
    {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
        T value;
        uint8_t bytes[sizeof(T)];
    };

    template<typename T>
    union WordAccess
    {
        static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
        T value;
        uint16_t words[sizeof(T) >> 1];
    };
} // eof zvd


template<typename T>
constexpr uint8_t ZvdGetByte(T var, size_t idx) noexcept
{
    return zvd::ByteAccess<T>{var}.bytes[idx];
    
}

template<typename T>
constexpr void ZvdSetByte(T& var, size_t idx, uint8_t uByteVal) noexcept
{
    zvd::ByteAccess<T> byteAccess{ var };
    byteAccess.bytes[idx] = uByteVal;
    var = byteAccess.value;
}


template<typename T>
constexpr uint8_t ZvdGetWord(T var, size_t idx) noexcept
{
    return zvd::WordAccess<T>{var}.words[idx];
    
}

template<typename T>
constexpr void ZvdSetWord(T& var, size_t idx, uint16_t uWordVal) noexcept
{
    zvd::WordAccess<T> wordAccess{ var };
    wordAccess.words[idx] = uWordVal;
    var = wordAccess.value;
}


// ------------------------------------------------------------------------
// High/Low helpers (for common types)
// ------------------------------------------------------------------------

inline constexpr uint8_t ZvdLoByte(uint16_t v) noexcept { return static_cast<uint8_t>(v); }
inline constexpr uint8_t ZvdHiByte(uint16_t v) noexcept { return static_cast<uint8_t>(v >> 8); }

inline constexpr uint16_t ZvdLoWord(uint32_t v) noexcept { return static_cast<uint16_t>(v); }
inline constexpr uint16_t ZvdHiWord(uint32_t v) noexcept { return static_cast<uint16_t>(v >> 16); }

inline constexpr uint32_t ZvdLoDword(uint64_t v) noexcept { return static_cast<uint32_t>(v); }
inline constexpr uint32_t ZvdHiDword(uint64_t v) noexcept { return static_cast<uint32_t>(v >> 32); }


#if defined(ZVD_COMPILER_MSVC)
inline uint16_t ZvdByteSwap(uint16_t x) { return _byteswap_ushort(x); }
inline uint32_t ZvdByteSwap(uint32_t x) { return _byteswap_ulong(x); }
inline uint64_t ZvdByteSwap(uint64_t x) { return _byteswap_uint64(x); }

#elif defined(ZVD_COMPILER_GCC) || defined(ZVD_COMPILER_CLANG)
inline uint16_t ZvdByteSwap(uint16_t x) { return __builtin_bswap16(x); }
inline uint32_t ZvdByteSwap(uint32_t x) { return __builtin_bswap32(x); }
inline uint64_t ZvdByteSwap(uint64_t x) { return __builtin_bswap64(x); }

#else
// fallback (should never trigger in your setup)
inline uint16_t ZvdByteSwap(uint16_t x) 
{
    return (x << 8) | (x >> 8);
}

inline uint32_t ZvdByteSwap(uint32_t x)
{
    return (x << 24) | (x >> 24) | (0x0000FF00 & (x >> 8)) | (0x00FF0000 & (x << 8));
}

inline uint64_t ZvdByteSwap(uint64_t x)
{
    ByteAccess<uint64_t> byteAccess{x};
    for (size_t i = 0; i < 4; ++i)
    {
        std::swap(byteAccess.bytes[i], byteAccess.bytes[7 - i]);
    }
    return byteAccess.value;
}
#endif