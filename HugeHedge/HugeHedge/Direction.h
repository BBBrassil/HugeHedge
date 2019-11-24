//	Direction.h
//	Programmer: Brendan Brassil
//	Date Last Modified 2019-11-23

#ifndef DIRECTION_H	
#define DIRECTION_H

#include <string>

////////////////////////////////////////////////////////////////////////////////
/*	Cardinal direction enumerator
*/
////////////////////////////////////////////////////////////////////////////////
enum { NORTH, EAST, SOUTH, WEST };

////////////////////////////////////////////////////////////////////////////////
/*	Direction class
	An abstract class with static methods allowing allowing for conversion from
	a relative direction (left, right, opposite) to a cardinal direction
	(north, east, south, west) and for printing cardinal directions.
*/
////////////////////////////////////////////////////////////////////////////////
class Direction {
private:
	virtual void dummy() = 0; // only needed to make this class abstract so we
							  // don't ever try to make an instance of it
public:
	static int rightFrom(const int &cardinal);
	static int opposite(const int &cardinal);
	static int leftFrom(const int &cardinal);
	static char toChar(const int &cardinal);
	static std::string toString(const int &cardinal);
	static std::string toStringUpper(const int &cardinal);
	static std::string toStringMixed(const int &cardinal);
};

#endif