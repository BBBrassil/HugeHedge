//	ObjectReader.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

////////////////////////////////////////////////////////////////////////////////
/*	ObjectReader class
	Inherits from StreamReader. Used for reading data from text files into
	object member variables.

	Works with any class that overloads the >> operator.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef OBJECTREADER_H
#define OBJECTREADER_H

#include "StreamReader.h"
template <class T>
class ObjectReader : public StreamReader {
public:
	ObjectReader() : StreamReader() {}

	////////////////////////////////////////////////////////////////////////////
	/*	readObject()
		Reads data from an file, storing it in an object's member variables.

		! Throws a FileOpenFail exception if the input file fails to open.
		! Throws an EndOfFile exception if the end of the input stream is
		  reached before the expected data is read.
		! Throws a BadString exception if data can't be read from a line because
		  of incorrect formatting.
	*/
	////////////////////////////////////////////////////////////////////////////
	void read(T* obj) {
		// Open input file.
		try {
			open(fileName);
		}
		catch( FileOpenFail ) {
			throw;
		}
		// Read data from file.
		// Include the file name when rethrowing any exceptions.
		try {
			file() >> *obj;
		}
		catch( EndOfFile ) {
			close();
			throw new StreamReader::EndOfFile(fileName);
		}
		catch( BadString ex ) {
			close();
			throw new StreamReader::BadString(ex.getString(), fileName);
		}
	}
};

#endif