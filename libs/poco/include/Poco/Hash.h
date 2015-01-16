//
// Hash.h
//
// $Id: //poco/1.3/Foundation/include/Poco/Hash.h#1 $
//
// Library: Foundation
// Package: Hashing
// Module:  Hash
//
// Definition of the Hash class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_Hash_INCLUDED
#define Foundation_Hash_INCLUDED


#include "Poco/Foundation.h"
#include <cstddef>


namespace Poco {


template <class T>
struct Hash
	/// A generic hash function.
{
	std::size_t operator () (T value) const
		/// Returns the hash for the given value.
	{
		return hash(value);
	}
};


std::size_t Foundation_API hash(Int8 n);
std::size_t Foundation_API hash(UInt8 n);
std::size_t Foundation_API hash(Int16 n);
std::size_t Foundation_API hash(UInt16 n);
std::size_t Foundation_API hash(Int32 n);
std::size_t Foundation_API hash(UInt32 n);
std::size_t Foundation_API hash(Int64 n);
std::size_t Foundation_API hash(UInt64 n);
std::size_t Foundation_API hash(const std::string& str);


//
// inlines
//
inline std::size_t hash(Int8 n)
{
	return static_cast<std::size_t>(n)*2654435761U;
}


inline std::size_t hash(UInt8 n)
{
	return static_cast<std::size_t>(n)*2654435761U;
}


inline std::size_t hash(Int16 n)
{
	return static_cast<std::size_t>(n)*2654435761U;
}


inline std::size_t hash(UInt16 n)
{
	return static_cast<std::size_t>(n)*2654435761U;
}


inline std::size_t hash(Int32 n)
{
	return static_cast<std::size_t>(n)*2654435761U;
}


inline std::size_t hash(UInt32 n)
{
	return static_cast<std::size_t>(n)*2654435761U;
}


inline std::size_t hash(Int64 n)
{
	return static_cast<std::size_t>(n)*2654435761U;
}


inline std::size_t hash(UInt64 n)
{
	return static_cast<std::size_t>(n)*2654435761U;
}


} // namespace Poco


#endif // Foundation_Hash_INCLUDED
