//	World.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-24

#include "World.h"

#include "Path.h"
#include "Position.h"
#include "Tile.h"
#include "UniqueTile.h"
#include "Wall.h"
#include <fstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
	- fn: Name of text file used to read the tile layout.
*/
////////////////////////////////////////////////////////////////////////////////
World::World(const std::string& fn) {
	fileName = fn;

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
	Deallocates memory for the tiles array.
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

	! Throws an OpenFileFailure exception if the input file fails to open.
	! Throws a BadDimensions exception if the data read from the file will not
	  create a rectangular maze layout.
*/
////////////////////////////////////////////////////////////////////////////////
void World::setSize() {
	int row, col, length;
	std::string line;
	std::ifstream file(fileName);

	if( file.fail() )
		throw FileOpenFailure(fileName);

	try {
		std::getline(file, line);
		// World must have substance
		if( line == "" )
			throw BadDimensions();
		row = 1;
		col = line.length();
		while( std::getline(file, line) ) {
			row++;
			length = line.length();
			// World must be a rectangle
			if( length != col )
				throw BadDimensions();
		}

		rowCount = row;
		colCount = col;
	}
	catch( BadDimensions ) {
		file.close();
		throw;
	}

	file.close();
}

////////////////////////////////////////////////////////////////////////////////
/*	setupTiles()
	Runs setup methods for tiles and fills the world's tiles array.

	Determines which tiles to create by reading the layout from a text file.

	! Throws an OpenFileFailure exception if any input files fail to open.
*/
////////////////////////////////////////////////////////////////////////////////
void World::setupTiles() {
	std::string line;
	char ch;
	Position position;
	std::ifstream file;

	try {
		Path.setup();
		Wall.setup();
	}
	catch( Tile::FileOpenFailure ) {
		throw;
	}
	try {
		defaultTile = new UniqueTile("DefaultTile");
	}
	catch( Tile::FileOpenFailure ) {
		delete defaultTile;
		defaultTile = nullptr;
	}

	try {
		file.open(fileName);
		if( file.fail() )
			throw FileOpenFailure(fileName);

		tiles = new Tile*[tileCount];

		tileCount = 0;
		position.world = this;
		for( int i = 0; i < height(); i++ ) {
			std::getline(file, line);
			position.x = i;
			for( int j = 0; j < width(); j++ ) {
				ch = line[j];
				position.y = j;
				makeTile(ch, position);
				tileCount++;
			}
		}
		if( (tileCount + 1) < height() * width() )
			throw EndOfFile(fileName);
	}
	catch( FileOpenFailure ) {
		throw;
	}
	catch( EndOfFile ) {
		clear();
		file.close();
		throw;
	}

	file.close();
}

////////////////////////////////////////////////////////////////////////////////
/*	makeTile()
	Creates a Tile object of a given type at a given position.
	- type: Character determining type of tile to create.
	- position:  Position of the tile.
*/
////////////////////////////////////////////////////////////////////////////////
void makeTile(const char& type, const Position& position) {
	switch( type ) {
	default:
		Path(position);
		break;
	case '#':
		Wall(position);
		break;
	case '?':
		//PointOfInterest(position);
		break;
	case 'O':
		//MazeExit(position);
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	xyToIndex()
	Converts xy coordinates to an index in a 1D array.
*/
////////////////////////////////////////////////////////////////////////////////
int World::xyToIndex(const int& x, const int& y) {
	return (colCount * x) + y;
}

////////////////////////////////////////////////////////////////////////////////
/*	tile()
	Returns the Tile at the given xy coordinates in the World.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& World::tile(const int& x, const int& y) {
	if( !(x >= 0 && x < width()) || !(y >= 0 || y < height()) )
		return getDefaultTile();
	return *tiles[xyToIndex(x, y)];
}

////////////////////////////////////////////////////////////////////////////////
/*	defaultTile()
	Returns the default Tile object.

	Used for errors and when the player inspects a tile outside of the World.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& World::getDefaultTile() {
	return *defaultTile;
}

////////////////////////////////////////////////////////////////////////////////
/*	operator[]
	Returns the Tile at the given 1D index in the tiles array.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& World::operator[](const int& index) {
	if( index < 0 || index > tileCount )
		return getDefaultTile();
	return *tiles[index];
}

////////////////////////////////////////////////////////////////////////////////
/*	operator()
	Returns the Tile at the given xy coordinates in the World.
*/
////////////////////////////////////////////////////////////////////////////////
Tile& World::operator()(const int& x, const int& y) {
	return tile(x, y);
}