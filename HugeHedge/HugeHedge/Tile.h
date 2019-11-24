//	Tile.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-24

#ifndef TILE_H
#define TILE_H

#include "Position.h"
#include <string>

class World;

class Tile {
private:
	Position position;
public:
	Tile(const Position& p) { position = p; }
	virtual bool isWall() = 0;
	virtual char toChar() = 0;
	virtual std::string toString() = 0;
	World& getWorld() { return *position.world; }
	int getX() const { return position.x; }
	int getY() const { return position.y; }
	Tile& north();
	Tile& east();
	Tile& south();
	Tile& west();
	Tile& operator()(const int& x, const int& y);
	Tile& operator()(const int& cardinal);
	friend std::ostream operator<<(std::ostream& os, Tile& t);

	class FileOpenFailure {
	private:
		std::string fileName;
	public:
		FileOpenFailure(std::string s) { fileName = s; }
		void setFileName(std::string s) { fileName = s; }
		std::string getFileName() { return fileName; }
	};
};

#endif