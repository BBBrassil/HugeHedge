//	Player.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-16

////////////////////////////////////////////////////////////////////////////////
/*	Player class
	Handles all actions the user can make in the game.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "LinkedList.h"
#include "Position.h"
#include <iostream>
#include <memory>

class Item;
class Tile;
class World;

class Player {
private:
	Position position;
	int facing;
	std::unique_ptr<LinkedList<Item>> inventory;
	bool canMoveTo(const int& relative) const;
	void move(const int& relative);
	void use(Item* item);
	std::string actionText(const int& relative) const;
public:
	Player(const Position& p);
	World* getWorld() const { return position.world; }
	int getX() const { return position.x; }
	int getY() const { return position.y; }
	int getFacing() const { return facing; }
	Tile* getTile(const int& relative) const;
	Tile* getCurrentTile() const;
	bool hasItem(const Item& item) const;
	void collectItem(Item& item);
	void doAction(const int& relative);
	void lookAt(Tile* tile);
	void mainMenu(std::ostream& os = std::cout);
	void optionsMenu(std::ostream& os = std::cout);
	void inventoryMenu(std::ostream& os = std::cout);
	void debug();
};

#endif