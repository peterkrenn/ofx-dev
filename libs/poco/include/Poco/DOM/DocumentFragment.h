//
// DocumentFragment.h
//
// $Id: //poco/1.3/XML/include/Poco/DOM/DocumentFragment.h#1 $
//
// Library: XML
// Package: DOM
// Module:  DOM
//
// Definition of the DOM DocumentFragment class.
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


#ifndef DOM_DocumentFragment_INCLUDED
#define DOM_DocumentFragment_INCLUDED


#include "Poco/XML/XML.h"
#include "Poco/DOM/AbstractContainerNode.h"
#include "Poco/XML/XMLString.h"


namespace Poco {
namespace XML {


class XML_API DocumentFragment: public AbstractContainerNode
	/// DocumentFragment is a "lightweight" or "minimal" Document object. It is
	/// very common to want to be able to extract a portion of a document's tree
	/// or to create a new fragment of a document. Imagine implementing a user command
	/// like cut or rearranging a document by moving fragments around. It is desirable
	/// to have an object which can hold such fragments and it is quite natural
	/// to use a Node for this purpose. While it is true that a Document object
	/// could fulfill this role, a Document object can potentially be a heavyweight
	/// object, depending on the underlying implementation. What is really needed
	/// for this is a very lightweight object. DocumentFragment is such an object.
	///
	/// Furthermore, various operations -- such as inserting nodes as children of
	/// another Node -- may take DocumentFragment objects as arguments; this results
	/// in all the child nodes of the DocumentFragment being moved to the child
	/// list of this node.
	///
	/// The children of a DocumentFragment node are zero or more nodes representing
	/// the tops of any sub-trees defining the structure of the document. DocumentFragment
	/// nodes do not need to be well-formed XML documents (although they do need
	/// to follow the rules imposed upon well-formed XML parsed entities, which
	/// can have multiple top nodes). For example, a DocumentFragment might have
	/// only one child and that child node could be a Text node. Such a structure
	/// model represents neither an HTML document nor a well-formed XML document.
	///
	/// When a DocumentFragment is inserted into a Document (or indeed any other
	/// Node that may take children) the children of the DocumentFragment and not
	/// the DocumentFragment itself are inserted into the Node. This makes the DocumentFragment
	/// very useful when the user wishes to create nodes that are siblings; the
	/// DocumentFragment acts as the parent of these nodes so that the user can
	/// use the standard methods from the Node interface, such as insertBefore and
	/// appendChild.
{
public:
	// Node
	const XMLString& nodeName() const;
	unsigned short nodeType() const;

protected:
	DocumentFragment(Document* pOwnerDocument);
	DocumentFragment(Document* pOwnerDocument, const DocumentFragment& fragment);
	~DocumentFragment();

	Node* copyNode(bool deep, Document* pOwnerDocument) const;

private:
	static const XMLString NODE_NAME;

	friend class Document;
};


} } // namespace Poco::XML


#endif // DOM_DocumentFragment_INCLUDED
