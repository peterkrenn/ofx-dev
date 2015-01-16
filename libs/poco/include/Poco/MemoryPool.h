//
// MemoryPool.h
//
// $Id: //poco/1.3/Foundation/include/Poco/MemoryPool.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  MemoryPool
//
// Definition of the MemoryPool class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Foundation_MemoryPool_INCLUDED
#define Foundation_MemoryPool_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Mutex.h"
#include <vector>
#include <cstddef>


namespace Poco {


class Foundation_API MemoryPool
	/// A simple pool for fixed-size memory blocks.
	///
	/// The main purpose of this class is to speed-up
	/// memory allocations, as well as to reduce memory
	/// fragmentation in situations where the same blocks
	/// are allocated all over again, such as in server
	/// applications.
	///
	/// All allocated blocks are retained for future use.
	/// A limit on the number of blocks can be specified.
	/// Blocks can be preallocated.
{
public:
	MemoryPool(std::size_t blockSize, int preAlloc = 0, int maxAlloc = 0);
		/// Creates a MemoryPool for blocks with the given blockSize.
		/// The number of blocks given in preAlloc are preallocated.

	~MemoryPool();

	void* get();
		/// Returns a memory block. If there are no more blocks
		/// in the pool, a new block will be allocated.
		///
		/// If maxAlloc blocks are already allocated, an
		/// OutOfMemoryException is thrown.

	void release(void* ptr);
		/// Releases a memory block and returns it to the pool.

	std::size_t blockSize() const;
		/// Returns the block size.

	int allocated() const;
		/// Returns the number of allocated blocks.

	int available() const;
		/// Returns the number of available blocks in the pool.

private:
	MemoryPool();
	MemoryPool(const MemoryPool&);
	MemoryPool& operator = (const MemoryPool&);

	enum
	{
		BLOCK_RESERVE = 128
	};

	typedef std::vector<char*> BlockVec;

	std::size_t _blockSize;
	int         _maxAlloc;
	int         _allocated;
	BlockVec    _blocks;
	FastMutex   _mutex;
};


//
// inlines
//
inline std::size_t MemoryPool::blockSize() const
{
	return _blockSize;
}


inline int MemoryPool::allocated() const
{
	return _allocated;
}


inline int MemoryPool::available() const
{
	return (int) _blocks.size();
}


} // namespace Poco


#endif // Foundation_MemoryPool_INCLUDED
