//	Wall.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

#include "Wall.h"

#include "IOManager.h"

std::string Wall::fileName;
std::string Wall::objectName;
std::string Wall::description;
char Wall::token;

////////////////////////////////////////////////////////////////////////////////
/*	read()
	Reads data from an input stream, storing it in the tile's fields.

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void Wall::read(std::istream& ns) {
	std::string line, data;

	// Read data from input stream.
	// Rethrow all exceptions.
	try {
		// objectName
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		objectName = data;

		// description
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		description = data;

		// token
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		token = data[0];
	}
	catch( ... ) {
		throw;
	}
}