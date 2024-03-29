//	Wall.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-16

////////////////////////////////////////////////////////////////////////////////
/*	Wall class
	A generic tile class for tiles that block the player's movement.

	Implements the abstract Tile class.

	Uses static members for the name, token, etc that are shared between all
	Wall objects.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef WALL_H
#define WALL_H

#include "Tile.h"

#include "World.h"

class Wall : public Tile {
private:
	static std::string fileName;
	static std::string objectName;
	static std::string description;
	static char token;
	static void read(std::istream& ns);
public:
	Wall(const Position& p) : Tile(p) {}
	std::string getName() const { return objectName; }
	std::string toString() const { return description; }
	char toChar() const { return token; }
	bool isWall() const { return true; }
	friend void World::readTileData();
};

#endif