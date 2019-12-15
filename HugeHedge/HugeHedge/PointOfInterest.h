//	PointOfInterest.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

////////////////////////////////////////////////////////////////////////////////
/*	PointOfInterest class
	
	A type of tile object that contains a Mystery object with which the player
	can interact. Inherits from the UniqueTile class.
*/
////////////////////////////////////////////////////////////////////////////////

#include "UniqueTile.h"

#include "StreamReader.h"
#include "ObjectReader.h"

//#include "Mystery.h"
#include "Player.h"

class PointOfInterest : public UniqueTile {
private:
	std::string mysteryFileName = "";
	Mystery* mystery = nullptr;
public:
	PointOfInterest(const Position& p, const std::string& fn);
	//friend void Player::lookAt(Mystery* mystery);
	friend std::istream& operator>>(std::istream& ns, PointOfInterest& poi);
};

