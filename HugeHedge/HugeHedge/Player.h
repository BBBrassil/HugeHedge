//	Player.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

////////////////////////////////////////////////////////////////////////////////
/*	Player class
	Handles all actions the user can make in the game.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"
#include "Position.h"

class Item;
class Mystery;
class Tile;
class World;

class Player {
private:
	Position position;
	int facing;
	bool canMoveTo(const int& direction);
	void move(const int& direction);
	void lookAt(const Mystery* mystery);
	void lookAt(const Tile* tile);
	void use(const Item* item);
	LinkedList<Item> inventory;
public:
	Player(const Position& p) { position = p; facing = 0; }
	World* getWorld() const { return position.world; }
	int getX() const { return position.x; }
	int getY() const { return position.y; }
	int getFacing() const { return facing; }
	Tile* getTile(const int& direction) const;
	Tile* getCurrentTile() const;
	void collectItem(const Item& item);
	void options();
	void mainMenu();
};

#endif