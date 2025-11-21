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

#include "system/zvdmemdefs.h"


#if defined (ZVD_PLATFORM_LINUX)

#include "platform/linux/zvdmemallocposix.h"

#elif defined(ZVD_PLATFORM_WINDOWS) 

#include "platform/win/zvdmemallocwin.h"

#endif

/** @name Platform-Independent Memory Allocation Functions
* Unified platform-independent memory allocation and deallocation functions, akin to C++ standard library procedures.
*/
//@{
ZvdVoidPtr ZVD_CDECL ZvdfMalloc(size_t nBytes);
ZvdVoidPtr ZVD_CDECL ZvdfRealloc(ZvdVoidPtr pMemblockOld, size_t nOldBytes, size_t nBytes);
void ZVD_CDECL ZvdfFree(ZvdVoidPtr pMemblock);

ZvdVoidPtr ZVD_CDECL ZvdfAlignedMalloc(size_t nBytes, size_t nAlignment);
ZvdVoidPtr ZVD_CDECL ZvdfAlignedRealloc(ZvdVoidPtr pMemblockOld, size_t nOldBytes, size_t nBytes, size_t nAlignment);
void ZVD_CDECL ZvdfAlignedFree(ZvdVoidPtr pMemblock);

ZvdVoidPtr ZVD_CDECL ZvdfStackAlloc(size_t nBytes);
void ZVD_CDECL ZvdfStackFree(ZvdVoidPtr pMemblock);
//@}
