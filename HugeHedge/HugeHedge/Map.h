//	Map.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <string>
#include <sstream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/*	MapItem struct
	Simply contains a pointer to a tile and an associated character.
	Allows for map items to be temporarily stored so the table of contents will
	be printed in order.
*/
////////////////////////////////////////////////////////////////////////////////
struct MapItem {
	Tile* tile;
	char key;
};

////////////////////////////////////////////////////////////////////////////////
/*	Map class

	Handles all formatting of the map to the world that will help the player
	navigate the maze.
*/
////////////////////////////////////////////////////////////////////////////////
class Map {
private:
	std::stringstream mapContents;
	World* world;
	int count;
	bool isOrdered(Tile* tile) const;
	char getKey(Tile* tile);
	std::string tocLine(const char& key, const Tile* tile) const;
	void read();
public:
	Map(World* w) { world = w; count = 0; read(); }
	void print(std::ostream& os = std::cout);
};

#endif