//	Exit.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "Exit.h"

////////////////////////////////////////////////////////////////////////////////
/*	onSolved()
	Fired when the player solves this tile's puzzle.

	Signals the world that the player has escaped the maze and won the game!

	- player: Player object who has solved the puzzle.
	- os: Any output stream.
*/
////////////////////////////////////////////////////////////////////////////////
void Exit::onSolved(Player& player, std::ostream& os) {
	os << seeSolvedMessage();
	getWorld()->setGameOver(true);
}