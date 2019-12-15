//	UniqueTile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

#include "UniqueTile.h"

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
	Reads data from a file, storing it in the tile's fields.

	! Throws a FileOpenFail exception if the file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
UniqueTile::UniqueTile(const Position& p, const std::string& fn) : Tile(p) {
	ObjectReader<UniqueTile>* reader = new ObjectReader<UniqueTile>(fn);

	fileName = fn;
	// Default initializations to get the IDE to stop yelling at me
	token = '\0';
	wall = true;

	// Read fields from file
	try {
		reader->read(*this);
	}
	catch( StreamReader::FileOpenFail ) {
		delete reader;
		reader = nullptr;
		throw;
	}
	catch( StreamReader::EndOfFile ) {
		delete reader;
		reader = nullptr;
		throw;
	}
	catch( StreamReader::BadString ) {
		delete reader;
		reader = nullptr;
		throw;
	}
	delete reader;
	reader = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>>
	Reads data from an input stream, storing it in the unique tile's fields

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& ns, UniqueTile& t) {
	std::string line, data;

	try {
		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		t.objectName = data;

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		t.description = data;

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		t.token = data[0];

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		if( data != "0" && data != "1" )
			throw StreamReader::BadString(line);
		t.wall = data[0] - '0';
	}
	catch( ... ) {
		throw;
	}
	return ns;
}