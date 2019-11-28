//	Tile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-24

#include "Tile.h"

#include "Direction.h"
#include "World.h"

////////////////////////////////////////////////////////////////////////////////
/*	north()
	Returns the Tile that lies to the north.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::north() const {
	return getWorld().tile(position.x, position.y + 1);
}

////////////////////////////////////////////////////////////////////////////////
/*	east()
	Returns the Tile that lies to the east.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::east() const {
	return getWorld().tile(position.x + 1, position.y);
}

////////////////////////////////////////////////////////////////////////////////
/*	south()
	Returns a pointer to the Tile that lies to the south.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::south() const {
	return getWorld().tile(position.x, position.y - 1);
}

////////////////////////////////////////////////////////////////////////////////
/*	west()
	Returns the Tile that lies to the west.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::west() const {
	return getWorld().tile(position.x - 1, position.y);
}
////////////////////////////////////////////////////////////////////////////////
/*	operator() overloaded for xy coordinates
	Returns the tile at the given xy coordinates in the world.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::operator()(const int& x, const int& y) const {
	return getWorld().tile(x, y);
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
	default: return getWorld().getDefaultTile(); break;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator<<
	Prints toString() method.
*/
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Tile& t) {
	os << t.toString();
	return os;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>>
	Reads member variable data from an input stream.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& ns, Tile& t) {
	
}