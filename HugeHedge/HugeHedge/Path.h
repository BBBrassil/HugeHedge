//	Path.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

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

#include <string>

class World;

class Path : public Tile {
private:
	static std::string fileName;
	static std::string objectName;
	static std::string description;
	static char token;
	static void read(std::istream& ns);
public:
	Path(const Position& p) : Tile(p) {}
	std::string toString() const { return description; }
	char toChar() const { return token; }
	bool isWall() const { return false; }
	friend void World::readTileData();
};

#endif
