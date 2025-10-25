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

//=============================================================================
// Compiler detection and related helpers.
//=============================================================================


//-----------------------------------------------------------------------------
// Compilers family detection

#if defined(_MSC_VER)
//**********************************************************
// Microsoft Visual C++ compiler related further detections
//**********************************************************
#	define ZVD_COMPILER_MSVC 1
#   define ZVD_COMPILER_NAMEA "Microsoft Visual C++"
#   define ZVD_COMPILER_NAMEW L"Microsoft Visual C++"

//-----------------------------------------------------------------------------
// Microsoft compiler version

#define ZVD_VISUAL_STUDIO_6_x_0					1200
#define ZVD_VISUAL_STUDIO_NET_2002_7_x_0		1300
#define ZVD_VISUAL_STUDIO_NET_2003_7_x_1		1310
#define ZVD_VISUAL_STUDIO_2005_8_x_0			1400
#define ZVD_VISUAL_STUDIO_2008_9_x_0			1500
#define ZVD_VISUAL_STUDIO_2010_10_x_0			1600
#define ZVD_VISUAL_STUDIO_2012_11_x_0			1700
#define ZVD_VISUAL_STUDIO_2013_12_x_0			1800
#define ZVD_VISUAL_STUDIO_2015_14_x_0			1900
#define ZVD_VISUAL_STUDIO_2017_RTW_15_x_0		1910
#define ZVD_VISUAL_STUDIO_2017_15_x_3			1911
#define ZVD_VISUAL_STUDIO_2017_15_x_5			1912
#define ZVD_VISUAL_STUDIO_2017_15_x_6			1913
#define ZVD_VISUAL_STUDIO_2017_15_x_7			1914
#define ZVD_VISUAL_STUDIO_2017_15_x_8			1915
#define ZVD_VISUAL_STUDIO_2017_15_x_9			1916
#define ZVD_VISUAL_STUDIO_2019_RTW_16_x_0		1920
#define ZVD_VISUAL_STUDIO_2019_16_x_1			1921
#define ZVD_VISUAL_STUDIO_2019_16_x_2			1922
#define ZVD_VISUAL_STUDIO_2019_16_x_3			1923
#define ZVD_VISUAL_STUDIO_2019_16_x_4			1924
#define ZVD_VISUAL_STUDIO_2019_16_x_5			1925
#define ZVD_VISUAL_STUDIO_2019_16_x_6			1926
#define ZVD_VISUAL_STUDIO_2019_16_x_7			1927
#define ZVD_VISUAL_STUDIO_2019_16_x_8_16_x_9	1928
#define ZVD_VISUAL_STUDIO_2019_16_x_10_16_x_11	1929
#define ZVD_VISUAL_STUDIO_2022_RTW_17_x_0		1930

#define ZVD_COMPILER_MSVC_VERSION _MSC_VER


/** Macro to get MSVC version.
*/

#   define ZVD_COMPILER_MSVC_VERSION_OR_HIGHER(ver) (ZVD_COMPILER_MSVC_VERSION >= ver)
#   define ZVD_COMPILER_MSVC_VERSION_LESS_THAN(ver) (ZVD_COMPILER_MSVC_VERSION < ver)

#   if defined ZVD_CFG_DISABLE_WARN4996
#       pragma warning(disable:4996)
#   endif
#   pragma warning(disable:26495)


#	if (ZVD_COMPILER_MSVC_VERSION_LESS_THAN(ZVD_CFG_MIN_MSVC_VER))
#		error "unsupported VC version -- its too old; you need VC 2022 (17.0) or higher"
#	endif



#elif defined(__GNUC__)
//*******************************************
// GNU C compiler related further detections
//*******************************************
#	define ZVD_COMPILER_GCC 1
#   define ZVD_COMPILER_NAMEA "GCC"
#   define ZVD_COMPILER_NAMEW L"GCC"

#   define ZVD_GCC_VER_PACKED_TO_INT(major,minor,patch) \
    (major * 10000 + minor * 100 + patch)

#   define ZVD_GCC_CUR_VER_PACKED_TO_INT \
    ZVD_GCC_VER_PACKED_TO_INT(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)

/**  GCC version helper

Usage
    @code
// Test for GCC >= 8.2.1
#if ZVD_GCC_VER_LESS(8,2,1)
#error "too old version of gcc"
#endif
    @endcode

*/
#   define ZVD_GCC_VER_LESS(major,minor,patch) \
    (ZVD_GCC_CUR_VER_PACKED_TO_INT < ZVD_GCC_VER_PACKED_TO_INT(major,minor,patch))


/** Macro to get gcc version.
    @code
// Test for GCC >= 8.1.0
#if ZVD_COMPILER_GNUC_VERSION >= 80100
    @endcode
*/
#   define ZVD_COMPILER_GNUC_VERSION ZVD_GCC_CUR_VER_PACKED_TO_INT

