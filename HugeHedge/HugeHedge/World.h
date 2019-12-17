//	World.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

#ifndef WORLD_H
#define WORLD_H

#include "Position.h"
#include <string>
#include <vector>

class Tile;

class World {
private:
	std::string fileName;
	Tile** tileMap; // array of Tile pointers; acts like a 2D array, but isn't
	Tile* defaultTile;
	int rowCount;
	int colCount;
	int tileCount;
	bool gameOver;
	void setDimensions();
	void clear();
public:
	World(const std::string& s);
	~World();
	void readTileData();
	void makeTileMap();
	int height() const { return rowCount; }
	int width() const { return colCount; }
	int size() const { return tileCount; }
	int xyToIndex(const int& x, const int& y) const;
	int indexToX(const int& index) const;
	int indexToY(const int& index) const;
	bool getGameOver() const { return gameOver; }
	void setGameOver(const bool& b) { gameOver = b; };
	Tile* getDefaultTile() const;
	Tile* tile(const int& index) const;
	Tile* tile(const int& x, const int& y) const;

	//////////////////////////////////////////////////////////////////////////////
	/* BadDimensions exception
		Thrown when the data read from a file would not produce a rectangular
		tile set for the World.
	*/
	//////////////////////////////////////////////////////////////////////////////
	class BadDimensions {
	private:
		std::string fileName;
	public:
		BadDimensions(const std::string& s) { fileName = s; }
		std::string getFileName() { return fileName; }
	};

	//////////////////////////////////////////////////////////////////////////////
	/*	OutOfWorld exception
		Thrown when something attempts to get a position that exists outside the
		world's array of tiles.
	*/
	//////////////////////////////////////////////////////////////////////////////
	class OutOfWorld {
	private:
		Position position;
	public:
		OutOfWorld(World* w, const int& n) {
			position.world = w;
			position.x = w->indexToX(n);
			position.y = w->indexToY(n);
		}
		OutOfWorld(World* w, int x, int y) {
			position.world = w;
			position.x = x;
			position.y = y;
		}
		Position getPosition() const { return position; }
	};
};

#endif