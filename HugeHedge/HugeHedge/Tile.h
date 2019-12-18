//	Tile.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

////////////////////////////////////////////////////////////////////////////////
/*	Tile abstract class

	An abstract class for tile objects that can either block the player's
	movement or can be occupied by the player and other objects.

	* Overloads the ++ and -- operators to make iterating through all the tiles
	  a World easier.
	* Overloads the << operator via a pure virtual toString() method that child
	  classes will need to define.
	* Implemented by:
	  - Path
	  - UniqueTile
	    -> PointOfInterest
		   -> Exit
	  - Wall
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef TILE_H
#define TILE_H

#include "Direction.h"
#include "Position.h"
#include "World.h"
#include <iostream>
#include <string>

class Player;

class Tile {
private:
	Position position;
public:
	Tile(const Position& p) { position = p; }
	virtual std::string getName() const = 0;
	virtual std::string toString() const = 0;
	virtual char toChar() const = 0;
	virtual bool isWall() const = 0;
	virtual void onEnter(Player& player, std::ostream& os = std::cout);
	virtual void onExamined(const Player& player, std::ostream& os = std::cout);
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