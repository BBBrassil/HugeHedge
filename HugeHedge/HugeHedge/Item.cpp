//	Item.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

#include "Item.h"

#include "ObjectReader.h"
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
	Reads data from a file, storing it in the item's fields.

	! Throws a FileOpenFail exception if the file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
Item::Item(const std::string& fn) {
	std::unique_ptr<ObjectReader<Item>> reader(new ObjectReader<Item>(fn));

	try {
		reader->read(*this);
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	toString()
	Shows the item name and description.
*/
////////////////////////////////////////////////////////////////////////////////
std::string Item::toString() const {
	std::stringstream ss;
	ss
		<< name << '\n'
		<< "  " << description << '\n';

	return ss.str();
}

////////////////////////////////////////////////////////////////////////////////
/*	operator<
	Compares item names.
*/
////////////////////////////////////////////////////////////////////////////////
bool Item::operator<(const Item& right) const {
	return name < right.name;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>
	Compares item names.
*/
////////////////////////////////////////////////////////////////////////////////
bool Item::operator>(const Item& right) const {
	return name > right.name;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator==
	Compares item names.
*/
////////////////////////////////////////////////////////////////////////////////
bool Item::operator==(const Item& right) const {
	return name == right.name;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator<=
	Compares item names.
*/
////////////////////////////////////////////////////////////////////////////////
bool Item::operator<=(const Item& right) const {
	return *this < right || *this == right;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator<=
	Compares item names.
*/
////////////////////////////////////////////////////////////////////////////////
bool Item::operator>=(const Item& right) const {
	return *this > right || *this == right;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator!=
	Compares item names.
*/
////////////////////////////////////////////////////////////////////////////////
bool Item::operator!=(const Item& right) const {
	return !(*this == right);
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>>
	Reads data from an input stream, storing it in the item's fields.

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& ns, Item& item) {
	std::string line, data;

	try {
		// name
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		item.name = data;

		// description
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		item.description = data;
	}
	catch( ... ) {
		throw;
	}
	return ns;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator<<
	Simply sends the the toString() method into the stream.
*/
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, Item& item) {
	os << item.toString();
	return os;
}