//	World.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-24

#ifndef WORLD_H
#define WORLD_H

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
};

#endif