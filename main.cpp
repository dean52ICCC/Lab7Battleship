/*
	Brayden Dean
	C++ 2023
	Due: December/20/2023
	Lab 7
	Make a simple game of battleship. Need four boards, two for the player and two for the computer.
	The computer will randomly place its ships on the board. They cannot overlap or go off the board.
	The player will place their ships on the board using an x/y coordinate and a direction.
	They cannot overlap or go off the board. The computer will randomly fire at the player's board.
	The player should be given the option to view the boards, fire, or surrender. It should keep track
	of wins and losses
*/

#include <iostream>
#include "Game.h"

int main() {
	//Initialize variables
	bool quit = false;
	int mode = 0;
	//Create game object
	Game game;

	//Main loop
	while (!quit) {
		//Print menu
		system("cls");
		game.printMenu();
		//Select mode
		std::cin >> mode;
		if (mode == 1) {
			game.playerVsComputer();
		}
		else if (mode == 2) {
			game.playerVsPlayer();
		}
		else if (mode == 3) {
			game.computerVsComputer();
		}
		else if (mode == 4) {
			quit = true;
		}
		else {
			//Invalid input
			std::cout << "Invalid input. Please try again." << std::endl;
			system("pause");
		}
		//Clear cin
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}

	return 0;
}