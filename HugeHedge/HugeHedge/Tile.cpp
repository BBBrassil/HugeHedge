//	Tile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-14

#include "Tile.h"

#include "Direction.h"
#include "World.h"

////////////////////////////////////////////////////////////////////////////////
/*	neighbor()
	Returns the tile that lies in a given cardinal direction.
	If that tile would be outside of the world, returns the default tile
	instead.

	! Throws a Misdirection exception upon invalid input.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Tile::neighbor(const int& cardinal) {
	Tile* t;

	try {
		switch( cardinal ) {
		case NORTH:
			t = getWorld()->tile(position.x, position.y - 1);
			break;
		case EAST:
			t = getWorld()->tile(position.x + 1, position.y);
			break;
		case SOUTH:
			t = getWorld()->tile(position.x, position.y + 1);
			break;
		case WEST:
			t = getWorld()->tile(position.x - 1, position.y);
			break;
		default:
			throw new Direction::Misdirection(cardinal);
			break;
		}
	}
	catch( World::OutOfWorld ) {
		t = getWorld()->getDefaultTile();
	}
	catch( Direction::Misdirection ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator++ prefix
	Returns the tile at the next index in the world's tiles array.
	Goes to tile 0 if it gets to the end of the array.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Tile::operator++() {
	Tile* temp;
	try {
		temp = getWorld()->tile(getWorld()->xyToIndex(getX(), getY() + 1));
	}
	catch( World::OutOfWorld ) {
		temp = getWorld()->tile(0);
	}
	return temp;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator++ postfix
	Returns the tile at the next index in the world's tile map.
	Goes to tile 0 if it gets to the end of the array.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Tile::operator++(int) {
	Tile* temp = this;
	++(*this);
	return temp;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator-- prefix
	Returns the tile at the next index in the world's tile map.
	Goes back to last tile if it gets to the beginning of the array.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Tile::operator--() {
	Tile* temp;
	try {
		temp = getWorld()->tile(getWorld()->xyToIndex(getX(), getY() - 1));
	}
	catch( World::OutOfWorld ) {
		temp = getWorld()->tile(getWorld()->size() - 1);
	}
	return temp;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator-- postfix
	Returns the tile at the next index in the world's tile map.
	Goes back to last tile if it gets to the beginning of the array.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Tile::operator--(int) {
	Tile* temp = this;
	--(*this);
	return temp;
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