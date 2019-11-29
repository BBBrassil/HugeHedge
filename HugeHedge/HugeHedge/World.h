//	World.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#ifndef WORLD_H
#define WORLD_H

#include "Position.h"
#include <string>

class Tile;

class World {
private:
	std::string fileName;
	Tile** tiles; // array of Tile pointers; acts like a 2D array, but isn't
	Tile* defaultTile;
	int rowCount;
	int colCount;
	int tileCount;
	void clear();
	void setSize();
	void setupTiles();
public:
	World(const std::string& s);
	~World();
	int height() const { return rowCount; }
	int width() const { return colCount; }
	int size() const { return tileCount; }
	Tile& getDefaultTile() const;
	int xyToIndex(const int& x, const int& y) const;
	int indexToX(const int& index) const;
	int indexToY(const int& index) const;
	Tile& tile(const int& x, const int& y) const;
	Tile& operator[](const int& index) const;
	Tile& operator()(const int& x, const int& y) const;

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
		OutOfWorld(World* w, const int&x, const int& y) {
			position.world = w;
			position.x = x;
			position.y = y;
		}
		Position getPosition() const { return position; }
	};
};

#endif