//
// MessageHeader.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/MessageHeader.h#1 $
//
// Library: Net
// Package: Messages
// Module:  MessageHeader
//
// Definition of the MessageHeader class.
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


#ifndef Net_MessageHeader_INCLUDED
#define Net_MessageHeader_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/NameValueCollection.h"
#include <ostream>
#include <istream>
#include <vector>


namespace Poco {
namespace Net {


class Net_API MessageHeader: public NameValueCollection
	/// A collection of name-value pairs that are used in
	/// various internet protocols like HTTP and SMTP.
	///
	/// The name is case-insensitive.
	///
	/// There can be more than one name-value pair with the
	/// same name.
	///
	/// MessageHeader supports writing and reading the
	/// header data in RFC 2822 format.
{
public:
	MessageHeader();
		/// Creates the MessageHeader.

	MessageHeader(const MessageHeader& messageHeader);
		/// Creates the MessageHeader by copying
		/// another one.

	virtual ~MessageHeader();
		/// Destroys the MessageHeader.

	MessageHeader& operator = (const MessageHeader& messageHeader);
		/// Assigns the content of another MessageHeader.

	virtual void write(std::ostream& ostr) const;
		/// Writes the message header to the given output stream.
		///
		/// The format is one name-value pair per line, with
		/// name and value separated by a colon and lines
		/// delimited by a carriage return and a linefeed
		/// character. See RFC 2822 for details.

	virtual void read(std::istream& istr);
		/// Reads the message header from the given input stream.
		///
		/// See write() for the expected format.
		/// Also supported is folding of field content, according
		/// to section 2.2.3 of RFC 2822.
		///
		/// Reading stops at the first empty line (a line only
		/// containing \r\n or \n), as well as at the end of
		/// the stream.
		///
		/// Some basic sanity checking of the input stream is
		/// performed.
		///
		/// Throws a MessageException if the input stream is
		/// malformed.

	static void splitElements(const std::string& s, std::vector<std::string>& elements, bool ignoreEmpty = true);
		/// Splits the given string into separate elements. Elements are expected
		/// to be separated by commas.
		///
		/// For example, the string
		///   text/plain; q=0.5, text/html, text/x-dvi; q=0.8
		/// is split into the elements
		///   text/plain; q=0.5
		///   text/html
		///   text/x-dvi; q=0.8
		///
		/// Commas enclosed in double quotes do not split elements.
		///
		/// If ignoreEmpty is true, empty elements are not returned.

	static void splitParameters(const std::string& s, std::string& value, NameValueCollection& parameters);
		/// Splits the given string into a value and a collection of parameters.
		/// Parameters are expected to be separated by semicolons.
		///
		/// Enclosing quotes of parameter values are removed.
		///
		/// For example, the string
		///   multipart/mixed; boundary="MIME_boundary_01234567"
		/// is split into the value
		///   multipart/mixed
		/// and the parameter
		///   boundary -> MIME_boundary_01234567

	static void splitParameters(const std::string::const_iterator& begin, const std::string::const_iterator& end, NameValueCollection& parameters);
		/// Splits the given string into a collection of parameters.
		/// Parameters are expected to be separated by semicolons.
		///
		/// Enclosing quotes of parameter values are removed.

	static void quote(const std::string& value, std::string& result, bool allowSpace = false);
		/// Checks if the value must be quoted. If so, the value is
		/// appended to result, enclosed in double-quotes.
		/// Otherwise. the value is appended to result as-is.

private:
	enum Limits
		/// Limits for basic sanity checks when reading a header
	{
		MAX_NAME_LENGTH  = 256,
		MAX_VALUE_LENGTH = 4096
	};
};


} } // namespace Poco::Net


#endif // Net_MessageHeader_INCLUDED
