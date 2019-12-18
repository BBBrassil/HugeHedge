//	Tile.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "Tile.h"

////////////////////////////////////////////////////////////////////////////////
/*	onEnter()
	Fired when the player enters this tile.

	Default definition does nothing fancy, but may be overridden by child
	classes.

	- player: Player object who has entered the tile.
	- os: Any output stream.
*/
////////////////////////////////////////////////////////////////////////////////
void Tile::onEnter(Player& player, std::ostream& os) {
	os << *this << "\n\n";
}

////////////////////////////////////////////////////////////////////////////////
/*	onExamined()
	Fired when the player looks at this tile.

	Default definition does nothing fancy, but may be overridden by child
	classes.

	- player: Player object who has examined the tile.
	- os: Any output stream.
*/
////////////////////////////////////////////////////////////////////////////////
void Tile::onExamined(const Player& player ,std::ostream& os) {
	os << *this << "\n\n";
}

////////////////////////////////////////////////////////////////////////////////
/*	neighbor()
	Returns the tile that lies in a given cardinal direction.
	If that tile would be located outside of the world, returns the default tile
	instead.

	! Throws a Misdirection exception upon invalid input.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Tile::neighbor(const int& cardinal) {
	try {
		switch( cardinal ) {
		case NORTH:
			return getWorld()->tile(position.x, position.y - 1);
			break;
		case EAST:
			return getWorld()->tile(position.x + 1, position.y);
			break;
		case SOUTH:
			return getWorld()->tile(position.x, position.y + 1);
			break;
		case WEST:
			return getWorld()->tile(position.x - 1, position.y);
			break;
		default:
			throw new Direction::Misdirection(cardinal);
			break;
		}
	}
	catch( World::OutOfWorld ) {
		return getWorld()->getDefaultTile();
	}
	catch( Direction::Misdirection ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator++ prefix
	Returns the tile at the next index in the world's tile map.
	Goes to tile 0 if it gets to the end of the array.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Tile::operator++() {
	try {
		return getWorld()->tile(getWorld()->xyToIndex(getX(), getY() + 1));
	}
	catch( World::OutOfWorld ) {
		return getWorld()->tile(0);
	}
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
	try {
		return getWorld()->tile(getWorld()->xyToIndex(getX(), getY() - 1));
	}
	catch( World::OutOfWorld ) {
		return getWorld()->tile(getWorld()->size() - 1);
	}
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