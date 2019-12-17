#include "Path.h"
#include "Player.h"
#include "Position.h"
#include "StreamReader.h"
#include "UniqueTile.h"
#include "Wall.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	World* world = new World("World.map");
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