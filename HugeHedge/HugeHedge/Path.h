//	Path.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

////////////////////////////////////////////////////////////////////////////////
/*	Path class
	A generic tile class for tiles that don't block the player's movement.

	Implements the abstract Tile class.
	
	Uses static members for the name, token, etc that are shared between all
	Path objects. These are read from a file, which can be done before or after
	a Path is instantiated via the read() method.
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
	virtual void read(const std::string& fn);
public:
	Path(const Position& p);
	std::string toString() { return objectName; }
	char toChar() { return token; }
	bool isWall() { return false; }
};

#endif
