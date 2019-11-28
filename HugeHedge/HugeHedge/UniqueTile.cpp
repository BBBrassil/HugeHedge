//	UniqueTile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#include "UniqueTile.h"

#include "StreamReader.h"

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
*/
////////////////////////////////////////////////////////////////////////////////
UniqueTile::UniqueTile(const Position& p, const std::string& fn) : Tile(p) {
	StreamReader* reader = new StreamReader();

	// Open input file.
	fileName = fn;
	try {
		reader->open(fileName);
	}
	catch( StreamReader::FileOpenFail ) {
		delete reader;
		reader = nullptr;
		throw;
	}

	// Read data from file.
	// Include the file name when rethrowing exceptions because the reader doesn't
	// know it.
	try {
		reader->file >> *this;
	}
	catch( StreamReader::EmptyStream ) {
		reader->close();
		delete reader;
		reader = nullptr;
		throw StreamReader::EmptyStream(fileName);
	}
	catch( StreamReader::EndOfFile ) {
		reader->close();
		delete reader;
		reader = nullptr;
		throw StreamReader::EndOfFile(fileName);
	}
	catch( StreamReader::BadString ex ) {
		reader->close();
		delete reader;
		reader = nullptr;
		throw StreamReader::BadString(ex.getString(), fileName);
	}
	catch( StreamReader::MissingValue ex ) {
		reader->close();
		delete reader;
		reader = nullptr;
		throw StreamReader::MissingValue(ex.getString(), fileName);
	}
	
	delete reader;
	reader = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/*	read()
	
	Reads data from an input stream, storing it in the tile's member variables.
*/
////////////////////////////////////////////////////////////////////////////////
void UniqueTile::read(std::istream& ns) {
	std::string line;

	try {
		StreamReader::getline(ns, line);
		name = line;
		StreamReader::getline(ns, line);
		token = line[0];
		StreamReader::getline(ns, line);
		if( line != "0" || "1" )
			throw StreamReader::BadString(line);
		wall = line[0] - '0';
	}
	catch( ... ) {
		throw;
	}
}