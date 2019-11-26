//	FileReader.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-26

////////////////////////////////////////////////////////////////////////////////
/*	FileReader class
	
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

class FileReader {
private:
	std::string fileName;
	std::ifstream file;
	bool isComment(const std::string& s) const;
	int findDelimiter(const std::string& s, const char& delimiter) const;
public:
	std::ifstream& open(std::string s);
	void close();
	std::string getline();
	std::string key(const std::string& s) const;
	std::string value(const std::string& s) const;
	
	///////////////////////////////////////////////////////////////////////////////
	/*	FileException parent class
	*/
	///////////////////////////////////////////////////////////////////////////////
	class FileException {
	private:
		std::string fileName;
	public:
		FileException(const std::string& s) { fileName = s; }
		std::string getFileName() const { return fileName; }
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	BadFormat exception
		Thrown when data read from a file does not follow the expected format.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class BadFormat : FileException {
	public:
		BadFormat(const std::string& s) : FileException(s) {};
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	BadValue exception
		Thrown when a value is read but the data can't be assigned where it should
		be, e.g. if the data type is wrong.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class BadValue : FileException {
	private:
		std::string keyName;
		std::string valueName;
	public:
		BadValue(const std::string& fn, const std::string& kn, const std::string& vn) :
			FileException(fn) {
			keyName = kn;
			valueName = vn;
		};
		std::string getKeyName() const { return keyName; }
		std::string getValueName() const { return valueName; }
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	EndOfFile exception
		Thrown when the end of a file is reached before all the data needed from the
		file has been read.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class EndOfFile : FileException {
	public:
		EndOfFile(const std::string& s) : FileException(s) {};
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	EmptyFile exception
		Thrown when no data can be read from a file because it is empty.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class EmptyFile : FileException {
	public:
		EmptyFile(const std::string& s) : FileException(s) {};
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	FileOpenFail exception
		Thrown when a file fails to open.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class FileOpenFail : FileException {
	public:
		FileOpenFail(const std::string& s) : FileException(s) {};
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	MissingValue exception
		Thrown when a key is read but the value isn't.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class MissingValue : FileException {
	private:
		std::string keyName;
	public:
		MissingValue(const std::string& fn, const std::string& kn) :
			FileException(fn) { keyName = kn; };
		std::string getKeyName() const { return keyName; }
	};
};
#endif