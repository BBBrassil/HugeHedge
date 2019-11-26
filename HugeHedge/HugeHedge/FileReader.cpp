//	FileReader.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-26

#include "FileReader.h"

////////////////////////////////////////////////////////////////////////////////
/*	open()
	Opens the FileReader's file stream with the associated file name.
	Returns the stream.

	! Throws a FileOpenFail exception if the file fails to open.
*/
////////////////////////////////////////////////////////////////////////////////
std::ifstream& FileReader::open(std::string s) {
	fileName = s;
	file.open(s);

	if( file.fail() )
		throw FileOpenFail(fileName);

	return file;
}

////////////////////////////////////////////////////////////////////////////////
/*	close()
	Simply closes the FileReader's file stream.
*/
////////////////////////////////////////////////////////////////////////////////
void FileReader::close() {
	file.close();
}

////////////////////////////////////////////////////////////////////////////////
/*	getline()
	Extracts a line from the FileReader's file stream, ignoring comment lines.

	! Throws an EmptyFile exception if nothing is read from the file.
	! Throws an EndOfFile exception if only comments are read from the file.
*/
////////////////////////////////////////////////////////////////////////////////
std::string FileReader::getline() {
	std::string line;

	std::getline(file, line);
	if( file.eof() )
		throw EmptyFile(fileName);

	while( isComment(line) )
		std::getline(file, line);
	if( file.eof() )
		throw EndOfFile(fileName);

	return line;
}

////////////////////////////////////////////////////////////////////////////////
/*	isComment()
	Returns true if a given string is a comment.
	A comment line starts with a semicolon (;).
*/
////////////////////////////////////////////////////////////////////////////////
bool FileReader::isComment(const std::string& s) const {
	return s[0] == ';';
}

////////////////////////////////////////////////////////////////////////////////
/*	findDelimiter()
	Returns the index of a delimiter character if it can be found in a given
	string.

	! Throws a BadFormat exception if no delimiter is found.
*/
////////////////////////////////////////////////////////////////////////////////
int FileReader::findDelimiter(const std::string& s, const char& delimiter) const {
	int index = (int)s.find(delimiter);

	if( index < 0 )
		throw BadFormat(fileName);

	return index;
}

////////////////////////////////////////////////////////////////////////////////
/*	key()
	Extracts a key from a string.
	Key/value format is "key=value".

	! Throws a BadFormat exception if no key is read.
*/
////////////////////////////////////////////////////////////////////////////////
std::string FileReader::key(const std::string& s) const {
	int index = findDelimiter(s, '=');

	return s.substr(0, index);
}

////////////////////////////////////////////////////////////////////////////////
/* value()
	Extracts a value from a string.
	Key/value format is "key=value".

	! Throws a BadFormat exception if the string has no delimiter.
	! Throws a MissingValue exception if no value is read.
*/
////////////////////////////////////////////////////////////////////////////////
std::string FileReader::value(const std::string& s) const {
	int index;

	try {
		index = findDelimiter(s, '=');
	}
	catch( BadFormat ) {
		throw;
	}

	if( index == s.length() - 1 )
		throw MissingValue(fileName, key(s));

	return s.substr((size_t)index + 1, s.length() - index);
}