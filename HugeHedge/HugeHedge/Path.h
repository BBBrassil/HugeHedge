//	Path.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

////////////////////////////////////////////////////////////////////////////////
/*	Path class
	A generic tile class for tiles that don't block the player's movement.

	Implements the abstract Tile class.
	
	Uses static members for the name, token, etc that are shared between all
	Path objects.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef PATH_H
#define PATH_H

#include "Tile.h"

class Path : public Tile {
private:
	static std::string fileName;
	static std::string objectName;
	static char token;
public:
	Path(const Position& p);
	void read(std::istream& ns);
	void setup(const std::string& fn);
	std::string toString() { return objectName; }
	char toChar() { return token; }
	bool isWall() { return false; }
};

#endif
