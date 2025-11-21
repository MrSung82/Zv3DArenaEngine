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
Purpose: blank file for implementations (.cpp files).

----------------------
 For developers notes
----------------------

*/

#include "base/zvdassert.h"
#include "base/zvderror.h"
#include "system/zvdmemdefs.h"
#include "platform/win/zvdmemallocwin.h"

#include <malloc.h>

#if defined(ZVD_PLATFORM_WINDOWS)

Zvdfpt_malloc Zvdfp_malloc = std::malloc;
Zvdfpt_realloc Zvdfp_realloc = std::realloc;
Zvdfpt_free Zvdfp_free = std::free;

Zvdfpt_aligned_malloc Zvdfp_aligned_malloc = _aligned_malloc;
Zvdfpt_aligned_realloc Zvdfp_aligned_realloc = _aligned_realloc;
Zvdfpt_aligned_free Zvdfp_aligned_free = _aligned_free;

#ifdef ZVD_DEBUG
Zvdfpt_malloca Zvdfp_malloca = malloc;
Zvdfpt_freea Zvdfp_freea = free;
#else
Zvdfpt_malloca Zvdfp_malloca = _malloca;
Zvdfpt_freea Zvdfp_freea = _freea;
#endif

//-----------------------------------------------------------------------------
ZvdVoidPtr ZVD_CDECL ZvdfMalloc(size_t nBytes)
{
    ZvdVoidPtr pResultMem = nullptr;

    pResultMem = Zvdfp_malloc(nBytes);

    return pResultMem;
}

//-----------------------------------------------------------------------------
ZvdVoidPtr ZVD_CDECL ZvdfRealloc(ZvdVoidPtr pMemblockOld, size_t nOldBytes, size_t nBytes)
{
    ZvdVoidPtr pResultMem = nullptr;

    ZVD_UNUSED(nOldBytes);
    pResultMem = Zvdfp_realloc(pMemblockOld, nBytes);

    return pResultMem;
}

//-----------------------------------------------------------------------------
void ZVD_CDECL ZvdfFree(ZvdVoidPtr pMemblock)
{
    if (!pMemblock)
        return;

    Zvdfp_free(pMemblock);

}


//-----------------------------------------------------------------------------
ZvdVoidPtr ZVD_CDECL ZvdfAlignedMalloc(size_t nBytes, size_t nAlignment)
{
    ZvdVoidPtr pResultMem = nullptr;

    pResultMem = Zvdfp_aligned_malloc(nBytes, nAlignment);

    return pResultMem;
}

//-----------------------------------------------------------------------------
ZvdVoidPtr ZVD_CDECL ZvdfAlignedRealloc(ZvdVoidPtr pMemblockOld, size_t nOldBytes, size_t nBytes, size_t nAlignment)
{
    ZvdVoidPtr pResultMem = nullptr;

    ZVD_UNUSED(nOldBytes);
    pResultMem = Zvdfp_aligned_realloc(pMemblockOld, nBytes, nAlignment);

    return pResultMem;
}

//-----------------------------------------------------------------------------
void ZVD_CDECL ZvdfAlignedFree(ZvdVoidPtr pMemblock)
{
    if (!pMemblock)
        return;

    Zvdfp_aligned_free(pMemblock);

}

//-----------------------------------------------------------------------------
ZvdVoidPtr ZVD_CDECL ZvdfStackAlloc(size_t nBytes)
{
    ZvdVoidPtr pResultMem = nullptr;

    pResultMem = Zvdfp_malloca(nBytes);

    return pResultMem;
}

//----------------------------------------------------------------------------- 
void ZVD_CDECL ZvdfStackFree(ZvdVoidPtr pMemblock)
{
    if (!pMemblock)
        return;

    Zvdfp_freea(pMemblock);
}

#endif // eof Windows platform