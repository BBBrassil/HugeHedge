//	World.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-11-29

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
	rowCount = 0;
	colCount = 0;
	tileCount = 0;

	try {
		setSize();
		tileSetup();
		makeTileMap();
	}
	catch( ... ) {
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
	for( int i = 0; i < size(); i++ ) {
		if( tileMap[i] != nullptr ) {
			delete tileMap[i];
			tileMap[i] = nullptr;
		}
	}

	delete[] tileMap;
	tileMap = nullptr;

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
	std::unique_ptr<StreamReader> reader(new StreamReader());
	
	try {
		reader->open(fileName);
		std::getline(reader->file(), line);
		// World must have substance
		if( line == "" )
			throw BadDimensions(fileName);
		row = 1;
		col = line.length();
		while( std::getline(reader->file(), line) ) {
			row++;
			length = line.length();
			// World must be a rectangle
			if( length != col )
				throw BadDimensions(fileName);
		}

		rowCount = row;
		colCount = col;
		tileCount = row * col;
	}
	catch( StreamReader::FileOpenFail ) {
		throw;
	}
	catch( BadDimensions ) {
		reader->close();
		throw;
	}

	reader->close();
}

////////////////////////////////////////////////////////////////////////////////
/*	makeTile()
	Creates a Tile object of a given type at a given position.
	Returns a pointer to the tile.
	- type:     Character determining type of tile to create.
	- position: Position of the tile.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* World::makeTile(const char& type, const Position& position) {
	switch( type ) {
	default:
		return new Path(position);
	case '#':
		return new Wall(position);
	case '?':
		break;
	case 'O':
		break;
	}
}

void World::tileSetup() {
	std::string tileFileName, line;
	Position position;
	std::unique_ptr<StreamReader> reader(new StreamReader());
	
	try {
		tileFileName = "Default.tile";
		position.world = this;
		position.x = -1;
		position.y = -1;
		defaultTile = new UniqueTile(position, tileFileName);

		tileFileName = "Wall.tile";
		reader->open(tileFileName);
		Wall::read(reader->file());
		reader->close();
		
		tileFileName = "Path.tile";
		reader->open(tileFileName);
		Path::read(reader->file());
		reader->close();
	}
	catch( StreamReader::FileOpenFail ) {
		throw;
	}
	catch( StreamReader::EndOfFile ) {
		throw StreamReader::EndOfFile(tileFileName);
	}
	catch( StreamReader::BadString ex ) {
		throw StreamReader::BadString(ex.getString(), tileFileName);
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	makeTileSet()
	Fills the world's tiles array. Reads all tile member data from the
	appropriate files.

	Determines which tiles to create by reading the layout from a text file.

	! Throws a FileOpenFail exception if any input files fail to open.
	! Throws an EndOfFile exception if there is no data to read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void World::makeTileMap() {
	std::unique_ptr<StreamReader> reader(new StreamReader());
	Position position;
	std::string line;
	char type;
	
	tileMap = new Tile*[tileCount];
	try {
		reader->open(fileName);
		position.world = this;
		for( int i = 0; i < size(); i++ ) {
			reader->file() >> type;
			position.x = indexToX(i);
			position.y = indexToY(i);
			switch( type ) {
			case '#':
				tileMap[i] = new Wall(position);
				break;
			default:
				tileMap[i] = new Path(position);
				break;
			}
		}

		reader->close();
	}
	catch( StreamReader::FileOpenFail ) {
		clear();
		throw;
	}
	catch( StreamReader::EndOfFile ) {
		reader->close();
		clear();
		throw StreamReader::EndOfFile(fileName);
	}
	catch( BadDimensions ) {
		reader->close();
		clear();
		throw;
	}
}

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
		return *tileMap[xyToIndex(x, y)];
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
	return *tileMap[index];
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