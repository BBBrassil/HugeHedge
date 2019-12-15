//	Tile.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-14

////////////////////////////////////////////////////////////////////////////////
/*	Abstract Tile class

	An abstract class for tile objects that can either block the player's
	movement or can be occupied by the player and other objects.

	Implemented by:
	- Path
	- UniqueTile
	- Wall
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef TILE_H
#define TILE_H

#include "Position.h"
#include <iostream>
#include <string>

class World;

class Tile {
private:
	Position position;
public:
	Tile(const Position& p) { position = p; }
	virtual std::string toString() const = 0;
	virtual char toChar() const = 0;
	virtual bool isWall() const = 0;
	World* getWorld() const { return position.world; }
	int getX() const { return position.x; }
	int getY() const { return position.y; }
	Tile* neighbor(const int& cardinal);
	Tile* operator++();
	Tile* operator++(int);
	Tile* operator--();
	Tile* operator--(int);
	friend std::ostream& operator<<(std::ostream& os, const Tile& t);
};

#endif