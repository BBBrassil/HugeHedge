//	HudgeHedge.cpp
//	Programmer: Brendan Brassil
//	Date Last Modified: 2019-12-18

#include "Direction.h"
#include "IOManager.h"
#include "Player.h"
#include "Position.h"
#include "World.h"
#include <cctype>
#include <iostream>
using namespace std;

bool mainMenu(bool &quit);
void newGame(World* world, Player* player);

int main() {
	World* world = nullptr;
	Player* player = nullptr;
	bool quit = false;
	bool startNewGame = false;

	while( !quit && !startNewGame ) {
		startNewGame = mainMenu(quit);

		try {
			if( startNewGame ) {
				startNewGame = false;
				newGame(world, player);
			}
		}
		catch( IOManager::FileOpenFail ex ) {
			cout << "Exception: failed to open file \'" << ex.getFileName() << "\'. Exiting...\n";
		}
		catch( IOManager::BadString ex ) {
			cout << "Exception: Bad string in file \'" << ex.getFileName() << "\'. Exiting...\n";
		}
		catch( IOManager::EndOfFile ex ) {
			cout << "Exception: End of file \'" << ex.getFileName() << "\'. Exiting...\n";
		}
		catch( World::BadDimensions ex ) {
			cout << "Exception: Bad world dimensions in file \'" << ex.getFileName() << "\'. Exiting...\n";
		}
		catch( World::OutOfWorld ) {
			cout << "Exception: You slipped outside the world. That's one way to escape the maze...\n";
		}
		catch( Direction::Misdirection ex ) {
			cout << "Exception: " << ex.getDirection() << " is not a valid direction. Exiting...\n";
		}
	}

	delete world;
	world = nullptr;

	delete player;
	player = nullptr;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/*	mainMenu()
	Shows the main menu.

	Returns true if we are to start a new game, false otherwise.
*/
////////////////////////////////////////////////////////////////////////////////
bool mainMenu(bool& quit) {
	char choice;

		system("cls");
		cout
			<< "\n"
			<< "     _   _   _   _   _____   _____             \n"
			<< "    | | | | | | | | |  ___| |  ___|            \n"
			<< "    | |_| | | | | | | |     | |___             \n"
			<< "    |  _  | | | | | | |  _  |  ___|            \n"
			<< "    | | | | | |_| | | |_| | | |___             \n"
			<< "    |_| |_| |_____| |_____| |_____|            \n"
			<< "     _   _   _____   ____    _____   _____     \n"
			<< "    | | | | |  ___| |  _ \\  |  ___| |  ___|    \n"
			<< "    | |_| | | |___  | | | | | |     | |___     \n"
			<< "    |  _  | |  ___| | | | | | |  _  |  ___|    \n"
			<< "    | | | | | |___  | |_| | | |_| | | |___     \n"
			<< "    |_| |_| |_____| |_____| |_____| |_____|    \n"
			<< "\n\n"
			<< "    S) Start new game.\n"
			<< "    Q) Quit game.\n"
			<< "\n"
			<< "    > ";

		choice = std::toupper(std::cin.get());
		cin.ignore(100, '\n');

		switch( choice ) {
		case 'S':
			return true;
		case 'Q':
			quit = true;
			return false;
		default:
			mainMenu(quit);
		}
}

////////////////////////////////////////////////////////////////////////////////
/*	newGame()
	Starts a new game.
*/
////////////////////////////////////////////////////////////////////////////////
void newGame(World* world, Player* player) {
	system("cls");

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
	catch( ... ) {
		delete world;
		world = nullptr;

		delete player;
		player = nullptr;

		throw;
	}
}