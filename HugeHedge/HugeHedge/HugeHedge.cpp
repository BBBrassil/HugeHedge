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
	position.x = 1;
	position.y = 1;

	Player* player = new Player(position);

	cout << endl;

	player->options();



	/*



	Tile* t;
	for (int i = 0; i < world->size(); i++) {
		t = world->tileMap[i];
		for (int j = 0; j < 4; j++) {
			Tile& neighbor = t->neighbor(j);
			cout << '\t' << Direction::toChar(j) << " from here is " << neighbor.getX() << ", " << neighbor.getY() << endl;
		}
		system("pause");
	}

	*/



	delete world;
	world = nullptr;

	delete player;
	player = nullptr;


	cout << endl << endl;
	system("pause");
	return 0;
}