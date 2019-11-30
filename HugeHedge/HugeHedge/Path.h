//	Path.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-29

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

#include "World.h"

class Path : public Tile {
private:
	static std::string fileName;
	static std::string objectName;
	static char token;
	static void read(std::istream& ns);
public:
	Path(const Position& p);
	std::string toString() const { return objectName; }
	char toChar() const { return token; }
	bool isWall() const { return false; }
	friend void World::readTileData();
};

#endif
