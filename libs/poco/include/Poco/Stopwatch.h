//
// Stopwatch.h
//
// $Id: //poco/1.3/Foundation/include/Poco/Stopwatch.h#2 $
//
// Library: Foundation
// Package: DateTime
// Module:  Stopwatch
//
// Definition of the Stopwatch class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Foundation_Stopwatch_INCLUDED
#define Foundation_Stopwatch_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Timestamp.h"


namespace Poco {


class Foundation_API Stopwatch
	/// A simple facility to measure time intervals
	/// with microsecond resolution.
{
public:
	Stopwatch();
	~Stopwatch();

	void start();
		/// Starts (or restarts) the stopwatch.

	void stop();
		/// Stops or pauses the stopwatch.

	void reset();
		/// Resets the stopwatch.

	void restart();
		/// Resets and starts the stopwatch.

	Timestamp::TimeDiff elapsed() const;
		/// Returns the elapsed time in microseconds
		/// since the stopwatch started.

	int elapsedSeconds() const;
		/// Returns the number of seconds elapsed
		/// since the stopwatch started.

	static Timestamp::TimeVal resolution();
		/// Returns the resolution of the stopwatch.

private:
	Stopwatch(const Stopwatch&);
	Stopwatch& operator = (const Stopwatch&);

	Timestamp           _start;
	Timestamp::TimeDiff _elapsed;
	bool                _running;
};


//
// inlines
//
inline void Stopwatch::start()
{
	if (!_running)
	{
		_start.update();
		_running = true;
	}
}


inline void Stopwatch::stop()
{
	if (_running)
	{
		Timestamp current;
		_elapsed += current - _start;
		_running = false;
	}
}


inline int Stopwatch::elapsedSeconds() const
{
	return int(elapsed()/resolution());
}


inline Timestamp::TimeVal Stopwatch::resolution()
{
	return Timestamp::resolution();
}


} // namespace Poco


#endif // Foundation_Stopwatch_INCLUDED
