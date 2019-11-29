//	World.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-28

#include "World.h"

#include "Path.h"
#include "Position.h"
#include "StreamReader.h"
#include "Tile.h"
#include "UniqueTile.h"
#include "Wall.h"
#include <fstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
	- s: Name of text file used to read the tile layout.
*/
////////////////////////////////////////////////////////////////////////////////
World::World(const std::string& s) {
	fileName = s;

	try {
		setSize();
		setupTiles();
	}
	catch( BadDimensions ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	Destructor
*/
////////////////////////////////////////////////////////////////////////////////
World::~World() {
	clear();
}

////////////////////////////////////////////////////////////////////////////////
/*	clear()
	Deallocates memory for the tiles array and defaultTile.
*/
////////////////////////////////////////////////////////////////////////////////
void World::clear() {
	delete[] tiles;
	tiles = nullptr;

	delete defaultTile;
	defaultTile = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/*	setWorldSize()
	Setup function to determine the dimensions of the World.

	Reads from a file using the file name that was set in the constructor and
	counts the number of rows and columns in the file to determine the world's
	height, width, and tile count.

	! Throws a FileOpenFailure exception if the input file fails to open.
	! Throws a BadDimensions exception if the data read from the file will not
	  create a rectangular maze layout.
*/
////////////////////////////////////////////////////////////////////////////////
void World::setSize() {
	int row, col, length;
	std::string line;
	std::ifstream file(fileName);
	StreamReader* reader = new StreamReader();

	try {
		reader->open(fileName);
	}
	catch( StreamReader::FileOpenFail ) {
		delete reader;
		reader = nullptr;
		throw;
	}

	try {
		std::getline(file, line);
		// World must have substance
		if( line == "" )
			throw BadDimensions(fileName);
		row = 1;
		col = line.length();
		while( std::getline(file, line) ) {
			row++;
			length = line.length();
			// World must be a rectangle
			if( length != col )
				throw BadDimensions(fileName);
		}

		rowCount = row;
		colCount = col;
	}
	catch( BadDimensions ) {
		reader->close();
		delete reader;
		reader = nullptr;
		throw;
	}

	reader->close();
	delete reader;
	reader = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/*	setupTiles()
	Runs setup methods for tiles and fills the world's tiles array.

	Determines which tiles to create by reading the layout from a text file.

	! Throws a FileOpenFail exception if any input files fail to open.
	! Throws an EndOfFile exception if the end of a file is reached before setup
	  is complete.
*/
////////////////////////////////////////////////////////////////////////////////
void World::setupTiles() {
	std::string line;
	char ch;
	Position position;
	std::ifstream file;
	StreamReader* reader = new StreamReader();

	try {
		position.world = this;
		position.x = -1;
		position.y = -1;
		defaultTile = new UniqueTile(position, "Default.tile");
	}
	catch( StreamReader::FileOpenFail ) {
		delete defaultTile;
		defaultTile = nullptr;
		throw;
	}

	try {
		reader->open(fileName);

		tiles = new Tile*[tileCount];

		tileCount = 0;
		position.world = this;
		for( int i = 0; i < height(); i++ ) {
			std::getline(file, line);
			position.x = i;
			for( int j = 0; j < width(); j++ ) {
				ch = line[j];
				position.y = j;
				//makeTile(ch, position);
				tileCount++;
			}
		}
		if( (tileCount + 1) < height() * width() )
			throw StreamReader::EndOfFile(fileName);
	}
	catch( StreamReader::FileOpenFail ) {
		throw;
	}
	catch( ... ) {
		clear();
		reader->close();
		delete reader;
		reader = nullptr;
		throw;
	}

	file.close();
}

////////////////////////////////////////////////////////////////////////////////
/*	makeTile()
	Creates a Tile object of a given type at a given position.
	- type:      Character determining type of tile to create.
	- position:  Position of the tile.
*/
////////////////////////////////////////////////////////////////////////////////

/*
void makeTile(const char& type, const Position& position) {
	switch( type ) {
	default:
		Path* t = new Path(position);
		t->setup("Path.tile");
		break;
	case '#':
		Wall* t = new Wall(position);
		t->setup("Wall.tile");
		break;
	case '?':
		//PointOfInterest(position);
		break;
	case 'O':
		//MazeExit(position);
		break;
	}
}

*/
////////////////////////////////////////////////////////////////////////////////
/*	getDefaultTile()
	Returns the default Tile object.

	Used for errors and when the player inspects a tile outside of the World.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& World::getDefaultTile() const {
	return *defaultTile;
}

////////////////////////////////////////////////////////////////////////////////
/*	xyToIndex()
	Converts xy coordinates to an index in a 1D array.
*/
////////////////////////////////////////////////////////////////////////////////
int World::xyToIndex(const int& x, const int& y) const {
	return (colCount * x) + y;
}

////////////////////////////////////////////////////////////////////////////////
/*	indexToX()
	Converts an index in a 1D array to an x-coordinate in a 2D plane.
*/
////////////////////////////////////////////////////////////////////////////////
int World::indexToX(const int& index) const {
	return index % colCount;
}

////////////////////////////////////////////////////////////////////////////////
/*	indexToY()
	Converts an index in a 1D array to a y-coordinate in a 2D plane.
*/
////////////////////////////////////////////////////////////////////////////////
int World::indexToY(const int& index) const {
	return index / colCount;
}

////////////////////////////////////////////////////////////////////////////////
/*	tile()
	Returns the Tile at the given xy coordinates in the World.

	Returns the default tile if these coordinates fall outside the World.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& World::tile(const int& x, const int& y) const {
	if( !(x >= 0 && x < width()) || !(y >= 0 || y < height()) )
		throw OutOfWorld((World*)this, x, y);
	try {
		return *tiles[xyToIndex(x, y)];
	}
	catch( OutOfWorld ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator[]
	Returns the Tile at the given 1D index in the tiles array.

	Returns the default tile if the given index is out of bounds.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& World::operator[](const int& index) const {
	if( index < 0 || index > tileCount )
		throw OutOfWorld((World*)this, index);
	return *tiles[index];
}

////////////////////////////////////////////////////////////////////////////////
/*	operator()
	Returns the Tile at the given xy coordinates in the World.

	Returns the default tile if these coordinates fall outside the World.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& World::operator()(const int& x, const int& y) const {
	try {
		return tile(x, y);
	}
	catch( OutOfWorld ) {
		throw;
	}
}