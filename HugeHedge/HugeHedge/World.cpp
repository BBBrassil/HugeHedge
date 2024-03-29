//	World.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

#include "World.h"

#include "Exit.h"
#include "IOManager.h"
#include "Map.h"
#include "Path.h"
#include "UniqueTile.h"
#include "Wall.h"
#include <algorithm>
#include <memory>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
/*	Default Constructor

	! Throws a FileOpenFailure exception if any input file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadDimensions exception if the data read from the tile map file
	  will not create a rectangular tile map.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
World::World() : World("World.map") {}

////////////////////////////////////////////////////////////////////////////////
/*	Constructor with file name
	- s: Name of text file used to read the tile layout.

	! Throws a FileOpenFailure exception if any input file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadDimensions exception if the data read from the tile map file
	  will not create a rectangular tile map.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
World::World(const std::string& s) {
	fileName = s;
	rowCount = 0;
	colCount = 0;
	tileCount = 0;

	try {
		setDimensions();
		makeTileMap();
		readTileData();
		placeItems();
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
/*	setDimensions()
	Setup function to determine the dimensions of the world.

	Reads from a file using the file name that was set in the constructor and
	counts the number of rows and columns in the file to determine the world's
	height, width, and tile count.

	! Throws a FileOpenFailure exception if the input file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadDimensions exception if the data read from the tile map file
	  will not create a rectangular tile map.
*/
////////////////////////////////////////////////////////////////////////////////
void World::setDimensions() {
	int row, col;
	std::string line;
	std::unique_ptr<IOManager> reader(new IOManager());
	try {
		reader->open(fileName);
		IOManager::getline(reader->file(), line);
		// World must have substance
		if( line == "" )
			throw BadDimensions(fileName);
		row = 1;
		col = (int)line.length();
		while( IOManager::getline(reader->file(), line) ) {
			row++;
			// World must be a rectangle
			if( line.length() != col )
				throw BadDimensions(fileName);
		}
		reader->close();

		rowCount = row;
		colCount = col;
		tileCount = row * col;
	}
	catch( IOManager::FileOpenFail ) {
		throw;
	}
	catch( IOManager::EndOfFile ) {
		reader->close();
		throw IOManager::EndOfFile(fileName);
	}
	catch( BadDimensions ) {
		reader->close();
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	clear()
	Deallocates memory for the tile map array and default tile.
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

	delete worldMap;
	worldMap = nullptr;

	delete mapItem;
	mapItem = nullptr;

}

////////////////////////////////////////////////////////////////////////////////
/*	makeTileMap()
	Fills the world's tiles array. Reads all tile member data from the
	appropriate files.

	Determines which tiles to create by reading the layout from a text file.

	! Throws a FileOpenFail exception if any input file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before all the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void World::makeTileMap() {
	std::unique_ptr<IOManager> reader(new IOManager());
	Position position;
	std::string line;
	std::stringstream ss;
	char type;

	tileMap = new Tile * [tileCount];
	exit = nullptr;
	try {
		reader->open(fileName);
		position.world = this;
		// Ignore comments and get only map data characters
		while( IOManager::getline(reader->file(), line) )
			ss << line;
		// Creat a tile for each character read
		for( int i = 0; i < size(); i++ ) {
			ss >> type;
			// Set tile position
			position.x = indexToX(i);
			position.y = indexToY(i);
			// Determine type of tile to create
			switch( type ) {
			case '#':
				tileMap[i] = new Wall(position);
				break;
			case '-':
				tileMap[i] = new Exit(position, "Exit.tile");
				exit = (Exit*)(tileMap[i]);
				break;
			case 'B':
				tileMap[i] = new UniqueTile(position, "BirdBath.tile");
				break;
			case 'C':
				tileMap[i] = new UniqueTile(position, "CropCircle.tile");
				break;
			case 'D':
				tileMap[i] = new PointOfInterest(position, "Shed.tile");
				break;
			case 'F':
				tileMap[i] = new PointOfInterest(position, "Fountain.tile");
				break;
			case 'G':
				tileMap[i] = new PointOfInterest(position, "Garden.tile");
				break;
			case 'S':
				tileMap[i] = new PointOfInterest(position, "Statue.tile");
				break;
			case 'T':
				tileMap[i] = new PointOfInterest(position, "Tree.tile");
				break;
			case 'Z':
				tileMap[i] = new PointOfInterest(position, "Gazebo.tile");
				break;
			default:
				tileMap[i] = new Path(position);
				break;
			}
		}
		reader->close();
	}
	catch( IOManager::FileOpenFail ) {
		clear();
		throw;
	}
	catch( IOManager::EndOfFile ) {
		reader->close();
		clear();
		throw IOManager::EndOfFile(fileName);
	}
	catch( BadDimensions ) {
		reader->close();
		clear();
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	readTileData()
	Reads data for the tiles from files, storing it in their fields.

	* Friend function of the Wall and Path classes. Their static fields will be
	  assigned here and only here.

	! Throws a FileOpenFail exception if any input file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before all the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
void World::readTileData() {
	std::string tileFileName, line;
	Position position;
	std::unique_ptr<IOManager> tileReader(new IOManager());
	std::unique_ptr<ObjectReader<Exit>> exitReader;
	std::unique_ptr<ObjectReader<PointOfInterest>> poiReader;
	std::unique_ptr<ObjectReader<UniqueTile>> uniqueReader;
	std::unique_ptr<ObjectReader<Item>> itemReader;

	try {
		tileFileName = "Default.tile";
		position.world = this;
		position.x = -1;
		position.y = -1;
		defaultTile = new UniqueTile(position, tileFileName);
		exitReader = std::unique_ptr<ObjectReader<Exit>>(new ObjectReader<Exit>());
		poiReader = std::unique_ptr<ObjectReader<PointOfInterest>>(new ObjectReader<PointOfInterest>());
		uniqueReader = std::unique_ptr<ObjectReader<UniqueTile>>(new ObjectReader<UniqueTile>());
		Tile* t = nullptr;
		UniqueTile* uniqueTile = nullptr;
		PointOfInterest* poi = nullptr;
		Exit* ex;

		// Wall - static
		tileFileName = "Wall.tile";
		tileReader->open(tileFileName);
		Wall::read(tileReader->file());
		tileReader->close();

		// Path - static
		tileFileName = "Path.tile";
		tileReader->open(tileFileName);
		Path::read(tileReader->file());
		tileReader->close();

		// Non-static tiles
		// Dyynamically cast as needed to use the right type of ObjectReader
		for( int i = 0; i < size(); i++ ) {
			t = tile(i);
			if( dynamic_cast<Exit*>(t) ) {
				ex = dynamic_cast<Exit*>(t);
				tileFileName = ex->getFileName();
				exitReader->setFileName(tileFileName);
				exitReader->read(*ex);
				exitReader->close();
			}
			else if( dynamic_cast<PointOfInterest*>(t) ) {
				poi = dynamic_cast<PointOfInterest*>(t);
				tileFileName = poi->getFileName();
				poiReader->setFileName(tileFileName);
				poiReader->read(*poi);
				poiReader->close();
				// If this tile has requires a key to solve, keep note
				if( poi->isKeyRequired() )
					keyLocations.push_back(i);
				else
					spareLocations.push_back(i);
			}
			else if( dynamic_cast<UniqueTile*>(t) ) {
				uniqueTile = dynamic_cast<UniqueTile*>(t);
				tileFileName = uniqueTile->getFileName();
				uniqueReader->setFileName(tileFileName);
				uniqueReader->read(*uniqueTile);
				uniqueReader->close();
			}
		}
	}
	catch( IOManager::FileOpenFail ) {
		throw;
	}
	catch( IOManager::EndOfFile ) {
		tileReader->close();
		poiReader->close();
		uniqueReader->close();
		throw IOManager::EndOfFile(tileFileName);
	}
	catch( IOManager::BadString ex ) {
		tileReader->close();
		poiReader->close();
		uniqueReader->close();
		throw IOManager::BadString(ex.getString(), tileFileName);
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	placeItems()
	Places all the keys to solving puzzles and other handy items on point of
	interest tiles.
*/
////////////////////////////////////////////////////////////////////////////////
void World::placeItems() {
	Item* key;
	PointOfInterest* poi;

	// Shuffle the vectors for randomness
	std::random_shuffle(keyLocations.begin(), keyLocations.end());
	std::random_shuffle(spareLocations.begin(), spareLocations.end());

	// First thing to place is the exit key.
	key = &exit->getKey();


	// Next are all the other puzzle elements
	// (done one by one in order so it's possible to solve them all)
	for( int i : keyLocations ) {
		poi = dynamic_cast<PointOfInterest*>(tile(i));
		poi->addItem(*key);
		key = &poi->getKey();
	}

	// Place the last item in a spare point of interest
	poi = dynamic_cast<PointOfInterest*>(tile(spareLocations[0]));
	poi->addItem(*key);

	// Create the world map and add it to another spare point of interest
	worldMap = new Map(this);
	mapItem = new Item("Map.item");
	poi = dynamic_cast<PointOfInterest*>(tile(spareLocations[1]));
	poi->addItem(getMapItem());

	for( int i = 2; i < spareLocations.size(); i++ )
		poi->setSolved(true);
}

////////////////////////////////////////////////////////////////////////////////
/*	getDefaultTile()
	Returns the default tile object.
	Used for when the player inspects a tile that exists outside of the world.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* World::getDefaultTile() const {
	return defaultTile;
}

////////////////////////////////////////////////////////////////////////////////
/*	xyToIndex()
	Converts xy coordinates to an index in a 1D array.
*/
////////////////////////////////////////////////////////////////////////////////
int World::xyToIndex(const int& x, const int& y) const {
	return (colCount * y) + x;
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
/*	tile() overloaded for index
	Returns the tile at the given 1D index in world's tile map array.

	! Throws an OutOfWorld exception if this index falls outside of the array.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* World::tile(const int& index) const {
	if( index < 0 || index > tileCount )
		throw new OutOfWorld((World*)this, index);
	return tileMap[index];
}

////////////////////////////////////////////////////////////////////////////////
/*	tile() overloaded for x and y
	Returns the tile at the given xy coordinates in the world.

	! Throws an OutOfWorld exception if these coordinates fall outside of the
	  world.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* World::tile(const int& x, const int& y) const {
	if( x < 0 || x >= width() || y < 0 || y >= height() )
		throw new OutOfWorld((World*)this, x, y);
	return tileMap[xyToIndex(x, y)];
}