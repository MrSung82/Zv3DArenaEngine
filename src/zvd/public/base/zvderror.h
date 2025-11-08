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
// Error constants

const uint16_t kZVD_EC_MAX = 32767u;

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
