//	Wall.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

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

#include <string>

class Wall : public Tile {
private:
	static std::string fileName;
	static std::string objectName;
	static char token;
public:
	Wall(const Position& p);
	void read(std::istream& ns);
	void setup(const std::string& fn);
	std::string toString() const { return objectName; }
	char toChar() const { return token; }
	bool isWall() const { return true; }
	friend int main();
};

#endif