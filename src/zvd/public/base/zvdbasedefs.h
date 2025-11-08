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

#include "zvdconfig.h"

#ifndef __cplusplus
#error "This project is for C++ language only!"
#endif



//-----------------------------------------------------------------------------
// Compilers family detection

#include "base/zvdcompiler.h"
#include "base/zvdplatform.h"

#if defined(ZVD_COMPILER_MSVC) 
#	ifdef _DEBUG
#		ifndef ZVD_DEBUG
#			define ZVD_DEBUG
#		endif
#	endif

#endif


#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <limits>
#include <type_traits>


// Verifies that a supported platform is detected.
#if !(defined(ZVD_PLATFORM_WINDOWS) || defined(ZVD_PLATFORM_LINUX))
#	error "For now windows and linux platforms are supported only."
#endif


//-----------------------------------------------------------------------------
// API macros, Library type
#if defined(ZVD_PLATFORM_WINDOWS)

#ifdef ZVD_DLL_EXPORTS
#	define ZVD_API __declspec(dllexport)
#elif ZVD_DLL_IMPORTS
#	define ZVD_API __declspec(dllimport)
#else
// static library use this
#	define ZVD_API 
#endif

// Used for dll exporting and importing functions
#define  ZVD_DLL_EXPORTED_FUNCLIST_BEGIN	extern "C" { 
#define  ZVD_DLL_EXPORTED_FUNCLIST_END }


#elif defined ZVD_PLATFORM_LINUX

#ifdef ZVD_DLL_EXPORTS
#	define ZVD_API __attribute__((visibility("default")))
#else
#	define ZVD_API
#endif

// Used for dll exporting and importing functions
#define  ZVD_DLL_EXPORTED_FUNCLIST_BEGIN	extern "C" { 
#define  ZVD_DLL_EXPORTED_FUNCLIST_END }  

#else

#error "Unsupported Platform."

#endif


// Used for standard calling conventions
#ifdef ZVD_PLATFORM_WINDOWS
#	define  ZVD_STDCALL			__stdcall
#	define	ZVD_CDECL			__cdecl
#	define  ZVD_FASTCALL		__fastcall
#	define  ZVD_CALLCONV		ZVD_CDECL

#elif defined(ZVD_PLATFORM_LINUX)
#	define ZVD_STDCALL
#	define ZVD_CDECL
#	define ZVD_FASTCALL
#	define ZVD_CALLCONV		   

#else
#	error "Unknown platform"
#endif


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
} // eof zvd


template<typename T>
constexpr uint8_t ZvdGetByte(T var, size_t idx) noexcept
{
    return ByteAccess<T>{var}.bytes[idx];
    
}

template<typename T>
constexpr void ZvdSetByte(T& var, size_t idx, uint8_t uByteVal) noexcept
{
    ByteAccess<T> byteAccess{ var };
    byteAccess.bytes[idx] = uByteVal;
    var = byteAccess.value;
}


namespace zvd
{
    // ------------------------------------------------------------------------
    // Get / set byte at index (0 = LSB)
    // ------------------------------------------------------------------------

    template<typename T>
    constexpr uint8_t GetByte(T var, size_t idx) noexcept 
    {
        return ZvdGetByte(var, idx);
    }

    template<typename T>
    constexpr void SetByte(T& var, size_t idx, uint8_t uByteVal) noexcept 
    {
        ZvdSetByte(var, idx, uByteVal);
    }

    // ------------------------------------------------------------------------
    // High/Low helpers (for common types)
    // ------------------------------------------------------------------------

    inline constexpr uint8_t LoByte(uint16_t v) noexcept { return static_cast<uint8_t>(v); }
    inline constexpr uint8_t HiByte(uint16_t v) noexcept { return static_cast<uint8_t>(v >> 8); }

    inline constexpr uint16_t LoWord(uint32_t v) noexcept { return static_cast<uint16_t>(v); }
    inline constexpr uint16_t HiWord(uint32_t v) noexcept { return static_cast<uint16_t>(v >> 16); }

    inline constexpr uint32_t LoDword(uint64_t v) noexcept { return static_cast<uint32_t>(v); }
    inline constexpr uint32_t HiDword(uint64_t v) noexcept { return static_cast<uint32_t>(v >> 32); }

