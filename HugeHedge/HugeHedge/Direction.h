//	Direction.h
//	Programmer: Brendan Brassil
//	Date Last Modified 2019-12-14

#ifndef DIRECTION_H	
#define DIRECTION_H

#include <string>

////////////////////////////////////////////////////////////////////////////////
/*	Cardinal direction enumerator
*/
////////////////////////////////////////////////////////////////////////////////
enum { NORTH, EAST, SOUTH, WEST };

////////////////////////////////////////////////////////////////////////////////
/*	Relative direction enumerator
*/
////////////////////////////////////////////////////////////////////////////////
enum { FORWARD, RIGHT, BACK, LEFT};

////////////////////////////////////////////////////////////////////////////////
/*	Direction class
	An abstract class with static methods allowing allowing for conversion from
	a relative direction (left, right, opposite) to a cardinal direction
	(north, east, south, west) and for printing cardinal directions.
*/
////////////////////////////////////////////////////////////////////////////////
class Direction {
private:
	virtual void dummy() = 0; // needed to make this class abstract so we don't
							  // ever accidentally try to instantiate it
public:
	static int rightFrom(const int &cardinal);
	static int opposite(const int &cardinal);
	static int leftFrom(const int &cardinal);
	static int navigate(const int& cardinal, const int& relative);
	static char toChar(const int &cardinal);
	static std::string toString(const int &cardinal);
	static std::string toStringUpper(const int &cardinal);
	static std::string toStringMixed(const int &cardinal);

	///////////////////////////////////////////////////////////////////////////////
	/*	Misdirection exception
		Thrown when something tries to go in a direction (cardinal or relative)
		that doesn't exist (i.e. one that isn't a value of 0, 1, 2, or 3).
	*/
	///////////////////////////////////////////////////////////////////////////////
	class Misdirection {
	private:
		int direction;
	public:
		Misdirection(const int& d) { direction = d; }
		int getDirection() const { return direction; }
	};
};

#endif