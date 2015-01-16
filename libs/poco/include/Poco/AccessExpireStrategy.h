//
// AccessExpireStrategy.h
//
// $Id: //poco/1.3/Foundation/include/Poco/AccessExpireStrategy.h#1 $
//
// Library: Foundation
// Package: Cache
// Module:  AccessExpireStrategy
//
// Definition of the AccessExpireStrategy class.
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


#ifndef  Foundation_AccessExpireStrategy_INCLUDED
#define  Foundation_AccessExpireStrategy_INCLUDED


#include "Poco/KeyValueArgs.h"
#include "Poco/ValidArgs.h"
#include "Poco/ExpireStrategy.h"
#include "Poco/Bugcheck.h"
#include "Poco/Timestamp.h"
#include "Poco/EventArgs.h"
#include <set>
#include <map>


namespace Poco {


template <
	class TKey,
	class TValue
>
class AccessExpireStrategy: public ExpireStrategy<TKey, TValue>
	/// An AccessExpireStrategy implements time and access based expiration of cache entries
{
public:
	AccessExpireStrategy(Timestamp::TimeDiff expireTimeInMilliSec): ExpireStrategy<TKey, TValue>(expireTimeInMilliSec)
		/// Create an expire strategy. Note that the smallest allowed caching time is 25ms.
		/// Anything lower than that is not useful with current operating systems.
	{
	}

	~AccessExpireStrategy()
	{
	}

	void onGet(const void*, const TKey& key)
	{
		// get triggers an update to the expiration time
		typename ExpireStrategy<TKey, TValue>::Iterator it = this->_keys.find(key);
		if (it != this->_keys.end())
		{
			this->_keyIndex.erase(it->second);
			Timestamp now;
			typename ExpireStrategy<TKey, TValue>::IndexIterator itIdx =
				this->_keyIndex.insert(typename ExpireStrategy<TKey, TValue>::TimeIndex::value_type(now, key));
			it->second = itIdx;
		}
	}
};


} // namespace Poco


#endif // Foundation_AccessExpireStrategy_INCLUDED
