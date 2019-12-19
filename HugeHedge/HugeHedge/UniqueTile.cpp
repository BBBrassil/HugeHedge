//	UniqueTile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

#include "UniqueTile.h"

#include <memory>

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
		// objectName
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		t.objectName = data;

		// description
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		t.description = data;
		
		// token
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		t.token = data[0];

		// wall
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		if( data != "0" && data != "1" )
			throw IOManager::BadString(line);
		t.wall = data[0] - '0';
	}
	catch( ... ) {
		throw;
	}
	return ns;
}