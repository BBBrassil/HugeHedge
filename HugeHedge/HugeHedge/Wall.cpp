//	Wall.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-29

#include "Wall.h"

#include "StreamReader.h"

std::string Wall::fileName;
std::string Wall::objectName;
char Wall::token;

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
*/
////////////////////////////////////////////////////////////////////////////////
Wall::Wall(const Position& p) : Tile(p) {}

////////////////////////////////////////////////////////////////////////////////
/*	read()
	
	Reads data from an input stream, storing it in the tile's member variables.
	
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
		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		objectName = data;

		StreamReader::getlineEOF(ns, line);
		data = StreamReader::valueFrom(line);
		token = data[0];
	}
	catch( ... ) {
		throw;
	}
}