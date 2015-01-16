//
// MulticastSocket.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/MulticastSocket.h#1 $
//
// Library: Net
// Package: Sockets
// Module:  MulticastSocket
//
// Definition of the MulticastSocket class.
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


#ifndef Net_MulticastSocket_INCLUDED
#define Net_MulticastSocket_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/NetworkInterface.h"


namespace Poco {
namespace Net {


class Net_API MulticastSocket: public DatagramSocket
	/// A MulticastSocket is a special DatagramSocket
	/// that can be used to send packets to and receive
	/// packets from multicast groups.
{
public:
	MulticastSocket();
		/// Creates the MulticastSocket.

	MulticastSocket(IPAddress::Family family);
		/// Creates an unconnected datagram socket.
		///
		/// The socket will be created for the
		/// given address family.

	MulticastSocket(const SocketAddress& address, bool reuseAddress = false);
		/// Creates a datagram socket and binds it
		/// to the given address.
		///
		/// Depending on the address family, the socket
		/// will be either an IPv4 or an IPv6 socket.

	MulticastSocket(const Socket& socket);
		/// Creates the DatagramSocket with the SocketImpl
		/// from another socket. The SocketImpl must be
		/// a DatagramSocketImpl, otherwise an InvalidArgumentException
		/// will be thrown.

	~MulticastSocket();
		/// Destroys the DatagramSocket.

	MulticastSocket& operator = (const Socket& socket);
		/// Assignment operator.
		///
		/// Releases the socket's SocketImpl and
		/// attaches the SocketImpl from the other socket and
		/// increments the reference count of the SocketImpl.

	void setInterface(const NetworkInterface& interface);
		/// Sets the interface used for sending multicast packets.
		///
		/// To select the default interface, specify an empty
		/// interface.
		///
		/// This is done by setting the IP_MULTICAST_IF/IPV6_MULTICAST_IF
		/// socket option.

	NetworkInterface getInterface() const;
		/// Returns the interface used for sending multicast packets.

	void setLoopback(bool flag);
		/// Enable or disable loopback for multicast packets.
		///
		/// Sets the value of the IP_MULTICAST_LOOP/IPV6_MULTICAST_LOOP
		/// socket option.

	bool getLoopback() const;
		/// Returns true iff loopback for multicast packets is enabled,
		/// false otherwise.

	void setTimeToLive(unsigned value);
		/// Specifies the TTL/hop limit for outgoing packets.
		///
		/// Sets the value of the IP_MULTICAST_TTL/IPV6_MULTICAST_HOPS
		/// socket option.

	unsigned getTimeToLive() const;
		/// Returns the TTL/hop limit for outgoing packets.

	void joinGroup(const IPAddress& groupAddress);
		/// Joins the specified multicast group at the default interface.

	void joinGroup(const IPAddress& groupAddress, const NetworkInterface& interface);
		/// Joins the specified multicast group at the given interface.

	void leaveGroup(const IPAddress& groupAddress);
		/// Leaves the specified multicast group at the default interface.

	void leaveGroup(const IPAddress& groupAddress, const NetworkInterface& interface);
		/// Leaves the specified multicast group at the given interface.
};


} } // namespace Poco::Net


#endif // Net_MulticastSocket_INCLUDED
