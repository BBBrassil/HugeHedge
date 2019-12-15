//	Item.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

////////////////////////////////////////////////////////////////////////////////
/*	Item class
	Class for things the player can collect.

	* Overloads the << operator to display the player's items in an inventory
	  screen.
	* Overloads the >> operator to read fields from an input stream.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef ITEM_H
#define ITEM_H

#include "ObjectReader.h"
#include <string>
#include <iostream>
#include <sstream>

class Item {
private:
	std::string fileName;
	std::string name;
	std::string description;
public:
	Item(const std::string& fn);
	std::string getName() const { return name; }
	std::string getDescription() const { return description; }
	virtual std::string toString() const;
	friend std::ostream& operator<<(std::ostream& os, Item& item);
	friend std::istream& operator>>(std::istream& ns, Item& item);
};

#endif