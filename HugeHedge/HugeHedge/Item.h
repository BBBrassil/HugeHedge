//	Item.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

////////////////////////////////////////////////////////////////////////////////
/*	Item class

	Class for things the player can collect.

	* Overloads relational <, <=, >, >=, ==, and != operators.
	* Overloads the << operator to display the player's items in an inventory
	  screen.
	* Overloads the >> operator to read fields from an input stream.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {
private:
	std::string fileName;
	std::string name;
	std::string description;
public:
	Item() {} //
	Item(const std::string& fn);
	std::string getName() const { return name; }
	std::string getDescription() const { return description; }
	virtual std::string toString() const;
	virtual void onAcquired(std::ostream& os = std::cout);
	bool operator<(const Item& right) const;
	bool operator>(const Item& right) const;
	bool operator==(const Item& right) const;
	bool operator<=(const Item& right) const;
	bool operator>=(const Item& right) const;
	bool operator!=(const Item& right) const;
	friend std::ostream& operator<<(std::ostream& os, Item& item);
	friend std::istream& operator>>(std::istream& ns, Item& item);
};

#endif