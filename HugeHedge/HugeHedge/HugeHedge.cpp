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
	UniqueTile* def = new UniqueTile(wallPos, "default.tile");

	cout << def->toString() << ' ' << def->toChar() << ' ' << def->isWall() << ' '
		<< def->getX() << ' ' << def->getY() << endl;

	delete def;
	def = nullptr;

	cout << endl << endl;
	system("pause");
	return 0;
}