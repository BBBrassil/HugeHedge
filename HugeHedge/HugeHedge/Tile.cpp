//	Tile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#include "Tile.h"

#include "Direction.h"
#include "StreamReader.h"
#include "World.h"

////////////////////////////////////////////////////////////////////////////////
/*	north()
	Returns the Tile that lies to the north.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::north() const {
	try {
		return getWorld().tile(position.x, position.y + 1);
	}
	catch( World::OutOfWorld ) {
		return position.world->getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	east()
	Returns the Tile that lies to the east.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::east() const {
	try {
		return getWorld().tile(position.x + 1, position.y);
	}
	catch( World::OutOfWorld ) {
		return position.world->getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	south()
	Returns a pointer to the Tile that lies to the south.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::south() const {
	try {
		return getWorld().tile(position.x, position.y - 1);
	}
	catch( World::OutOfWorld ) {
		return position.world->getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	west()
	Returns the Tile that lies to the west.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::west() const {
	try {
		return getWorld().tile(position.x - 1, position.y);
	}
	catch( World::OutOfWorld ) {
		return position.world->getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator() overloaded for xy coordinates
	Returns the tile at the given xy coordinates in the world.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::operator()(const int& x, const int& y) const {
	try {
		return getWorld().tile(x, y);
	}
	catch( World::OutOfWorld ) {
		return position.world->getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator() overloaded for cardinal direction
	Returns the tile that lies in the given direction.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::operator()(const int& cardinal) const {
	switch( cardinal ) {
	case NORTH: return north(); break;
	case EAST: return east(); break;
	case SOUTH: return south(); break;
	case WEST: return west(); break;
	}
	return position.world->getDefaultTile();
}

////////////////////////////////////////////////////////////////////////////////
/*	operator<<
	Prints the pure virtual toString() method which classes that implement Tile
	will need to define.
*/
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Tile& t) {
	os << t.toString();
	return os;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>>
	Reads member variable data from an input stream.

	Calls the pure virtual read() method which classes that implement Tile will
	need to define.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& ns, Tile& t) {
	t.read(ns);

	return ns;
}