//	Mystery.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

#include "Mystery.h"

#include "ObjectReader.h"

Mystery::Mystery(const std::string& fn) {
	ObjectReader<Mystery>* reader = new ObjectReader<Mystery>(fn);

	fileName = fn;
	inventory = std::unique_ptr<LinkedList<Item>>(new LinkedList<Item>());

	// Read fields from file
	try {
		reader->read(*this);
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>>
	Reads data from an input stream, storing it in the mystery's fields.

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& ns, Mystery& mystery) {
	std::string line, data;

	try {
		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		mystery.objectName = data;

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		mystery.unsolvedDescription = data;

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		mystery.solvedDescription=data;
	}
	catch( ... ) {
		throw;
	}
	return ns;
}