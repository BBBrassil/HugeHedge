//	HudgeHedge.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "IOManager.h"
#include "Player.h"
#include "Position.h"
#include "World.h"
#include <iostream>
using namespace std;

int main() {
	World* world = nullptr;
	Player* player = nullptr;

	try {
		world = new World();

		Position position;
		position.world = world;
		position.x = 7;
		position.y = 4;

		player = new Player(position);

		player->optionsMenu();

		delete world;
		world = nullptr;

		delete player;
		player = nullptr;
	}
	catch( IOManager::FileOpenFail ex ) {
		cout << "unhandled exception: failed to open file \"" << ex.getFileName() << "\".\n";

		delete world;
		world = nullptr;

		delete player;
		player = nullptr;
	}

	cout << "Exiting...\n\n";
	system("pause");
	return 0;
}