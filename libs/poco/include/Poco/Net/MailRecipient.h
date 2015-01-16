//
// MailRecipient.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/MailRecipient.h#1 $
//
// Library: Net
// Package: Mail
// Module:  MailRecipient
//
// Definition of the MailRecipient class.
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


#ifndef Net_MailRecipient_INCLUDED
#define Net_MailRecipient_INCLUDED


#include "Poco/Net/Net.h"


namespace Poco {
namespace Net {


class Net_API MailRecipient
	/// The recipient of an e-mail message.
	///
	/// A recipient has a type (primary recipient,
	/// carbon-copy recipient, blind-carbon-copy
	/// recipient), an e-mail address and an optional
	/// real name.
{
public:
	enum RecipientType
	{
		PRIMARY_RECIPIENT,
		CC_RECIPIENT,
		BCC_RECIPIENT
	};

	MailRecipient();
		/// Creates an empty MailRecipient.

	MailRecipient(const MailRecipient& recipient);
		/// Creates a MailRecipient by copying another one.

	MailRecipient(RecipientType type, const std::string& address);
		/// Creates a MailRecipient of the given type.

	MailRecipient(RecipientType type, const std::string& address, const std::string& realName);
		/// Creates a MailRecipient of the given type.

	~MailRecipient();
		/// Destroys the MailRecipient.

	MailRecipient& operator = (const MailRecipient& recipient);
		/// Assigns another recipient.

	void swap(MailRecipient& recipient);
		/// Exchanges the content of two recipients.

	RecipientType getType() const;
		/// Returns the type of the recipient.

	void setType(RecipientType type);
		/// Sets the type of the recipient.

	const std::string& getAddress() const;
		/// Returns the address of the recipient.

	void setAddress(const std::string& address);
		/// Sets the address of the recipient.

	const std::string& getRealName() const;
		/// Returns the real name of the recipient.

	void setRealName(const std::string& realName);
		/// Sets the real name of the recipient.

private:
	std::string   _address;
	std::string   _realName;
	RecipientType _type;
};


//
// inlines
//
inline MailRecipient::RecipientType MailRecipient::getType() const
{
	return _type;
}


inline const std::string& MailRecipient::getAddress() const
{
	return _address;
}


inline const std::string& MailRecipient::getRealName() const
{
	return _realName;
}


inline void swap(MailRecipient& r1, MailRecipient& r2)
{
	r1.swap(r2);
}


} } // namespace Poco::Net


#endif // Net_MailRecipient_INCLUDED
