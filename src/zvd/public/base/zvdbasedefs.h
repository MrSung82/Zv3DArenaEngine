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

    // ------------------------------------------------------------------------
    // Get / set byte at index (0 = LSB)
    // ------------------------------------------------------------------------

    template<typename T>
    constexpr uint8_t GetByte(T value, size_t idx) noexcept 
    {
        return ByteAccess<T>{value}.bytes[idx];
    }

    template<typename T>
    constexpr void SetByte(T& value, size_t idx, uint8_t byte) noexcept 
    {
        ByteAccess<T> access{ value };
        access.bytes[idx] = byte;
        value = access.value;
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
    class ByteModifier {
        T& ref;
    public:
        explicit ByteModifier(T& value) : ref(value) {}
        uint8_t get(size_t idx) const { return GetByte(ref, idx); }
        void set(size_t idx, uint8_t b) { SetByte(ref, idx, b); }
    };

    template<typename T>
    class WordModifier {
        T& ref;
    public:
        explicit WordModifier(T& value) : ref(value) {}
        uint16_t get(size_t idx) const { return GetByte(static_cast<uint16_t>(ref >> (idx * 16)), 0); }
        void set(size_t idx, uint16_t w) 
        {
            ByteAccess<T> access{ ref };
            *reinterpret_cast<uint16_t*>(&access.bytes[idx * sizeof(uint16_t)]) = w;
            ref = access.value;
        }
    };

} // namespace zvd

using ZvdUIndex = size_t;
constexpr ZvdUIndex kZVD_INVALID_INDEX = std::numeric_limits<ZvdUIndex>::max();

constexpr uint8_t  kZVD_BAD_MARKER_U3 = 0x07;
constexpr uint8_t  kZVD_BAD_MARKER_U8 = 0xFF;
constexpr uint16_t kZVD_BAD_MARKER_U16 = 0xFFFF;
constexpr uint32_t kZVD_BAD_MARKER_U32 = 0xFFFFFFFFu;



namespace zvd 
{

#if defined(ZVD_COMPILER_MSVC)
    inline uint16_t byteswap(uint16_t x) { return _byteswap_ushort(x); }
    inline uint32_t byteswap(uint32_t x) { return _byteswap_ulong(x); }
    inline uint64_t byteswap(uint64_t x) { return _byteswap_uint64(x); }

#elif defined(ZVD_COMPILER__GNUC) || defined(ZVD_COMPILER_CLANG)
    inline uint16_t byteswap(uint16_t x) { return __builtin_bswap16(x); }
    inline uint32_t byteswap(uint32_t x) { return __builtin_bswap32(x); }
    inline uint64_t byteswap(uint64_t x) { return __builtin_bswap64(x); }

#else
    // fallback (should never trigger in your setup)
    inline uint16_t byteswap(uint16_t x) {
        return (x << 8) | (x >> 8);
    }
#endif

} // namespace zvd


#ifdef ZVD_PLATFORM_WINDOWS

/** ZVD_T(s) - Windows - specific macro to handle ANSI / Unicode string literals.
* Expands to L"..." if UNICODE is defined (wide string), otherwise to "..." (narrow string).
* Only available on Windows, as Linux uses UTF-8 narrow strings exclusively.
*/ 
#   ifdef UNICODE
#       define ZVD_T(s)    L##s
#   else
#       define ZVD_T(s)    s
#   endif

#endif