//	UniqueTile.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

////////////////////////////////////////////////////////////////////////////////
/*	UniqueTile class

	Class for tile objects that will have their data read from a file when
	instantiated. Implements the abstract Tile class.

	* Overloads the >> operator to read fields from an input stream.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIQUETILE_H
#define UNIQUETILE_H

#include "Tile.h"
#include "ObjectReader.h"

class UniqueTile : public Tile {
protected:
	std::string fileName;
	std::string objectName;
	char token;
	bool wall;
public:
	UniqueTile(const Position& p, const std::string& fn);
	std::string toString() const { return objectName; }
	char toChar() const { return token; }
	bool isWall() const { return wall; }
	friend std::istream& operator>>(std::istream& ns, UniqueTile& t);
};

#endif