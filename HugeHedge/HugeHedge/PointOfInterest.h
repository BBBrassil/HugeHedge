//	PointOfInterest.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

////////////////////////////////////////////////////////////////////////////////
/*	PointOfInterest class
	
	A type of tile object the player can interact with to solve puzzles.

	* Inherits from the UniqueTile class.
	* Overrides the onEnter() and onExamined() methods to handle player
	  interaction with whatever interesting things may be found.
	  elements that occupy this tile.
	* Overloads the >> operator to read fields from an input stream.
*/
////////////////////////////////////////////////////////////////////////////////

#include "UniqueTile.h"

#include "IOManager.h"
#include "ObjectReader.h"
#include "Player.h"

class PointOfInterest : public UniqueTile {
private:
	std::unique_ptr<LinkedList<Item>> inventory;
	std::shared_ptr<Item> key;
	std::string unsolvedMessage;
	std::string solvedMessage;
	bool requiresKey;
	bool solved;
protected:
	std::string seeUnsolvedMessage() const { return unsolvedMessage; }
	std::string seeSolvedMessage() const { return solvedMessage; }
public:
	PointOfInterest(const Position& p, const std::string& fn);
	void addItem(Item& item);
	void onEnter(Player& player, std::ostream& os = std::cout);
	virtual void onExamined(Player& player, std::ostream& os = std::cout);
	virtual void onSolved(Player& player, std::ostream& os = std::cout);
	friend std::istream& operator>>(std::istream& ns, PointOfInterest& poi);
	bool isKeyRequired() const { return requiresKey; }
	Item& getKey() { return *key; }

	friend class World;
};
