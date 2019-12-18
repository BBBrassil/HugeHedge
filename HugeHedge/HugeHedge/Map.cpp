//	Map.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "Map.h"

#include "UniqueTile.h"
#include <cctype>
#include <sstream>


////////////////////////////////////////////////////////////////////////////////
/*	isOrdered()
	Returns whether a given tile should be listed in order in the table of
	contents.
*/
////////////////////////////////////////////////////////////////////////////////
bool Map::isOrdered(Tile* tile) const {
	return tile->toChar() == '0';
}

////////////////////////////////////////////////////////////////////////////////
/*	getKey()
	Determines what character to print for identifying a tile on the map.
*/
////////////////////////////////////////////////////////////////////////////////
char Map::getKey(Tile* tile) const {
	static int count = 0;

	if( isOrdered(tile) ) {
		count++;
		// 1 - 9
		if( count < 10 )
			return count + '0';
		// A - Z
		if( count < 36 )
			return count - 10 + 'A';
		// a - z
		if( count < 62 )
			return count - 36 + 'a';
	}
	return tile->toChar();
}

////////////////////////////////////////////////////////////////////////////////
/*	tocLine()
	Returns a properly-formatted table of contents line;

	- key:  Token on the map identifying a tile.
	- tile: Pointer to the tile this line describes.
*/
////////////////////////////////////////////////////////////////////////////////
std::string Map::tocLine(const char& key, const Tile* tile) const {
	std::stringstream ss;

	ss << key << ' ' << tile->getName() << '\n';

	return ss.str();
}

////////////////////////////////////////////////////////////////////////////////
/*	read()
	Reads map data from the world to determine the contents.
	tiles.
*/
////////////////////////////////////////////////////////////////////////////////
void Map::read() {
	Tile* tile = nullptr;
	std::vector<MapItem> mapItems;
	char key;
	std::stringstream toc;

	mapContents << '\n';
	for( int i = 0; i < world->size(); i++ ) {
		tile = world->tile(i);
		key = getKey(tile);
		mapContents << key;
		if( world->indexToX(i) == world->width() - 1 )
			mapContents << '\n';
		// If this tile is unique, add it to the table of contents
		if( dynamic_cast<UniqueTile*>(tile) ) {
			// Save ordered map items for later
			if( isOrdered(tile) ) {
				MapItem mapItem;
				mapItem.tile = tile;
				mapItem.key = key;
				mapItems.push_back(mapItem);
			}
			// Print unordered items first first
			else {
				toc << tocLine(key, tile);
			}
		}
	}
	// Ordered items added at the end
	for( auto i : mapItems )
		toc << tocLine(i.key, i.tile);
	mapContents << '\n' << toc.str() << '\n';
}

////////////////////////////////////////////////////////////////////////////////
/*	print()
	Prints a map of the tiles plus table of contents identifying any unique
	tiles.
*/
////////////////////////////////////////////////////////////////////////////////
void Map::print(std::ostream& os) {
	os << mapContents.str();
}
