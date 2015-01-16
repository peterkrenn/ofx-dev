//
// HTTPIOStream.h
//
// $Id: //poco/Main/template/class.h#4 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPIOStream
//
// Definition of the HTTPIOStream class.
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


#ifndef Net_HTTPIOStream_INCLUDED
#define Net_HTTPIOStream_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/UnbufferedStreamBuf.h"


namespace Poco {
namespace Net {


class HTTPClientSession;


class Net_API HTTPResponseStreamBuf: public Poco::UnbufferedStreamBuf
{
public:
	HTTPResponseStreamBuf(std::istream& istr);

	~HTTPResponseStreamBuf();

private:
	int readFromDevice();

	std::istream& _istr;
};


inline int HTTPResponseStreamBuf::readFromDevice()
{
	return _istr.get();
}


class Net_API HTTPResponseIOS: public virtual std::ios
{
public:
	HTTPResponseIOS(std::istream& istr);

	~HTTPResponseIOS();

	HTTPResponseStreamBuf* rdbuf();

protected:
	HTTPResponseStreamBuf _buf;
};


inline HTTPResponseStreamBuf* HTTPResponseIOS::rdbuf()
{
	return &_buf;
}


class Net_API HTTPResponseStream: public HTTPResponseIOS, public std::istream
{
public:
	HTTPResponseStream(std::istream& istr, HTTPClientSession* pSession);

	~HTTPResponseStream();

private:
	HTTPClientSession* _pSession;
};


} } // namespace Poco::Net


#endif // Net_HTTPIOStream_INCLUDED
