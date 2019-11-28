//	StreamReader.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-27

////////////////////////////////////////////////////////////////////////////////
/*	StreamReader class

	Responsible for reading and validating all data in the project.

	Has methods that mimic the functionality of ifstream::open, ifstream::close,
	and std::getline that also throw exceptions for bad data.

	Only needs to be instantiated to open or close files. Static methods will
	suffice	for anything else and work with any input stream object. If these are
	called using a file stream, however, the caller will be responsible for
	knowing	the file name.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef STREAMREADER_H
#define STREAMREADER_H

#include <iostream>
#include <fstream>
#include <string>

class StreamReader {
private:
	std::string fileName;
	std::ifstream fileStream;
public:
	StreamReader() { fileName = ""; }
	void open(const std::string& fn);
	void close();
	std::ifstream& file() { return fileStream; }
	static void getline(std::istream& ns, std::string& s);
	static bool isComment(const std::string& s);
	static std::string keyFrom(const std::string& s);
	static std::string valueFrom(const std::string& s);

	///////////////////////////////////////////////////////////////////////////////
	/*	BadString exception
		Thrown when data read from a file does not follow the expected format.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class BadString {
	private:
		std::string badString;
		std::string fileName;
	public:
		BadString(const std::string& s) { fileName = ""; }
		BadString(const std::string& s, const std::string& fn) {
			badString = s; fileName = fn; }
		std::string getString() const { return badString; }
		std::string getFileName() const { return fileName; };
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	EmptyFile exception
		Thrown when no data can be read from a stream because there is nothing in
		it.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class EmptyStream {
	private:
		std::string fileName;
	public:
		EmptyStream() { fileName = ""; }
		EmptyStream(const std::string& fn) { fileName = fn; }
		std::string getFileName() const { return fileName; }
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	EndOfFile exception
		Thrown when the end of a stream is reached before all the data that needs
		to be read has been read.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class EndOfFile {
	private:
		std::string fileName;
	public:
		EndOfFile() { fileName = ""; }
		EndOfFile(const std::string& fn) { fileName = fn; }
		std::string getFileName() const { return fileName; }
	};
	
	///////////////////////////////////////////////////////////////////////////////
	/*	FileOpenFail exception
		Thrown when a file fails to open.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class FileOpenFail {
	private:
		std::string fileName;
	public:
		FileOpenFail(const std::string& fn = "") { fileName = fn; }
		std::string getFileName() const { return fileName; }
	};

	///////////////////////////////////////////////////////////////////////////////
	/*	MissingValue exception
		Thrown when a key is read but the value isn't.
	*/
	///////////////////////////////////////////////////////////////////////////////
	class MissingValue : public BadString {
	public:
		MissingValue(const std::string& s) : BadString(s) {}
		MissingValue(const std::string& s, const std::string& fn) :
			BadString(s, fn) {}
	};
};

#endif