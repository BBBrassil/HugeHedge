//	Path.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#include "Path.h"

#include "StreamReader.h"

std::string Path::fileName;
std::string Path::objectName;
char Path::token;

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
*/
////////////////////////////////////////////////////////////////////////////////
Path::Path(const Position& p) : Tile(p) {
	fileName = "";
	objectName = "";
	token = '\0';
}

////////////////////////////////////////////////////////////////////////////////
/*	read()

	Reads data from an input stream, storing it in the tile's member variables.

	! Throws an EndOfFile exception if there is no data to read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void Path::read(std::istream& ns) {
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
	! Throws an EndOfFile exception if there is no data to read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void Path::setup(const std::string& fn) {
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