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


#include "base/zvderror.h"
#include "base/zvdassert.h"
#include "base/zvdbyteutils.h"
#include "base/zvdstaticsingleton.h"
//#include "core/base/cpplib/zvdstdstringutils.h"

#ifdef ZVD_MSVC
#include <Windows.h>
#endif

#include <new>


//-----------------------------------------------------------------------------
ZvdPackedError::ZvdPackedError()
{
	Pack(m_retVal, kZVD_ES_UNKNOWN,
		static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kUNDEFINED), 
		kZVD_EC_UNACCEPTABLE, false);
}

//-----------------------------------------------------------------------------
ZvdPackedError::ZvdPackedError(ZvdByte nStatus, ZvdByte nSource, uint16_t nCode, bool bExt)
{ 
	Pack(m_retVal, nStatus, nSource, nCode, bExt);
}

//-----------------------------------------------------------------------------
void ZvdPackedError::Pack(ZvdRetVal& retVal, ZvdByte nStatus, ZvdByte nSource, uint16_t nCode, bool bExt)
{
	ZvdSetByte(retVal, 0, nStatus);
    ZvdByte uSourceField = (nSource & kZVD_EM_SOURCEMASK) | (bExt ? (kZVD_EM_SOURCEMASKEXT & kZVD_EF_EXTLIB) : 0u);
	ZvdSetByte(retVal, 1, uSourceField);
	ZVD_ASSERT_HIGH_NOMSG(nCode <= kZVD_EC_MAX);
	ZvdSetWord(retVal, 1, nCode);
}

//-----------------------------------------------------------------------------
ZvdByte ZvdPackedError::Status() const
{
	return ZvdGetByte(m_retVal, 0);
}

//-----------------------------------------------------------------------------
ZvdByte ZvdPackedError::Source(bool& bExt) const
{
	ZvdByte nSource = ZvdGetByte(m_retVal, 1);
	bExt = (nSource & kZVD_EM_SOURCEMASKEXT) != 0u;
	return nSource & kZVD_EM_SOURCEMASK;
}

//-----------------------------------------------------------------------------
uint16_t ZvdPackedError::Code() const
{
	return ZvdGetWord(m_retVal, 1);
}

//-----------------------------------------------------------------------------
const ZvdPackedError& ZvdPackedError::Ok()
{
	static ZvdPackedError sOk(kZVD_ES_OK, 
		static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kUNDEFINED),
		kZVD_EC_UNDEFINED);
	return sOk;
}

//-----------------------------------------------------------------------------
void ZvdPackedError::SetStatusFlag(uint8_t statusFlag)
{
	ZvdSetByte(m_retVal, 0, statusFlag);
}

//-----------------------------------------------------------------------------
void ZvdPackedError::AddStatusFlag(uint8_t statusFlag)
{
	ZvdSetByte(m_retVal, 0, ZvdGetByte(m_retVal, 0) | statusFlag);
}

//-----------------------------------------------------------------------------
void ZvdPackedError::AddCrashFlag()
{
	AddStatusFlag(kZVD_EF_ABORT);
}

//-----------------------------------------------------------------------------
bool ZvdPackedError::IsOk() const
{
	return Status() == kZVD_ES_OK;
}

//-----------------------------------------------------------------------------
bool ZvdPackedError::HasErrorMarker(ZvdRetVal val)
{
	return (ZvdGetByte(val, 0) & kZVD_EF_FAIL) != 0;
}

