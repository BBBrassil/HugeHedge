//	Weapon.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

#ifndef WEAPON_H
#define WEAPON_H

////////////////////////////////////////////////////////////////////////////////
/*	Weapon class
	
	Class for items that can do damage.
	Except there isn't a combat system, so this is just for show.

	* Inherits from the Item class.
	* Overrides the virtual toString() method.
*/
////////////////////////////////////////////////////////////////////////////////

#include "Item.h"

class Weapon : public Item {
private:
	int attack;
	int damage;
public:
	Weapon() : Item() { attack = 0; damage = 0; }
	Weapon(const std::string& fn);
	int getAttack() const { return attack; }
	int getDamage() const { return damage; }
	std::string toString() const;
	friend std::istream& operator>>(std::istream& os, Weapon& w);
};

#endif