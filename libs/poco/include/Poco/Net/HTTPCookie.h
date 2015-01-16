//
// HTTPCookie.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/HTTPCookie.h#2 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPCookie
//
// Definition of the HTTPCookie class.
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


#ifndef Net_HTTPCookie_INCLUDED
#define Net_HTTPCookie_INCLUDED


#include "Poco/Net/Net.h"


namespace Poco {
namespace Net {


class NameValueCollection;


class Net_API HTTPCookie
	/// This class represents a HTTP Cookie.
	///
	/// A cookie is a small amount of information sent by a Web
	/// server to a Web browser, saved by the browser, and later sent back
	/// to the server. A cookie's value can uniquely identify a client, so
	/// cookies are commonly used for session management.
	///
	/// A cookie has a name, a single value, and optional attributes such
	/// as a comment, path and domain qualifiers, a maximum age, and a
	/// version number.
	///
	/// This class supports both the Version 0 (by Netscape) and Version 1
	/// (by RFC 2109) cookie specifications. By default, cookies are created
	/// using Version 0 to ensure the best interoperability.
{
public:
	HTTPCookie();
		/// Creates an empty HTTPCookie.

	explicit HTTPCookie(const std::string& name);
		/// Creates a cookie with the given name.
		/// The cookie never expires.

	explicit HTTPCookie(const NameValueCollection& nvc);
		/// Creates a cookie from the given NameValueCollection.

	HTTPCookie(const std::string& name, const std::string& value);
		/// Creates a cookie with the given name and value.
		/// The cookie never expires.

	HTTPCookie(const HTTPCookie& cookie);
		/// Creates the HTTPCookie by copying another one.

	~HTTPCookie();
		/// Destroys the HTTPCookie.

	HTTPCookie& operator = (const HTTPCookie& cookie);
		/// Assigns a cookie.

	void setVersion(int version);
		/// Sets the version of the cookie.
		///
		/// Version must be either 0 (denoting a Netscape cookie)
		/// or 1 (denoting a RFC 2109 cookie).

	int getVersion() const;
		/// Returns the version of the cookie, which is
		/// either 0 or 1.

	void setName(const std::string& name);
		/// Sets the name of the cookie.

	const std::string& getName() const;
		/// Returns the name of the cookie.

	void setValue(const std::string& value);
		/// Sets the value of the cookie.
		///
		/// According to the cookie specification, the
		/// size of the value should not exceed 4 Kbytes.

	const std::string& getValue() const;
		/// Returns the value of the cookie.

	void setComment(const std::string& comment);
		/// Sets the comment for the cookie.
		///
		/// Comments are only supported for version 1 cookies.

	const std::string& getComment() const;
		/// Returns the comment for the cookie.

	void setDomain(const std::string& domain);
		/// Sets the domain for the cookie.

	const std::string& getDomain() const;
		/// Returns the domain for the cookie.

	void setPath(const std::string& path);
		/// Sets the path for the cookie.

	const std::string& getPath() const;
		/// Returns the path for the cookie.

	void setSecure(bool secure);
		/// Sets the value of the secure flag for
		/// the cookie.

	bool getSecure() const;
		/// Returns the value of the secure flag
		/// for the cookie.

	void setMaxAge(int maxAge);
		/// Sets the maximum age in seconds for
		/// the cookie.
		///
		/// A value of -1 causes the cookie to
		/// never expire on the client.
		///
		/// A value of 0 deletes the cookie on
		/// the client.

	int getMaxAge() const;
		/// Returns the maximum age in seconds for
		/// the cookie.

	void setHttpOnly(bool flag = true);
		/// Sets the HttpOnly flag for the cookie.

	bool getHttpOnly() const;
		/// Returns true iff the cookie's HttpOnly flag is set.

	std::string toString() const;
		/// Returns a string representation of the cookie,
		/// suitable for use in a Set-Cookie header.

private:
	int         _version;
	std::string _name;
	std::string _value;
	std::string _comment;
	std::string _domain;
	std::string _path;
	bool        _secure;
	int         _maxAge;
	bool        _httpOnly;
};


//
// inlines
//
inline int HTTPCookie::getVersion() const
{
	return _version;
}


inline const std::string& HTTPCookie::getName() const
{
	return _name;
}


inline const std::string& HTTPCookie::getValue() const
{
	return _value;
}


inline const std::string& HTTPCookie::getComment() const
{
	return _comment;
}


inline const std::string& HTTPCookie::getDomain() const
{
	return _domain;
}


inline const std::string& HTTPCookie::getPath() const
{
	return _path;
}


inline bool HTTPCookie::getSecure() const
{
	return _secure;
}


inline int HTTPCookie::getMaxAge() const
{
	return _maxAge;
}


inline bool HTTPCookie::getHttpOnly() const
{
	return _httpOnly;
}


} } // namespace Poco::Net


#endif // Net_HTTPCookie_INCLUDED
