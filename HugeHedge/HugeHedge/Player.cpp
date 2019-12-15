//	Player.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-15

#include "Player.h"

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

#include <sstream>
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
		<< "W) " << (canMoveTo(FORWARD) ? "Go" : "Can't go") << " forward.\n"
		<< "A) " << (canMoveTo(LEFT) ? "Go" : "Can't go") << " left.\n"
		<< "S) " << (canMoveTo(BACK) ? "Go" : "Can't go") << " back.\n"
		<< "D) " << (canMoveTo(RIGHT) ? "Go" : "Can't go") << " right.\n"
		<< "Q) Quit.\n";
	choice = std::toupper(std::cin.get());
	std::cin.ignore(100, '\n');

	switch( choice ) {
	case 'W':
		if( canMoveTo(FORWARD) )
			move(FORWARD);
		break;
	case 'A':
		if( canMoveTo(LEFT) )
			move(LEFT);
		break;
	case 'S' :
		if( canMoveTo(BACK) )
			move(BACK);
		break;
	case 'D':
		if( canMoveTo(RIGHT) )
		move(RIGHT);
		break;
	case 'Q':
		return;
	default:
		std::cout << "Invalid input. Try again.\n";
		break;
	}
	system("pause");
	system("cls");
	options();
}