    // ------------------------------------------------------------------------
    // Modifier classes (type-safe, no macros)
    // ------------------------------------------------------------------------

    template<typename T>
    class ByteModifier 
    {
        T& varRef;
    public:
        explicit ByteModifier(T& value) : varRef(value) {}
        uint8_t Get(size_t idx) const { return GetByte(varRef, idx); }
        void Set(size_t idx, uint8_t uByteVal) { SetByte(varRef, idx, uByteVal); }
    };

    template<typename T>
    class WordModifier 
    {
        T& varRef;
    public:
        explicit WordModifier(T& value) : varRef(value) {}
        uint16_t Get(size_t idx) const { return GetByte(static_cast<uint16_t>(varRef >> (idx * 16)), 0); }
        void Set(size_t idx, uint16_t uWordVal) 
        {
            ByteAccess<T> byteAccess{ varRef };
            *reinterpret_cast<uint16_t*>(&byteAccess.bytes[idx * sizeof(uint16_t)]) = uWordVal;
            varRef = byteAccess.value;
        }
    };

} // namespace zvd



using ZvdUIndex = size_t;
constexpr ZvdUIndex kZVD_INVALID_INDEX = std::numeric_limits<ZvdUIndex>::max();

constexpr uint8_t  kZVD_BAD_MARKER_U3 = 0x07;
constexpr uint8_t  kZVD_BAD_MARKER_U8 = 0xFF;
constexpr uint16_t kZVD_BAD_MARKER_U16 = 0xFFFF;
constexpr uint32_t kZVD_BAD_MARKER_U32 = 0xFFFFFFFFu;


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

namespace zvd 
{
    inline uint16_t ByteSwap(uint16_t x) { return ZvdByteSwap(x); }
    inline uint32_t ByteSwap(uint32_t x) { return ZvdByteSwap(x); }
    inline uint64_t ByteSwap(uint64_t x) { return ZvdByteSwap(x); }

} // namespace zvd


//-----------------------------------------------------------------------------
// Widen predefined macro and stringification support
#define ZVD_WIDECHAR(x)          ZVD_WIDECHAR_(x)
#define ZVD_WIDECHAR_(x)         L ## x
#define ZVD_NARROWCHAR(x)        x

#define ZVD_STRINGIFY_IMPL(x, t)     ZVD_STRINGIFY_IMPL_(x, t)
#define ZVD_STRINGIFY_IMPL_(x, t)    t(#x)

#define ZVD_FILE_AND_LINE_(t)  t(__FILE__) t("[") ZVD_STRINGIFY_IMPL(__LINE__, t) t("]")

#ifdef ZVD_DEBUG_CHARTYPE_WIDE
#   define ZVD_FILE_AND_LINE       ZVD_FILE_AND_LINE_(ZVD_WIDECHAR)
#   define ZVD_DEBUG_STRINGIFY(x)  ZVD_STRINGIFY_IMPL(x,ZVD_WIDECHAR)
#else
#   define ZVD_FILE_AND_LINE       ZVD_FILE_AND_LINE_(ZVD_NARROWCHAR)
#   define ZVD_DEBUG_STRINGIFY(x)  ZVD_STRINGIFY_IMPL(x,ZVD_NARROWCHAR)
#endif

#define ZVD_STRINGIFY(x)  ZVD_STRINGIFY_IMPL(x,ZVD_NARROWCHAR)
#define ZVD_STRINGIFY_W(x)  ZVD_STRINGIFY_IMPL(x,ZVD_WIDECHAR)


#ifdef ZVD_PLATFORM_WINDOWS

/** ZVD_T(s) - Windows - specific macro to handle ANSI / Unicode string literals.
* Expands to L"..." if UNICODE is defined (wide string), otherwise to "..." (narrow string).
* Only available on Windows, as Linux uses UTF-8 narrow strings exclusively.
*/
#   ifdef UNICODE
#       define ZVD_T(s)    ZVD_WIDECHAR(s)
#   else
#       define ZVD_T(s)    ZVD_NARROWCHAR(s)
#   endif

#endif