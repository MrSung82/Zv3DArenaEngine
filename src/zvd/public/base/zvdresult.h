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

#include "base/zvderror.h"

template <typename Tag, typename... TArgs>
class ZvdResult;

#pragma pack(push, 1)
/** Stores error value and textual description. */
template <>
class ZvdResult<ZvdsDefaultTag>
{
public:
	ZvdResult(const ZvdPackedError& packedError = ZvdPackedError::Ok(), const char* pText = nullptr)
		: m_packedError{ packedError }
		, m_pText{ pText }
	{
	}

	const ZvdPackedError& GetErrorToRead() const 
	{
		return m_packedError;
	}

	ZvdPackedError& GetErrorToModify()
	{
		return m_packedError;
	}

	bool IsOk() const { return m_packedError.IsOk(); }

	const char* GetText() const { return m_pText; }
	void SetText(const char* pText) { m_pText = pText; }

	/// <summary>
	/// A factory method to create a success result object for cleaner code.
	/// </summary>
	static ZvdResult<ZvdsDefaultTag> Ok()
	{
		// It just calls the default constructor which already defaults to an OK state.
		return ZvdResult<ZvdsDefaultTag>();
	}
private:
	ZvdPackedError m_packedError;
#ifdef ZVD_64_BIT_PROCESSOR
    ZvdByte m_pad[4];
#endif
	const char* m_pText{};
};
#pragma pack(pop)



/// <summary>
/// A generic result object that wraps a ZvdPackedError.
/// This is the primary type that functions should return to indicate success or failure.
/// </summary>
/// <example><code>
/// ZvdRegularResult MyFunction()
/// {
///     if (error)
///         return ZvdRegularResult(myPackedError);
///     return ZvdRegularResult::Ok(); // or just ZvdRegularResult();
/// }
/// </code></example>
typedef ZvdResult<ZvdsDefaultTag> ZvdRegularResult;

struct ZvdResultIndexTag {};

#pragma pack(push, 1)
template <typename TIndex>
class ZvdResult <ZvdResultIndexTag, TIndex> : ZvdRegularResult
{
public:
	ZvdResult(TIndex nIndex = kZVD_INVALID_INDEX, 
		const ZvdPackedError& packedError = ZvdPackedError::Ok(),
		const char* pText = nullptr)
		: ZvdRegularResultpackedError, pText)
		, m_nIndex{ nIndex }
	{
		m_pad[0] = m_pad[1] = m_pad[2] = m_pad[3] = 0;
#ifdef ZVD_64_BIT_PROCESSOR
        m_pad[4] = m_pad[5] = m_pad[6] = m_pad[7] = 0;
#endif
	}

	TIndex Get() const { return m_nIndex; }

	TIndex m_nIndex{};
#ifdef ZVD_64_BIT_PROCESSOR
    ZvdByte m_pad[8];
#else
    ZvdByte m_pad[4];
#endif
}; 
#pragma pack(pop)

template <typename TIndex>
using ZvdIndexResult = ZvdResult <ZvdResultIndexTag, TIndex>;


struct ZvdResultPointerTag {};

#pragma pack(push, 1)
template <typename T>
struct ZvdResult<ZvdResultPointerTag, T*> : ZvdRegularResult
{
	ZvdResult(T* ptr = nullptr, 
		const ZvdPackedError& packedError = ZvdPackedError::Ok(),
		const char* pText = nullptr)
		: ZvdRegularResult(packedError, pText)
		, m_ptr{ptr}
	{
		m_pad[0] = m_pad[1] = m_pad[2] = m_pad[3];
#ifdef ZVD_64_BIT_PROCESSOR
        m_pad[4] = m_pad[5] = m_pad[6] = m_pad[7] = 0;
#endif
	}

	T* Get() { return m_ptr; }
	void Set(T* ptr) { m_ptr = ptr; }

	T* m_ptr{};
#ifdef ZVD_64_BIT_PROCESSOR
    ZvdByte m_pad[8];
#else
    ZvdByte m_pad[4];
#endif
};
#pragma pack(pop)

template <typename T>
using ZvdPointerResult = ZvdResult <ZvdResultPointerTag, T*>;