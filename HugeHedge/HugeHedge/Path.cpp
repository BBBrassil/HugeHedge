//	Wall.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#include "Path.h"

#include "StreamReader.h"

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
*/
////////////////////////////////////////////////////////////////////////////////
void Path::read(const std::string& fn) {
	StreamReader* reader = new StreamReader();
	std::string line;

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
		StreamReader::getline(reader->file(), line);
		objectName = line;
		StreamReader::getline(reader->file(), line);
		token = line[0];
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

	reader->close();
	delete reader;
	reader = nullptr;
}