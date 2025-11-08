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


/**
 Memory allocation flags (bitfield)
 */
class ZVD_API ZvdcMemFlags
{
public:

    enum Bits
    {
        kNOFLAGS = 0x00000000,

        /// No requirements or hints set (default)
        kNO_REQ_OR_HINT = ZVD_MAKE_BIT_FLAG_VALUE(0, 0x00),

        /** Bit 0: 1 = strict requirement, 0 = optional hint */
        kHINT = ZVD_MAKE_BIT_FLAG_VALUE(0, 0x01),

        /// Lifetime flags (bits 1-3)
        kLIFETIME_TEMP = ZVD_MAKE_BIT_FLAG_VALUE(1, 0),  ///< Short-term operations (transient data)
        kLIFETIME_FRAME = ZVD_MAKE_BIT_FLAG_VALUE(1, 1),  ///< Valid only during current frame
        kLIFETIME_EVENT = ZVD_MAKE_BIT_FLAG_VALUE(1, 2),  ///< Tied to game event (e.g. explosion)
        kLIFETIME_LEVEL = ZVD_MAKE_BIT_FLAG_VALUE(1, 3),  ///< Persists until level unload
        kLIFETIME_SCENE = ZVD_MAKE_BIT_FLAG_VALUE(1, 4),  ///< Valid across multiple levels
        kLIFETIME_SESSION = ZVD_MAKE_BIT_FLAG_VALUE(1, 5),  ///< Persists for game session
        kLIFETIME_APP = ZVD_MAKE_BIT_FLAG_VALUE(1, 6),  ///< Until app termination

        /// Bitmask for lifetime flags (bits 1-3)
        kLIFETIME_MASK = 0x0E  ///< Binary 00001110
    };

    inline ZvdcMemFlags();
    inline ZvdcMemFlags(Bits eValue);

protected:
    // The flags storage
    Bits m_nValue;
};


//-----------------------------------------------------------------------------
inline ZvdcMemFlags::ZvdcMemFlags()
{
    m_nValue = kNOFLAGS;
}

//-----------------------------------------------------------------------------
inline ZvdcMemFlags::ZvdcMemFlags(Bits nValue)
{
    m_nValue = nValue;
}