//	Wall.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#include "Wall.h"

#include "StreamReader.h"

std::string Wall::fileName;
std::string Wall::objectName;
char Wall::token;

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
*/
////////////////////////////////////////////////////////////////////////////////
Wall::Wall(const Position& p) : Tile(p) {
	fileName = "";
	objectName = "";
	token = '\0';
}

////////////////////////////////////////////////////////////////////////////////
/*	read()
	
	Reads data from an input stream, storing it in the tile's member variables.

	! Throws an EmptyStream exception if the stream has no data to read.
	! Throws an EndOfFile exception if no data can be read from the stream other
	  than comment lines (which are skipped).
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
	! Throws a MissingValue exception if a value can't be extracted from line
	  either because it's missing or because of incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void Wall::read(std::istream& ns) {
	std::string line, data;

	// Read data from input stream.
	// Rethrow all exceptions.
	try {
		StreamReader::getline(ns, line);
		data = StreamReader::valueFrom(line);
		objectName = data;

		StreamReader::getline(ns, line);
		data = StreamReader::valueFrom(line);
		token = data[0];
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	setup()
	
	Reads data from a file, opens an input stream, then calls the read() method.

	! Throws a FileOpenFail exception if the file fails to open.
	! Throws an EmptyStream exception if the stream has no data to read.
	! Throws an EndOfFile exception if no data can be read from the stream other
	  than comment lines (which are skipped).
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
	! Throws a MissingValue exception if a value can't be extracted from line
	  either because it's missing or because of incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void Wall::setup(const std::string& fn) {
	StreamReader* reader = new StreamReader();
	std::string line;

	// Open input file.
	fileName = fn;
	try {
		reader->open(fileName);
	}
	catch( StreamReader::FileOpenFail ) {
		throw;
	}

	// Read data from file.
	// Include the file name when rethrowing exceptions because the reader doesn't
	// know it.
	try {
		reader->file() >> *this;
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
	catch( StreamReader::MissingValue ex ) {
		reader->close();
		delete reader;
		reader = nullptr;
		throw StreamReader::MissingValue(ex.getString(), fileName);
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