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
	Tile& getDefaultTile() const;
	int xyToIndex(const int& x, const int& y);
	Tile& tile(const int& x, const int& y) const;
	Tile& operator[](const int& index) const;
	Tile& operator()(const int& x, const int& y) const;

	// File exception parent class
	class FileException {
	private:
		std::string fileName;
	public:
		FileException(const std::string& s) { fileName = s; }
		std::string getFileName() const { return fileName; }
	};

	// BadDimensions exception
	class BadDimensions : FileException {
	public:
		BadDimensions(const std::string& s) : FileException(s) {}
	};

	// EndOfFile exception
	class EndOfFile : FileException {
	public:
		EndOfFile(const std::string& s) : FileException(s) {}
	};

	// FileOpenFailure exception
	class FileOpenFailure : FileException {
	public:
		FileOpenFailure(const std::string& s) : FileException(s) {}
	};
};

#endif