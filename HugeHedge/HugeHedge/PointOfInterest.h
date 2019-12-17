//	PointOfInterest.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-16

////////////////////////////////////////////////////////////////////////////////
/*	PointOfInterest class
	
	A type of tile object the player can interact with to solve puzzles.
	Inherits from the UniqueTile class.
*/
////////////////////////////////////////////////////////////////////////////////

#include "UniqueTile.h"

#include "StreamReader.h"
#include "ObjectReader.h"

#include "Player.h"

class PointOfInterest : public UniqueTile {
protected:
	bool solved;
public:
	PointOfInterest(const Position& p, const std::string& fn);
	virtual void onSolved() {}
	friend std::istream& operator>>(std::istream& ns, PointOfInterest& poi);
};

