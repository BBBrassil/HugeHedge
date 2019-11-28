//	Tile.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-27

#ifndef TILE_H
#define TILE_H

#include "Position.h"
#include <string>
#include <iostream>

class World;

class Tile {
private:
	Position position;
public:
	Tile(const Position& p) { position = p; }
	virtual void read(std::istream& ns, Tile& t) = 0;
	virtual bool isWall() const = 0;
	virtual char toChar() const = 0;
	virtual std::string toString() const = 0;
	World& getWorld() const { return *position.world; }
	int getX() const { return position.x; }
	int getY() const { return position.y; }
	Tile& north() const;
	Tile& east() const;
	Tile& south() const;
	Tile& west() const;
	Tile& operator()(const int& x, const int& y) const;
	Tile& operator()(const int& cardinal) const;
	friend std::ostream& operator<<(std::ostream& os, const Tile& t);
};

#endif