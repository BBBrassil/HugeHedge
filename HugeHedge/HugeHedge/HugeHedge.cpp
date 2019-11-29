#include "Path.h"
#include "UniqueTile.h"
#include "Wall.h"

#include <iostream>
using namespace std;

int main() {
	Position wallPos;
	wallPos.world = nullptr;
	wallPos.x = 0;
	wallPos.y = 0;
	Wall* wall = new Wall(wallPos);
	wall->setup("Wall.tile");

	cout << wall->toString() << ' ' << wall->toChar() << ' ' << wall->isWall() << ' '
		<< wall->getX() << ' ' << wall->getY() << endl;

	delete wall;
	wall = nullptr;

	cout << endl << endl;
	system("pause");
	return 0;
}