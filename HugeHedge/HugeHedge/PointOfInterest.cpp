//	PointOfInterest.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "PointOfInterest.h"

////////////////////////////////////////////////////////////////////////////////
/*	Constructor

	! Throws a FileOpenFail exception if the file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
PointOfInterest::PointOfInterest(const Position& p, const std::string& fn) : UniqueTile(p, fn) {
	solved = false;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>>
	Reads data from an input stream, storing it in the unique tile's fields

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& ns, PointOfInterest& poi) {
	std::string line, data;

	try {
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		poi.objectName = data;

		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		poi.token = data[0];

		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		if( data != "0" && data != "1" )
			throw IOManager::BadString(line);
		poi.wall = data[0] - '0';

		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		poi.description = data;
	}
	catch( ... ) {
		throw;
	}
	return ns;
}

////////////////////////////////////////////////////////////////////////////////
/*	onExamined()
	Fired when the player looks at this tile.

	//

	- player: Player object who has examined the tile.
	- os: Any output stream.
*/
////////////////////////////////////////////////////////////////////////////////
void PointOfInterest::onEnter(Player& player, std::ostream& os) {
	os << toString() << "\n\n";
}