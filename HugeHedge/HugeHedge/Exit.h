//	Exit.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

////////////////////////////////////////////////////////////////////////////////
/*	Exit class
	
	* Inherits from the PointOfInterest class.
	* Overrides the onSolved() method to allow the player to win the game.
*/
////////////////////////////////////////////////////////////////////////////////

#include "PointOfInterest.h"

class Exit : public PointOfInterest {
public:
	Exit(const Position& p, const std::string& fn) : PointOfInterest(p, fn) {}
	void onSolved(Player& player, std::ostream& os);
};