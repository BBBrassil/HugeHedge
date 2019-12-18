//	HudgeHedge.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "Player.h"
#include "Position.h"
#include "World.h"
#include <iostream>
using namespace std;

int main() {
	World* world = new World();
	Position position;
	position.world = world;
	position.x = 7;
	position.y = 4;

	Player* player = new Player(position);

	player->optionsMenu();

	delete world;
	world = nullptr;

	delete player;
	player = nullptr;

	cout << "Exiting...\n\n";
	system("pause");
	return 0;
}