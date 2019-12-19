//	PointOfInterest.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

#include "PointOfInterest.h"

#include "Weapon.h"

////////////////////////////////////////////////////////////////////////////////
/*	Constructor

	! Throws a FileOpenFail exception if the file fails to open.
	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
PointOfInterest::PointOfInterest(const Position& p, const std::string& fn) : UniqueTile(p, fn) {
	inventory = std::unique_ptr<LinkedList<Item>>(new LinkedList<Item>());
	key = nullptr;
	reward = nullptr;
	solved = false;
}

////////////////////////////////////////////////////////////////////////////////
/*	addItem()
	Adds an item to the tile's inventory.
*/
////////////////////////////////////////////////////////////////////////////////
void PointOfInterest::addItem(Item& item) {
	inventory->insert(item);
}

////////////////////////////////////////////////////////////////////////////////
/*	onEnter()
	Fired when the player enters this tile.

	- player: Player object who has entered the tile.
	- os: Any output stream.
*/
////////////////////////////////////////////////////////////////////////////////
void PointOfInterest::onEnter(Player& player, std::ostream& os) {
	try {
		if( !inventory->empty() ) {
			player.examineMenu(this, os);
		}
		else
			os << *this << "\n\n";
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	onExamined()
	Fired when the player looks at this tile.

	Adds any items in the tile's inventory to the player's inventory.

	- player: Player object who has examined the tile.
	- os: Any output stream.
*/
////////////////////////////////////////////////////////////////////////////////
void PointOfInterest::onExamined(Player& player, std::ostream& os) {
	try {
		if( !solved ) {
			if( !isKeyRequired() || player.hasItem(*key) ) {
				setSolved(true);
				onSolved(player, os);
			}
			else {
				os << seeUnsolvedMessage() << "\n";
			}
		}
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	onSolved()
	Fired when the player solves this tile's puzzle.

	Displays a message and adds any items in the tile's inventory to the
	player's inventory.

	- player: Player object who has solved the puzzle.
	- os: Any output stream.
*/
////////////////////////////////////////////////////////////////////////////////
void PointOfInterest::onSolved(Player& player, std::ostream& os) {
	try {
		os << seeSolvedMessage() << "\n\n";
		if( *inventory )
			player.collectAll(*inventory);
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	operator>>
	Reads data from an input stream, storing it in the unique tile's fields

	! Throws an EndOfFile exception if the end of the input stream is reached
	  before the expected data is read.
	! Throws a BadString exception if data can't be read from a line because of
	  incorrect formatting.
*/
////////////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& ns, PointOfInterest& poi) {
	std::string line, data, itemFileName;

	try {
		// objectName
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		poi.objectName = data;

		// description
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		poi.description = data;

		// token
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		poi.token = data[0];

		// wall
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		if( data != "0" && data != "1" )
			throw IOManager::BadString(line);
		poi.wall = data[0] - '0';

		// key
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		if( data != "no" ) {
			poi.requiresKey = true;
			itemFileName = data.substr(data.find_last_of('.'), data.length() - 1);
			if( itemFileName == ".weapon" )
				poi.key = std::shared_ptr<Item>(new Weapon(data));
			else
				poi.key = std::shared_ptr<Item>(new Item(data));
		}
		else {
			poi.requiresKey = false;
		}

		// unSolvedMessage
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		poi.unsolvedMessage = data;

		// solvedMessage
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		poi.solvedMessage = data;

		// reward
		IOManager::getlineEOF(ns, line);
		data = IOManager::valueFrom(line);
		if( data != "no" ) {
			itemFileName = data.substr(data.find_last_of('.'), data.length() - 1);
			if( itemFileName == "weapon" )
				poi.reward = std::shared_ptr<Item>(new Weapon(data));
			else
				poi.reward = std::shared_ptr<Item>(new Item(data));
			poi.addItem(*poi.reward);
		}
	}
	catch( ... ) {
		throw;
	}
	return ns;
}