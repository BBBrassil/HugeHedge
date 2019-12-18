//	Exit.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "Exit.h"

Exit::Exit(const Position& p, const std::string& fn) : PointOfInterest(p, fn) {
	key = std::shared_ptr<Item>(new Item("ExitKey.item"));
}

void Exit::onExamined(const Player& player, std::ostream& os) {
	if( !solved ) {
		os << toString() << '\n';
		if( player.hasItem(*key) ) {
			os << seeSolvedMessage();
			solved = true;
			getWorld()->setGameOver(true);
		}
		else {
			os << seeUnsolvedMessage();
		}
		os << "\n\n";
	}
}