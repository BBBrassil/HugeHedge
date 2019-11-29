//	UniqueTile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#include "UniqueTile.h"

#include "StreamReader.h"

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
	
	Reads data from a file, storing it in the tile's member variables.

	! Throws a FileOpenFail exception if the file fails to open.
	! Throws an EndOfFile exception if there is no data to read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
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
		reader->file() >> *this;
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

	reader->close();
	delete reader;
	reader = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/*	read()
	
	Reads data from an input stream, storing it in the tile's member variables.
	
	! Throws an EndOfFile exception if there is no data to read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void UniqueTile::read(std::istream& ns) {
	std::string line, data;
	
	try {
		StreamReader::getline(ns, line);
		data = StreamReader::valueFrom(line);
		objectName = data;

		StreamReader::getline(ns, line);
		data = StreamReader::valueFrom(line);
		token = data[0];

		StreamReader::getline(ns, line);
		data = StreamReader::valueFrom(line);
		if( data != "0" && data != "1" )
			throw StreamReader::BadString(line);
		wall = data[0] - '0';
	}
	catch( ... ) {
		throw;
	}
}