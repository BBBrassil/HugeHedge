//	Position.h
//	Programmer: Brendan Brassil
//	Date Last Modified 2019-11-23

#ifndef POSITION_H
#define POSITION_H

class World;

////////////////////////////////////////////////////////////////////////////////
/*	Position struct
	Identifies where an object is - which world it's in, and at what coordinates
	in that world.
	- world:  Pointer to a World object.
	- x:      X-coordinate in the World.
	- y:      Y-coordinate in the World.
*/
////////////////////////////////////////////////////////////////////////////////
struct Position {

	World* world;
	int x;
	int y;
};

#endif