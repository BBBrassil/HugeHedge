//	Item.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

#include "Item.h"

#include "ObjectReader.h"
#include <string>
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
	ObjectReader<Item>* reader = new ObjectReader<Item>();
	name = "";
	description = "";

	try {
		reader->read((Item*)this);
	}
	catch( StreamReader::FileOpenFail ) {
		delete reader;
		reader = nullptr;
	}
	catch( StreamReader::EndOfFile ) {
		delete reader;
		reader = nullptr;
	}
	catch( StreamReader::BadString ) {
		delete reader;
		reader = nullptr;
	}
	delete reader;
	reader = nullptr;
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
		<< '\t' << description << '\n';

	return ss.str();
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
		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		item.name = data;

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
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