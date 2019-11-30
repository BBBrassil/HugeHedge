#include "Path.h"
#include "Position.h"
#include "StreamReader.h"
#include "UniqueTile.h"
#include "Wall.h"

#include <iostream>
#include <fstream>
using namespace std;

int main() {
	World* world = new World("World.txt");

	for( int i = 0; i < world->size(); i++ ) {
		Tile& t = (*world)[i];
		cout << t.toChar();
		if( t.getX() == world->width() - 1 )
			cout << endl;
	}

	delete world;
	world = nullptr;


	cout << endl << endl;
	system("pause");
	return 0;
}