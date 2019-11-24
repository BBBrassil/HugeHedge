//	Direction.h
//	Programmer: Brendan Brassil
//	Date Last Modified 2019-11-23

#include "Direction.h"

////////////////////////////////////////////////////////////////////////////////
/*	rightFrom()
	Finds the cardinal direction to the right of a given cardinal direction.
	e.g. East is right from North.

	Returns an integer corresponding to the cardinal direction enum.
	(NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3)

*/
////////////////////////////////////////////////////////////////////////////////
int Direction::rightFrom(const int &cardinal) {
	return (cardinal + 1) % 4;
}

////////////////////////////////////////////////////////////////////////////////
/*	opposite()
	Finds the cardinal direction opposite a given cardinal direction.
	e.g. South is opposite North.

	Returns an integer corresponding to the cardinal direction enum.
	(NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3)
*/
////////////////////////////////////////////////////////////////////////////////
int Direction::opposite(const int &cardinal) {
	return (cardinal + 2) % 4;
}

////////////////////////////////////////////////////////////////////////////////
/*	leftFrom()
	Finds the cardinal direction to the left of a given cardinal direction.
	e.g. West is left from North.

	Returns an integer corresponding to the cardinal direction enum.
	(NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3)
*/
////////////////////////////////////////////////////////////////////////////////
int Direction::leftFrom(const int &cardinal) {
	return (cardinal + 3) % 4;
}

////////////////////////////////////////////////////////////////////////////////
/*	toChar()
	Returns cardinal direction as a character.
	(N, E, S, W, or null character)
*/
////////////////////////////////////////////////////////////////////////////////
char Direction::toChar(const int &cardinal) {
	switch( cardinal ) {
	case NORTH: return 'N';
	case EAST: return 'E';
	case SOUTH: return 'S';
	case WEST: return 'W';
	}
	return '\0';
}

////////////////////////////////////////////////////////////////////////////////
/*	toString()
	Returns cardinal direction as a string.
	(north, east, south, west, or null)
*/
////////////////////////////////////////////////////////////////////////////////
std::string Direction::toString(const int &cardinal) {
	switch( cardinal ) {
	case NORTH: return "north";
	case EAST: return "east";
	case SOUTH: return "south";
	case WEST: return "west";
	}
	return "null";
}

////////////////////////////////////////////////////////////////////////////////
/*	toStringUpper()
	Returns cardinal direction as an uppercase string.
	(NORTH, EAST, SOUTH, WEST, or NULL)
*/
////////////////////////////////////////////////////////////////////////////////
std::string Direction::toStringUpper(const int &cardinal) {
	switch( cardinal ) {
	case NORTH: return "NORTH";
	case EAST: return "EAST";
	case SOUTH: return "SOUTH";
	case WEST: return "WEST";
	}
	return "NULL";
}

////////////////////////////////////////////////////////////////////////////////
/*	toStringMixed()
	Returns cardinal direction as a mixed case string.
	(North, East, South, West, or Null)
*/
////////////////////////////////////////////////////////////////////////////////
std::string Direction::toStringMixed(const int &cardinal) {
	switch( cardinal ) {
	case NORTH: return "North";
	case EAST: return "East";
	case SOUTH: return "South";
	case WEST: return "West";
	}
	return "Null";
}