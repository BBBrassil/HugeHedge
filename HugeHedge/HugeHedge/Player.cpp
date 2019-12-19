//	Player.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-19

#include "Player.h"

#include "Direction.h"
#include "Exit.h"
#include "Map.h"
#include "Tile.h"
#include "World.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/*	Constructor
*/
////////////////////////////////////////////////////////////////////////////////
Player::Player(const Position& p) {
	position = p;
	facing = NORTH;
	inventory = std::unique_ptr<LinkedList<Item>>(new LinkedList<Item>());
}

////////////////////////////////////////////////////////////////////////////////
/*	getTile()
	Gets a tile in a given direction relative to the player.
	(FORWARD, RIGHT, BACK, LEFT)
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Player::getTile(const int& relative) const {
	int direction = Direction::navigate(getFacing(), relative);

	try {
		return getCurrentTile()->neighbor(direction);
	}
	catch( World::OutOfWorld ) {
		return getWorld()->getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	getCurrentTile()
	Gets the tile at the player's current location.
*/
////////////////////////////////////////////////////////////////////////////////
Tile* Player::getCurrentTile() const {
	try {
		return getWorld()->tile(getX(), getY());
	}
	catch( World::OutOfWorld ) {
		return getWorld()->getDefaultTile();
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	actionText()
	Returns a string with the action the player is allowed to perform.
	"Move" if they can move, "Look" otherwise.
*/
////////////////////////////////////////////////////////////////////////////////
std::string Player::actionText(const int& relative) const {
	std::stringstream ss;

	if( canMoveTo(relative) )
		ss << "Move " << Direction::relativeString(relative) << '.';
	else if( dynamic_cast<Exit*>(getTile(relative)) )
		ss << "Use the exit.";
	else
		ss << "Look " << Direction::relativeString(relative) << '.';

	return ss.str();
}

////////////////////////////////////////////////////////////////////////////////
/*	doAction()
	Makes the player perform an action.
	If they can move in a given direction, they move there.
	Otherwise, they look at the tile that lies in that direction.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::doAction(const int& relative) {
	std::string direction = Direction::relativeString(relative);
	Tile* tile = getTile(relative);

	try {
		system("cls");
		if( canMoveTo(relative) ) {
			std::cout << "You move " << direction << ".\n";
			move(relative);
		}
		else if( dynamic_cast<Exit*>(getTile(relative)) ) {
			lookAt(tile);
			face(relative);
		}
		else {
			std::cout << "You look " << direction << ".\n";
			lookAt(tile);
			face(relative);
		}
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	canMoveTo()
	Checks whether a player can move to a tile in a given relative direction.
	(FORWARD, RIGHT, BACK, LEFT)
*/
////////////////////////////////////////////////////////////////////////////////
bool Player::canMoveTo(const int& relative) const {
	return !(getTile(relative)->isWall());
}

////////////////////////////////////////////////////////////////////////////////
/*	face()
	Makes the player face a given relative direction.
	(FORWARD, RIGHT, BACK, LEFT)
*/
////////////////////////////////////////////////////////////////////////////////
void Player::face(const int& relative) {
	facing = Direction::navigate(getFacing(), relative);
}

////////////////////////////////////////////////////////////////////////////////
/*	move()
	Moves the player to another tile, in a given relative direction.
	(FORWARD, RIGHT, BACK, LEFT)

	Does NOT validate whether the player is ALLOWED to move in that direction.
	Only moves them.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::move(const int& relative) {
	try {
		int direction = Direction::navigate(getFacing(), relative);
		Tile* destination = getCurrentTile()->neighbor(direction);
		position.x = destination->getX();
		position.y = destination->getY();
		facing = direction;

		destination->onEnter(*this);
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	lookAt()
	Player looks at a tile, getting a description or interaction options.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::lookAt(Tile* tile) {
	tile->onExamined(*this);
}

////////////////////////////////////////////////////////////////////////////////
/*	hasItem()
	Returns true if a given item is found in the player's inventory.
*/
////////////////////////////////////////////////////////////////////////////////
bool Player::hasItem(const Item& item) const {
	return inventory->contains(item);
}

////////////////////////////////////////////////////////////////////////////////
/*	collectItem()
	Adds an item to the player's inventory.

	! Throws a FileOpenException if the map file fails to open.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::collectItem(Item& item) {
	try {
		std::cout << "Acquired item:\n" << item << '\n';
		inventory->insert(item);
		if( item == getWorld()->getMapItem() )
			mapFound();
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	collectAll()
	Adds all items from a list to the player's inventory.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::collectAll(LinkedList<Item>& list) {
	int numItems = list.size();
	bool hasMap = list.contains(getWorld()->getMapItem());

	if( numItems > 0 ) {
		std::cout << "Acquired item" << (numItems == 1 ? ":" : "s:") << "\n\n";
		list.print();
		list.move(*inventory);
	}
	if( hasMap )
		mapFound();
}

////////////////////////////////////////////////////////////////////////////////
/*	mapFound()
	Fired when the player finds the maze map.

	! Throws a FileOpenException if the map file fails to open.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::mapFound(std::ostream& os) {
	std::unique_ptr<IOManager> writer(new IOManager());

	os
		<< "You have found a map! This will make navigating the maze easier.\n"
		<< "[You can view the map in the menu. It has also been output to a file.]\n\n";
	try {
		writer->openOut("Map.txt");
		getWorld()->getWorldMap()->print(writer->file());
		writer->close();
	}
	catch( IOManager::FileOpenFail ) {
		throw;
	}}

////////////////////////////////////////////////////////////////////////////////
/*	mapMenu()
	Shows the map.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::mapMenu(std::ostream& os) {
	std::stringstream ss;
	std::string print;
	World* world = getWorld();
	if( hasItem(getWorld()->getMapItem()) ) {
		world->getWorldMap()->print(ss);
		print = ss.str();
		print[world->xyToIndex(getX(), (size_t)getY()) + (size_t)getY()] =
			(getFacing() == 0 ? '^' :
				getFacing() == 1 ? '>' :
				getFacing() == 2 ? 'V' :
				'<');
		os << print << "\n";
	}
	else {
		os << "[You don't have a map.]\n\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	mainMenu()
	Quits to the game's main menu.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::mainMenu(std::ostream& os) {
	getWorld()->setGameOver(false);
}

////////////////////////////////////////////////////////////////////////////////
/*	optionsMenu()
	Displays the player's standard options in the game.
	Runs recursively as long as the game isn't over.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::optionsMenu(std::ostream& os) {
	char choice;

	std::cout
		<< "W) " << actionText(FORWARD) << '\n'
		<< "A) " << actionText(LEFT) << '\n'
		<< "S) " << actionText(BACK) << '\n'
		<< "D) " << actionText(RIGHT) << '\n'
		<< '\n'
		<< "I) " << "View inventory.\n"
		<< "M) " << "View map.\n"
		<< "Q) Quit.\n"
		<< '\n'
		<< "> ";

	choice = std::toupper(std::cin.get());
	std::cin.ignore(100, '\n');

	switch( choice ) {
	case 'W':
		doAction(FORWARD);
		break;
	case 'A':
		doAction(LEFT);
		break;
	case 'S':
		doAction(BACK);
		break;
	case 'D':
		doAction(RIGHT);
		break;
	case 'I':
		system("cls");
		inventoryMenu();
		break;
	case 'M':
		system("cls");
		mapMenu(os);
		break;
	case 'Q':
		os << "\nQuitting to main menu...\n\n";
		getWorld()->setGameOver(true);
		break;
	default:
		std::cout << "\nInvalid input. Try again.\n";
		break;
	}

	system("pause");
	system("cls");

	if( getWorld()->getGameOver() )
		mainMenu();
	else
		optionsMenu();
}

////////////////////////////////////////////////////////////////////////////////
/*	examineMenu()
	Displays the player's options when interacting with a point of interest.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::examineMenu(PointOfInterest* poi, std::ostream& os) {
	char choice;
	std::string poiName = poi->getName();
	for( int i = 0; i < poiName.length(); i++ )
		poiName[i] = std::tolower(poiName[i]);

	try {
		std::cout
			<< "E) " << "Examine the " << poiName << '\n'
			<< "X) " << "Ignore it and move on.\n"
			<< '\n'
			<< "> ";

		choice = std::toupper(std::cin.get());
		std::cin.ignore(100, '\n');

		os << '\n';

		if( choice != 'E' && choice != 'X' ) {
			os << "\nInvalid input. Try again.\n";
			system("pause");
			system("cls");
			examineMenu(poi, os);
		}

		if( choice == 'E' ) {
			os << "\n\n";
			system("cls");
			poi->onExamined(*this, os);
		}
	}
	catch( ... ) {
		throw;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	inventoryMenu()
	Displays the player's items.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::inventoryMenu(std::ostream& os) {
	os << "INVENTORY\n\n";
	if( !(*inventory) )
		os << "[You have no items.]\n\n";
	else {
		inventory->print(os);
		os << "\n";
	}
}