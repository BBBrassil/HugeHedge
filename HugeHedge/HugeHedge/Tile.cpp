//	Tile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-29

#include "Tile.h"

#include "Direction.h"
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
		return getWorld().getDefaultTile();
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
		return getWorld().getDefaultTile();
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
		return getWorld().getDefaultTile();
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
		return getWorld().getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator++ prefix
	Returns the tile at the next index in the world's tiles array.
	Returns the default tile if the index goes out of bounds.	
	Can be used to iterate through all tiles in a world's array.

	Note: This method increments the index, not the tile; it does nothing to the
		  tile object. It only returns another tile reference. So it does
		  exactly the same thing as the postfix operator.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::operator++() const {
	try {
		return getWorld()[getWorld().xyToIndex(getX(), getY() + 1)];
	}
	catch( World::OutOfWorld ) {
		return getWorld().getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator++ postfix
	Returns the tile at the next index in the world's tiles array.
	Returns the default tile if the index goes out of bounds.	
	Can be used to iterate through all tiles in a world's array.

	Note: This method increments the index, not the tile; it does nothing to the
		  tile object. It only returns another tile reference. So it does
		  exactly the same thing as the prefix operator.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::operator++(int) const {
	return ++(*this);
}

////////////////////////////////////////////////////////////////////////////////
/*	operator-- prefix
	Returns the tile at the previous index in the world's tiles array.
	Returns the default tile if the index goes out of bounds.	
	Can be used to iterate through all tiles in a world's array.

	Note: This method decrements the index, not the tile; it does nothing to the
		  tile object. It only returns another tile reference. So it does
		  exactly the same thing as the postfix operator.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::operator--() const {
	try {
		return getWorld()[getWorld().xyToIndex(getX(), getY() - 1)];
	}
	catch( World::OutOfWorld ) {
		return getWorld().getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator-- postfix
	Returns the tile at the previous index in the world's tiles array.
	Returns the default tile if the index goes out of bounds.	
	Can be used to iterate through all tiles in a world's array.

	Note: This method decrements the index, not the tile; it does nothing to the
		  tile object. It only returns another tile reference. So it does
		  exactly the same thing as the prefix operator.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& Tile::operator--(int) const {
	return --(*this);
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
		return getWorld().getDefaultTile();
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
	return getWorld().getDefaultTile();
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