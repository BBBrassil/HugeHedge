//	PointOfInterest.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

#include "PointOfInterest.h"

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
	Adds a mystery to the tile.

	! Throws a FileOpenFail exception if the file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
PointOfInterest::PointOfInterest(const Position& p, const std::string& fn) : UniqueTile(p, fn) {
	mystery = nullptr;
	try {
		mystery = new Mystery(mysteryFileName);
	}
	catch( ... ) {
		throw;
	}
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
std::istream& operator>>(std::istream& ns, PointOfInterest& poi) {
	std::string line, data;

	try {
		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		poi.objectName = data;

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		poi.token = data[0];

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		if( data != "0" && data != "1" )
			throw StreamReader::BadString(line);
		poi.wall = data[0] - '0';

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		poi.mysteryFileName = data;
	}
	catch( ... ) {
		throw;
	}
	return ns;
}