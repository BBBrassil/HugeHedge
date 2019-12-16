//	Player.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-16

#include "Player.h"

#include "Direction.h"
#include "Mystery.h"
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
	facing = 0;
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
/*	actionWord()
	Returns a string with the action the player is allowed to perform.
	"Move" if they can move, "Look" otherwise.
*/
////////////////////////////////////////////////////////////////////////////////
std::string Player::actionWord(const bool& canMove) const {
	if( canMove )
		return "Move";
	return "Look";
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

	system("cls");
	if( canMoveTo(relative) ) {
		std::cout << "You move " << direction << ".\n";
		lookAt(getTile(relative));
		move(relative);
	}
	else {
		std::cout << "You look " << direction << ".\n";
		lookAt(getTile(relative));
	}
}

////////////////////////////////////////////////////////////////////////////////
/*	canMoveTo()
	Checks whether a player can move to a tile in a given relative direction.
	(FORWARD, RIGHT, BACK, LEFT)
*/
////////////////////////////////////////////////////////////////////////////////
bool Player::canMoveTo(const int& relative) {
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
}

////////////////////////////////////////////////////////////////////////////////
/*	lookAt() overloaded for Mystery objects
*/
////////////////////////////////////////////////////////////////////////////////
void Player::lookAt(Mystery* mystery) {

	inventory->steal(*(mystery->inventory));
}

////////////////////////////////////////////////////////////////////////////////
/*	lookAt() overloaded for Tile objects
	Gives the player a description of a tile.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::lookAt(Tile* tile) {
	std::cout << tile->toString() << "\n\n";
}

////////////////////////////////////////////////////////////////////////////////
/*	collectItem()
	Adds an item to the player's inventory.
*/
////////////////////////////////////////////////////////////////////////////////
void Player::collectItem(Item& item) {
	inventory->insert(item);
	item.onAcquired();
}



void Player::options() {
	char choice;

	std::stringstream ss;
	std::string print;

	World* world = getWorld();

	for( int i = 0; i < world->size(); i++ ) {
		ss << world->tile(i)->toChar();
		if( world->indexToX(i) == world->width() - 1 )
			ss << '\n';
	}
	print = ss.str();
	print[world->xyToIndex(getX(), (size_t)getY()) + (size_t)getY()] =
		(getFacing() == 0 ? '^' :
			getFacing() == 1 ? '>' :
			getFacing() == 2 ? 'V' :
			'<');
	std::cout << print << "\n\n";

	std::cout << "Current position: (" << getX() << ", " << getY() << ") facing "
		<< Direction::toChar(getFacing()) << ".\n";
	std::cout
		<< "W) " << actionWord(canMoveTo(FORWARD)) << " forward.\n"
		<< "A) " << actionWord(canMoveTo(LEFT)) << " left.\n"
		<< "S) " << actionWord(canMoveTo(BACK)) << " back.\n"
		<< "D) " << actionWord(canMoveTo(RIGHT)) << " right.\n"
		<< "Q) Quit.\n";
	choice = std::toupper(std::cin.get());
	std::cin.ignore(100, '\n');

	switch( choice ) {
	case 'W':
		doAction(FORWARD);
		break;
	case 'A':
		doAction(LEFT);
		break;
	case 'S' :
		doAction(BACK);
		break;
	case 'D':
		doAction(RIGHT);
		break;
	case 'Q':
		break;
	default:
		std::cout << "Invalid input. Try again.\n";
		break;
	}
	system("pause");
	system("cls");

	options();
}