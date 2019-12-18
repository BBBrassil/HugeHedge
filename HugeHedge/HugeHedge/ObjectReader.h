//	ObjectReader.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

////////////////////////////////////////////////////////////////////////////////
/*	ObjectReader template class

	Used for reading data from text files into fields.

	* Inherits from IOManager.
	* Template works with any class that overloads the >> operator.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef OBJECTREADER_H
#define OBJECTREADER_H

#include "IOManager.h"

template <class T>
class ObjectReader : public IOManager {
public:
	ObjectReader(const std::string& fn) : IOManager() { fileName = fn; }
	void read(T& obj);
};

////////////////////////////////////////////////////////////////////////////////
/*	read()
	Reads data from an file, storing it in an object's fields.

	! Throws a FileOpenFail exception if the input file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
void ObjectReader<T>::read(T& obj) {
	// Open input file.
	try {
		open(fileName);
	}
	catch( IOManager::FileOpenFail ) {
		throw;
	}
	// Read data from file.
	// Include the file name when rethrowing any exceptions.
	try {
		file() >> obj;
	}
	catch( IOManager::EndOfFile ) {
		close();
		throw new IOManager::EndOfFile(fileName);
	}
	catch( IOManager::BadString ex ) {
		close();
		throw new IOManager::BadString(ex.getString(), fileName);
	}
}

#endif