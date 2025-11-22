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

//-----------------------------------------------------------------------------
// Error types

// Use it to return from functions.
typedef uint32_t ZvdRetVal;

/// @brief Report level
enum ZvdeReportLevel
{
	kZVD_INFO,
	kZVD_WARN,
	kZVD_ERROR,
	kZVD_TRACE,
	kZVD_FATAL
};

#pragma pack(push, 1)
//-----------------------------------------------------------------------------
/// <summary>
/// A compact, 32-bit error object that packs status, source, and a specific code.
/// This is the core error type used throughout the engine instead of exceptions.
/// It is designed to be returned by value from functions.
///
/// The 32-bit value is structured as follows:
/// - Byte 0: Status flags (e.g., success, error, fatal). See ZvdeErrorControlBits.
/// - Byte 1: Source ID of the error (e.g., renderer, physics). See ZvdeErrorSource.
/// - Word 1 (Bytes 2-3): Specific error code. See ZvdeErrorCodes.
/// </summary>
/// <example><code>
/// ZvdPackedError error(kZVD_ES_ERROR, kZVD_ESRC_CORE_DARRAY, kZVD_EC_OUT_OF_RANGE);
/// </code></example>
class ZvdPackedError
{
public:
	ZvdPackedError();
	ZvdPackedError(ZvdRetVal retVal) : m_retVal{ retVal } {}
	ZvdPackedError(ZvdByte nStatus, ZvdByte nSource, uint16_t nCode, bool bExt = false);
	ZvdPackedError(const ZvdPackedError& oth)
		: m_retVal(oth.RetVal())
	{

	}

	// setters
	void SetStatusFlag(uint8_t statusFlag);
	void AddStatusFlag(uint8_t statusFlag);
	void AddCrashFlag();

	// getters
	ZvdRetVal RetVal() const { return m_retVal; }
	ZvdByte Status() const;
	ZvdByte Source(bool& bExt) const;
	uint16_t Code() const;

	bool IsOk() const;
	static const ZvdPackedError& Ok();
	static bool HasErrorMarker(ZvdRetVal val);
private:
	static void Pack(ZvdRetVal& retVal, ZvdByte nStatus, ZvdByte nSource, uint16_t nCode, bool bExt);
	ZvdRetVal m_retVal;
};
#pragma pack(pop)

//=============================================================================
// Error format

//-----------------------------------------------------------------------------
/// <summary>
/// A bitmask of flags that define the status and severity of an error.
/// This is packed into the first byte of a ZvdPackedError.
/// Flags can be combined using the bitwise OR operator.
/// Error codes must be interpreted
/// in context of local operation.
/// "E" means error. "EF" means error flag.
/// </summary>
/// <example><code>
/// ZvdByte status = kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC;
/// </code></example>
enum ZvdeErrorControlBits
{
	// 0 byte
	//

	/// no error (success)
	kZVD_EF_SUCCESS = 0,
	kZVD_EF_STOP = 1,
	/// error marker
	kZVD_EF_FAIL = (1 << 1),
	/// crash, exception - means that program can not be continued
	kZVD_EF_CRASH = (1 << 2),
	/// no resource
	kZVD_EF_NO_RESOURCE = (1 << 3),
	/// bad resource
	kZVD_EF_BAD_RESOURCE = (1 << 4),
	/// logic error
	kZVD_EF_BAD_LOGIC = (1 << 5),
	/// special marker - dependent flag
	kZVD_EF_SPECIAL = (1 << 6),

	/// big endian marker (7th & 31th bits of return value are always zero on LE-machines)
	kZVD_EF_BE = (1 << 7),

	kZVD_EF_UNKNOWN = kZVD_EF_STOP | kZVD_EF_FAIL | kZVD_EF_SPECIAL,
	kZVD_EF_CANCEL = kZVD_EF_STOP | kZVD_EF_SPECIAL,
	kZVD_EF_FATAL = kZVD_EF_FAIL | kZVD_EF_SPECIAL,
	///  Abort program. Error is in design.
	kZVD_EF_ABORT = kZVD_EF_FATAL | kZVD_EF_CRASH,
	/// error was raised at external code (in 1st byte if begin since 0)
	kZVD_EF_EXTLIB = (1 << 7)
};

// Error byte main values
//------------------------

/// nothing known about some error case
const ZvdByte kZVD_ES_UNKNOWN = kZVD_EF_UNKNOWN;

/// operation succeeded
const ZvdByte kZVD_ES_OK = kZVD_EF_SUCCESS;

/// operation succeeded (did nothing)
const ZvdByte kZVD_ES_NOTHING = kZVD_EF_STOP;

/// operation failed
const ZvdByte kZVD_ES_ERROR = kZVD_EF_FAIL;

/// operation canceled by caller (user)
const ZvdByte kZVD_ES_CANCEL = kZVD_EF_CANCEL;

/// operation failed and its a fatal
const ZvdByte kZVD_ES_FATAL = kZVD_EF_FATAL;


//-----------------------------------------------------------------------------
// Error constants and codes

/// @brief Error source mask
const ZvdByte kZVD_EM_SOURCEMASK = 0x7F;
/// @brief External error source mask
const ZvdByte kZVD_EM_SOURCEMASKEXT = 0x80;

/// Error code limits
const uint16_t kZVD_EC_MAX = 32767u;


//-----------------------------------------------------------------------------
/// <summary>
/// An enumeration of modules or subsystems where an error can originate.
/// The value is packed into the second byte of a ZvdPackedError.
/// The valid range for custom sources is from 1 to 127.
/// </summary>
enum class ZvdeErrorSource : uint8_t
{
	kUNDEFINED = 0, // if no error, there is no source
	kCORE_MEMORY,
	kCORE_ARRAYCONTAINER,
	kMAX = 127
};


/// <summary>
/// Specific error codes for different situations.
/// This is packed into the last two bytes of a ZvdPackedError.
/// </summary>
enum ZvdeErrorCodes
{
	kZVD_EC_UNKNOWN = kZVD_EC_MAX - 1,
	kZVD_EC_UNDEFINED = 0,

	/// <summary>
	/// A logic error indicating that an allegedly unreachable code path was executed.
	/// </summary>
	/// <remarks>
	/// This error should be used in places that are not supposed to be reached under
	/// any normal circumstances, such as the default case of a switch statement
	/// that is expected to handle all possible enum values.
	/// Reaching this code signals a critical flaw in program logic.
	/// </remarks>
	/// <example><code>
	/// return ZvdRegularResult(ZvdPackedError(kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC,
	///			static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY),
	///			kZVD_EC_UNACCEPTABLE));
	/// </code></example>
	kZVD_EC_UNACCEPTABLE,
	kZVD_EC_NOIMPL,
	kZVD_EC_NOPRECOND,
	/// has no instance or instance can not be created
	kZVD_EC_NOINSTANCE,
	/// instance can not be created on stack
	kZVD_EC_NOSTACKOBJECT,
	/// allocator instance can not be created on stack
	kZVD_EC_NOSTACKALLOCATOR,
	/// <summary>
	/// An operation would exceed the maximum theoretical size of a container.
	/// This is the error-code equivalent of the std::length_error exception.
	/// It is typically returned when a requested size (e.g., in reserve() or resize())
	/// is greater than the container's max_size().
	/// </summary>
	kZVD_EC_LENGTHERROR,
	kZVD_EC_CONSTRUCTEXCEPTION,
};
