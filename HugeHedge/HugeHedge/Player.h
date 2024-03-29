//	Player.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

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
class PointOfInterest;

class Player {
private:
	Position position;
	int facing;
	std::unique_ptr<LinkedList<Item>> inventory;
	bool canMoveTo(const int& relative) const;
	void face(const int& relative);
	void move(const int& relative);
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
	void collectAll(LinkedList<Item>& list);
	void mapFound(std::ostream& os = std::cout);
	void doAction(const int& relative);
	void lookAt(Tile* tile);
	void mainMenu(std::ostream& os = std::cout);
	void optionsMenu(std::ostream& os = std::cout);
	void examineMenu(PointOfInterest* poi, std::ostream& os = std::cout);
	void inventoryMenu(std::ostream& os = std::cout);
	void mapMenu(std::ostream& os = std::cout);
};

#endif