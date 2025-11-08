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


template <typename TRetVal, typename T1, typename T2>
TRetVal ZvdfMin(const T1& a, const T2& b)
{
	return (a < b) ? a : b;
}

template <typename T>
T ZvdfMin(const T& a, const T& b)
{
	return (a < b) ? a : b;
}

template <typename T>
T ZvdFastDivideBy2(T x)
{
	return x >> 1;
}

template <typename T>
T ZvdFastDivideBy4(T x)
{
	return x >> 2;
}

template <typename T>
T ZvdFastDivideBy8(T x)
{
	return x >> 3;
}

template <typename T>
T ZvdFastDivideBy16(T x)
{
	return x >> 4;
}