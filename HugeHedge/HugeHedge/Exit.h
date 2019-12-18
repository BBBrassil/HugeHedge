//	Exit.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

////////////////////////////////////////////////////////////////////////////////
/*	Exit class
	
	* Inherits from the PointOfInterest class.
	* Overrides the onExamined() method to allow the player to unlock the Exit.
*/
////////////////////////////////////////////////////////////////////////////////

#include "PointOfInterest.h"

#include <memory>

class Item;

class Exit : public PointOfInterest {
private:
	std::shared_ptr<Item> key;
public:
	Exit(const Position& p, const std::string& fn);
	Item& getKey() { return *key; }
	void onExamined(const Player& player, std::ostream& os = std::cout);
};