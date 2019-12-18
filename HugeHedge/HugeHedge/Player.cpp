//	Player.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "Player.h"

#include "Direction.h"
#include "Exit.h"
#include "Map.h"
#include "Tile.h"
#include "World.h"
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

	system("cls");
	if( canMoveTo(relative) ) {
		std::cout << "You move " << direction << ".\n";
		move(relative);
	}
	else if( dynamic_cast<Exit*>(tile) ) {
		lookAt(tile);
	}
	else {
		std::cout << "You look " << direction << ".\n";
		lookAt(tile);
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	canMoveTo()
	Checks whether a player can move to a tile in a given relative direction.
	(FORWARD, RIGHT, BACK, LEFT)
*/
////////////////////////////////////////////////////////////////////////////////
bool Player::canMoveTo(const int& relative) const {
	return !getTile(relative)->isWall();
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
	int direction = Direction::navigate(getFacing(), relative);
	Tile* destination = getCurrentTile()->neighbor(direction);
	position.x = destination->getX();
	position.y = destination->getY();
	facing = direction;

	destination->onEnter(*this);
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
*/
////////////////////////////////////////////////////////////////////////////////
void Player::collectItem(Item& item) {
	std::cout << "Acquired item:\n" << item << '\n';
	inventory->insert(item);
}

////////////////////////////////////////////////////////////////////////////////
/*	collectAll()
	Adds all items from a list to the player's inventory.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::collectAll(LinkedList<Item>& list) {
	int numItems = list.size();
	
	if( numItems > 0 ) {
		std::cout << "Acquired item" << (numItems == 1 ? ":" : "s:") << "\n\n";
		list.print();
		list.move(*inventory);
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	debug()
	Cheat function for debugging.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::debug() {
	std::stringstream ss;
	std::string print;
	World* world = getWorld();

	world->getWorldMap()->print(ss);
	print = ss.str();
	print[world->xyToIndex(getX(), (size_t)getY()) + (size_t)getY() + 1] =
		(getFacing() == 0 ? '^' :
			getFacing() == 1 ? '>' :
			getFacing() == 2 ? 'V' :
			'<');
	std::cout << print << "\n";

	std::cout << "Current position: (" << getX() << ", " << getY() << ") facing "
		<< Direction::toChar(getFacing()) << ".\n\n";
}

////////////////////////////////////////////////////////////////////////////////
/*	mainMenu()
	Displays the game main menu.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::mainMenu(std::ostream& os) {
	getWorld()->setGameOver(false);
}

////////////////////////////////////////////////////////////////////////////////
/*	optionsMenu()
	Displays the player's current options in the game.
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
		<< "I) " << "View inventory.\n"
		<< "Q) Quit.\n";
	std::cout << "X) " << "Debug.\n";
	std::cout << "\n> ";

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
	case 'Q':
		os << "\nQuitting to main menu...\n\n";
		getWorld()->setGameOver(true);
		break;
	case 'X':
		debug();
		break;
	default:
		std::cout << "\nInvalid input. Try again.\n\n";
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