//	Item.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

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
	Item(const std::string& fn);
	std::string getName() const { return name; }
	std::string getDescription() const { return description; }
	virtual std::string toString() const;
	friend std::ostream& operator<<(std::ostream& os, Item& item);
	friend std::istream& operator>>(std::istream& ns, Item& item);
};

#endif