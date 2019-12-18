//	Path.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "Path.h"

#include "IOManager.h"

std::string Path::fileName;
std::string Path::objectName;
std::string Path::description;
char Path::token;

////////////////////////////////////////////////////////////////////////////////
/*	read()

	Reads data from an input stream, storing it in the tile's member variables.

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void Path::read(std::istream& ns) {
	std::string line, data;

	// Read data from input stream.
	// Rethrow all exceptions.
	try {
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		objectName = data;

		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		description = data;

		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		token = data[0];
	}
	catch( ... ) {
		throw;
	}
}