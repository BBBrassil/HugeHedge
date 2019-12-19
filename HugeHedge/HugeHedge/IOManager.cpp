//	IOManager.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "IOManager.h"

////////////////////////////////////////////////////////////////////////////////
/*	open()
	Opens the IOManager's file stream with the associated file name for reading.

	! Throws a FileOpenFail exception if the input file fails to open.
*/
////////////////////////////////////////////////////////////////////////////////
void IOManager::open(const std::string& fn) {
	fileName = fn;

	fileStream.open(fileName, std::fstream::in);
	if( !fileStream )
		throw FileOpenFail(fileName);
}
////////////////////////////////////////////////////////////////////////////////
/*	openOut()
	Opens the IOManager's file stream with the associated file name for writing.

	! Throws a FileOpenFail exception if the input file fails to open.
*/
////////////////////////////////////////////////////////////////////////////////
void IOManager::openOut(const std::string& fn) {
	fileName = fn;

	fileStream.open(fileName, std::fstream::out);
	if( !fileStream )
		throw FileOpenFail(fileName);
}

////////////////////////////////////////////////////////////////////////////////
/*	close()
	Simply closes the IOManager's file stream and clears the file name.
*/
////////////////////////////////////////////////////////////////////////////////
void IOManager::close() {
	fileStream.close();
	fileName = "";
}

////////////////////////////////////////////////////////////////////////////////
/*	getline()
	Extracts a line from an input stream, ignoring comment lines.
	Returns an empty string if nothing was read.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& IOManager::getline(std::istream& ns, std::string& line) {
	std::getline(ns, line);
	if( !ns )
		line = "";

	while( isComment(line) )
		std::getline(ns, line);
	if( !ns )
		line = "";

	return ns;
}

////////////////////////////////////////////////////////////////////////////////
/*	getlineEOF()
	Extracts a line from an input stream, ignoring comment lines.

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& IOManager::getlineEOF(std::istream& ns, std::string& line) {
	std::getline(ns, line);
	if( !ns )
		throw EndOfFile();

	while( isComment(line) )
		std::getline(ns, line);
	if( !ns )
		throw EndOfFile();
	return ns;
}

////////////////////////////////////////////////////////////////////////////////
/*	isComment()
	Returns true if a given string is a comment.
	A comment line is any line that starts with a semicolon (;).
*/
////////////////////////////////////////////////////////////////////////////////
bool IOManager::isComment(const std::string& s) {
	return s[0] == ';';
}

////////////////////////////////////////////////////////////////////////////////
/*	keyFrom()
	Extracts a key from a string.
	Key/value format is "key=value".

	! Throws a BadString exception if a value could not be read from the string.
*/
////////////////////////////////////////////////////////////////////////////////
std::string IOManager::keyFrom(const std::string& s) {
	int index = s.find_first_of('=');

	if( index < 0 )
		throw BadString(s);

	return s.substr(0, (size_t)index - 1);
}

////////////////////////////////////////////////////////////////////////////////
/* valueFrom()
	Extracts a value from a string.
	Key/value format is "key=value".

	! Throws a BadString exception if a value could not be read from the string.
*/
////////////////////////////////////////////////////////////////////////////////
std::string IOManager::valueFrom(const std::string& s) {
	int index = s.find_first_of('=');

	if( index < 0 || index == s.length() - 1 )
		throw BadString(s);

	return s.substr((size_t)index + 1, s.length() - 1);
}