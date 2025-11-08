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
#include <atomic>


/** @brief Atomically increments an unsigned 32-bit integer value (uint32_t).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API uint32_t ZVD_STDCALL ZvdfAtomicIncrement(uint32_t& value) noexcept;

/** @brief Atomically decrements an unsigned 32-bit integer value (uint32_t).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API uint32_t ZVD_STDCALL ZvdfAtomicDecrement(uint32_t& value) noexcept;

/** @brief Atomically increments a signed 32-bit integer value (int32_t).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API int32_t ZVD_STDCALL ZvdfAtomicIncrement(int32_t& value) noexcept;

/** @brief Atomically decrements a signed 32-bit integer value (int32_t).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API int32_t ZVD_STDCALL ZvdfAtomicDecrement(int32_t& value) noexcept;

/** @brief Atomically increments an unsigned 64-bit integer value (uint64_t).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API uint64_t ZVD_STDCALL ZvdfAtomicIncrement(uint64_t& value) noexcept;

/** @brief Atomically decrements an unsigned 64-bit integer value (uint64_t).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API uint64_t ZVD_STDCALL ZvdfAtomicDecrement(uint64_t& value) noexcept;

/** @brief Atomically increments a signed 64-bit integer value (int64_t).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API int64_t ZVD_STDCALL ZvdfAtomicIncrement(int64_t& value) noexcept;

/** @brief Atomically decrements a signed 64-bit integer value (int64_t).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API int64_t ZVD_STDCALL ZvdfAtomicDecrement(int64_t& value) noexcept;

/** @brief Atomically increments an unsigned integer value (size_t).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API size_t ZVD_STDCALL ZvdfAtomicIncrementSize(size_t& value) noexcept;

/** @brief Atomically decrements an unsigned integer value (size_t).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API size_t ZVD_STDCALL ZvdfAtomicDecrementSize(size_t& value) noexcept;


/** @brief Atomically increments an unsigned 32-bit atomic integer value (std::atomic<uint32_t>).
 *  @param value Reference to the atomic value to increment.
 *  @return The new value after increment.
 */
inline ZVD_API uint32_t ZVD_STDCALL ZvdfAtomicIncrement(std::atomic<uint32_t>& value) noexcept
{
    return value.fetch_add(1, std::memory_order_seq_cst) + 1;
}

/** @brief Atomically decrements an unsigned 32-bit atomic integer value (std::atomic<uint32_t>).
 *  @param value Reference to the atomic value to decrement.
 *  @return The new value after decrement.
 */
inline ZVD_API uint32_t ZVD_STDCALL ZvdfAtomicDecrement(std::atomic<uint32_t>& value) noexcept
{
    return value.fetch_sub(1, std::memory_order_seq_cst) - 1;
}

/** @brief Atomically increments an unsigned 64-bit atomic integer value (std::atomic<uint64_t>).
 *  @param value Reference to the atomic value to increment.
 *  @return The new value after increment.
 */
inline ZVD_API uint64_t ZVD_STDCALL ZvdfAtomicIncrement(std::atomic<uint64_t>& value) noexcept
{
    return value.fetch_add(1, std::memory_order_seq_cst) + 1;
}

/** @brief Atomically decrements an unsigned 64-bit atomic integer value (std::atomic<uint64_t>).
 *  @param value Reference to the atomic value to decrement.
 *  @return The new value after decrement.
 */
inline ZVD_API uint64_t ZVD_STDCALL ZvdfAtomicDecrement(std::atomic<uint64_t>& value) noexcept
{
    return value.fetch_sub(1, std::memory_order_seq_cst) - 1;
}

/** @brief Atomically increments an unsigned atomic integer value (std::atomic<size_t>).
 *  @param value Reference to the atomic value to increment.
 *  @return The new value after increment.
 */
inline ZVD_API size_t ZVD_STDCALL ZvdfAtomicIncrementSize(std::atomic<size_t>& value) noexcept
{
    return value.fetch_add(1, std::memory_order_seq_cst) + 1;
}

/** @brief Atomically decrements an unsigned atomic integer value (std::atomic<size_t>).
 *  @param value Reference to the atomic value to decrement.
 *  @return The new value after decrement.
 */
inline ZVD_API size_t ZVD_STDCALL ZvdfAtomicDecrementSize(std::atomic<size_t>& value) noexcept
{
    return value.fetch_sub(1, std::memory_order_seq_cst) - 1;
}