/** Macro to check if gcc version is higher than given one.
    @code
// Test for GCC >= 8.1.0
#if ZVD_COMPILER_GNUC_VERSION_OR_HIGHER(8,1,0)
    @endcode
*/
#   define ZVD_COMPILER_GNUC_VERSION_OR_HIGHER(major,minor,patchlevel) \
    (!ZVD_GCC_VER_LESS(major,minor,patchlevel))


#	if !ZVD_COMPILER_GNUC_VERSION_OR_HIGHER(ZVD_CFG_MIN_GNUC_MAJOR,\
		ZVD_CFG_MIN_GNUC_MINOR,ZVD_CFG_MIN_GNUC_PATCHLEVEL)
#		error "too old gcc version"
#	endif



#elif defined(__clang__)
#   define ZVD_COMPILER_CLANG 1
#   define ZVD_COMPILER_NAMEA "clang"
#   define ZVD_COMPILER_NAMEW L"clang"
#   define ZVD_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)



#else
#	error "No supported compiler was found."

#endif // compiler detection



//-----------------------------------------------------------------------------
// C++ standard detection

// In Visual Studio add:
// /Zc:__cplusplus
// in project command line additional parameters field
// https://learn.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-170
#if (__cplusplus==202302L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP23 __cplusplus
#   define ZVD_CPP20 202002L
#   define ZVD_CPP17 201703L
#   define ZVD_CPP14 201402L
#   define ZVD_CPP11 201103L
#   define ZVD_CPP03 199711L
#	pragma message("C++23")

#elif(__cplusplus == 202002L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP20 __cplusplus
#   define ZVD_CPP17 201703L
#   define ZVD_CPP14 201402L
#   define ZVD_CPP11 201103L
#   define ZVD_CPP03 199711L
#	pragma message("C++20")

#elif(__cplusplus == 201703L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP17 __cplusplus
#   define ZVD_CPP14 201402L
#   define ZVD_CPP11 201103L
#   define ZVD_CPP03 199711L
#	pragma message("C++17")

#elif(__cplusplus == 201402L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP14 __cplusplus
#   define ZVD_CPP11 201103L
#   define ZVD_CPP03 199711L
#	pragma message("C++14")

#elif(__cplusplus == 201103L)
#   define ZVD_CPP11 __cplusplus
#   define ZVD_CPP03 199711L
#	pragma message("C++11")

#elif(__cplusplus == 199711L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP03 __cplusplus
#	pragma message("C++98")

#else
#   error "No any standart of C++ detected. You can comment this line for your own risk!"
//#define ZVD_CPP __cplusplus
//#define ZVD_CPP98 // 98/03 ?

#endif // C++ standard detection end

#ifndef ZVD_CPP
#   error "No required C++ standard is supported by current compiler!"
#endif

#ifndef ZVD_CPP17
#   error "C++17 or later required. Use /std:c++17 or -std=c++17 and /Zc:__cplusplus on MSVC."
#endif


// force inline
#if defined(ZVD_COMPILER_MSVC)
#   define ZVD_FORCE_INLINE __forceinline
#elif defined(ZVD_COMPILER_GCC) || defined(ZVD_COMPILER_CLANG)
#   define ZVD_FORCE_INLINE inline __attribute__((always_inline))
#else
#   define ZVD_FORCE_INLINE inline
#endif


#if defined(ZVD_COMPILER_GCC) || defined(ZVD_COMPILER_CLANG)
#   define ZVD_LIKELY(x)   __builtin_expect(!!(x), 1)
#   define ZVD_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#   define ZVD_LIKELY(x)   (x)
#   define ZVD_UNLIKELY(x) (x)
#endif


#if defined(__has_include)
#   define ZVD_HAS_INCLUDE(x) __has_include(x)
#else
#   define ZVD_HAS_INCLUDE(x) 0
#endif


// warning on/off
#if defined(ZVD_COMPILER_MSVC)
#   define ZVD_DISABLE_WARNING(w) __pragma(warning(push)) __pragma(warning(disable:w))
#   define ZVD_RESTORE_WARNING()  __pragma(warning(pop))
#elif defined(ZVD_COMPILER_GCC) || defined(ZVD_COMPILER_CLANG)
#   define ZVD_DISABLE_WARNING(w) _Pragma("GCC diagnostic push") _Pragma(#w)
#   define ZVD_RESTORE_WARNING()  _Pragma("GCC diagnostic pop")
#else
#   define ZVD_DISABLE_WARNING(w)
#   define ZVD_RESTORE_WARNING()
#endif


#define ZVD_UNUSED(x) ((void)(x))