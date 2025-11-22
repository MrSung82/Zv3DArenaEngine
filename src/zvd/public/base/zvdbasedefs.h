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


//-----------------------------------------------------------------------------
// Some helper types

/// @brief Struct which used in templates programming as tag
struct ZvdsDefaultTag {};

using ZvdVoidPtr = void*;
using ZvdCVoidPtr = const void*;

using ZvdUIndex = size_t;
constexpr ZvdUIndex kZVD_INVALID_INDEX = std::numeric_limits<ZvdUIndex>::max();

using ZvdByte = uint8_t;
using ZvdTwoBytes = uint16_t;

constexpr uint8_t  kZVD_BAD_MARKER_U3 = 0x07;
constexpr uint8_t  kZVD_BAD_MARKER_U8 = 0xFF;
constexpr uint16_t kZVD_BAD_MARKER_U16 = 0xFFFF;
constexpr uint32_t kZVD_BAD_MARKER_U32 = 0xFFFFFFFFu;


#define ZVD_MAKE_BIT_FLAG_VALUE(idxStartBit, nValue) ((nValue)<<(idxStartBit))