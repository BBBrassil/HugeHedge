//	Wall.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

////////////////////////////////////////////////////////////////////////////////
/*	Wall class
	A generic tile class for tiles that block the player's path. Implements the
	abstract Tile class.

	Uses static members for the name, token, etc that are shared between all
	Wall objects. These are read from a file, which can be done before or after
	a Wall is instantiated via the read() method.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef WALL_H
#define WALL_H

#include "Tile.h"

class Wall : public Tile {
private:
	static std::string fileName;
	static std::string objectName;
	static char token;
	virtual void read(const std::string& fn);
public:
	Wall(const Position& p);
	std::string toString() { return objectName; }
	char toChar() { return token; }
	bool isWall() { return true; }
};

#endif