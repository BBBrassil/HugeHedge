//	World.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-24

#ifndef WORLD_H
#define WORLD_H

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
	Tile& getDefaultTile();
	int xyToIndex(const int& x, const int& y);
	Tile& tile(const int& x, const int& y);
	Tile& operator[](const int& index);
	Tile& operator()(const int& x, const int& y);

	class BadDimensions {};

	class EndOfFile {
	private:
		std::string fileName;
	public:
		EndOfFile(std::string s) { fileName = s; }
		std::string getFileName() { return fileName; }
	};

	class FileOpenFailure {
	private:
		std::string fileName;
	public:
		FileOpenFailure(std::string s) { fileName = s; }
		std::string getFileName() { return fileName; }
	};
};

#endif