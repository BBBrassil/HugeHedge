//	StreamReader.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#include "StreamReader.h"

////////////////////////////////////////////////////////////////////////////////
/*	open()
	Opens the StreamReader's file stream with the associated file name.

	! Throws a FileOpenFail exception if the file fails to open.
*/
////////////////////////////////////////////////////////////////////////////////
void StreamReader::open(const std::string& fn) {
	fileName = fn;

	fileStream.open(fileName);
	if( !fileStream )
		throw FileOpenFail(fileName);
}


////////////////////////////////////////////////////////////////////////////////
/*	close()
	Simply closes the StreamReader's file stream and clears the file name.
*/
////////////////////////////////////////////////////////////////////////////////
void StreamReader::close() {
	fileStream.close();
	fileName = "";
}

////////////////////////////////////////////////////////////////////////////////
/*	getline()
	Extracts a line from an input stream, ignoring comment lines.

	! Throws an EndOfFile exception if no data is read.
*/
////////////////////////////////////////////////////////////////////////////////
void StreamReader::getline(std::istream& ns, std::string& line) {
	std::getline(ns, line);
	if( !ns )
		throw EndOfFile();

	while( isComment(line) )
		std::getline(ns, line);
	if( !ns )
		throw EndOfFile();
}

////////////////////////////////////////////////////////////////////////////////
/*	isComment()
	Returns true if a given string is a comment.
	A comment line is any line that starts with a semicolon (;).
*/
////////////////////////////////////////////////////////////////////////////////
bool StreamReader::isComment(const std::string& s) {
	return s[0] == ';';
}

////////////////////////////////////////////////////////////////////////////////
/*	keyFrom()
	Extracts a key from a string.
	Key/value format is "key=value".

	! Throws a BadString exception if no key is read.
*/
////////////////////////////////////////////////////////////////////////////////
std::string StreamReader::keyFrom(const std::string& s) {
	int index = s.find_first_of('=');

	if( index < 0 )
		throw BadString(s);

	return s.substr(0, (size_t)index - 1);
}

////////////////////////////////////////////////////////////////////////////////
/* valueFrom()
	Extracts a value from a string.
	Key/value format is "key=value".

	! Throws a BadString exception if a value could not be extracted from the
	  string.
*/
////////////////////////////////////////////////////////////////////////////////
std::string StreamReader::valueFrom(const std::string& s) {
	int index = s.find_first_of('=');

	if( index < 0 || index == s.length() - 1 )
		throw BadString(s);

	return s.substr((size_t)index + 1, s.length() - 1);
}