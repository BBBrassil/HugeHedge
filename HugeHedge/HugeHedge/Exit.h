//	Exit.h
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-16

#include "PointOfInterest.h"

#include <memory>

class Exit : public PointOfInterest {
private:
	std::shared_ptr<Item> key;
	std::string unsolvedMessage;
	std::string solvedMessage;
public:
	Exit(const Position& p, const std::string& fn);
	void onExamined(const Player& player, std::ostream& os = std::cout);
	std::string seeUnsolvedMessage() const { return unsolvedMessage; }
	std::string seeSolvedMessage() const { return solvedMessage; }
};