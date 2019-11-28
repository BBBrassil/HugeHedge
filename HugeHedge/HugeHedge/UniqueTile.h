//	UniqueTile.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

////////////////////////////////////////////////////////////////////////////////
/*	UniqueTile class
	
	Class for tile objects that will have their data read from a file when
	instantiated. Implements the abstract Tile class.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIQUETILE_H
#define UNIQUETILE_H

#include "Tile.h"

class UniqueTile : public Tile {
private:
	std::string fileName;
	bool wall;
	char token;
	std::string name;
public:
	UniqueTile(const Position& p, const std::string& fn);
	void read(std::istream& ns);
	bool isWall() const { return wall; }
	char toChar() const { return token; }
	std::string toString() const { return name; }
};

#endif