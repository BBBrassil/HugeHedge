//	Mystery.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

////////////////////////////////////////////////////////////////////////////////
/*	Mystery class

	Class for miscellaneous objects with which the player can interact to
	collect items and solve puzzles.

	* Overloads the >> operator to read fields from an input stream.
*/
////////////////////////////////////////////////////////////////////////////////


#include "LinkedList.h"
#include "Player.h"
#include <iostream>
#include <memory>
#include <string>

class Item;

class Mystery {
private:
	std::string fileName;
	std::string objectName;
	std::string unsolvedDescription;
	std::string solvedDescription;
	std::unique_ptr<LinkedList<Item>> inventory;
public:
	Mystery(const std::string& fn);
	friend void Player::lookAt(Mystery* mystery);
	friend std::istream& operator>>(std::istream& ns, Mystery& mystery);
};

