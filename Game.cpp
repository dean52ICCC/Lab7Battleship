#include "Game.h"
#include "Player.h"
#include "Computer.h"
#include <iostream>

//Constructor
Game::Game() : difficulty()
{
}

//Destructor
Game::~Game()
{
}

//Prints the menu
void Game::printMenu() {
	cout << "Welcome to Battleship!" << endl;
	cout << "----------------------" << endl;
	cout << "1. Player vs. Computer" << endl;
	cout << "2. Player vs. Player" << endl;
	cout << "3. Computer vs. Computer" << endl;
	cout << "4. Quit" << endl;
	cout << "Select a mode: ";
}

//Calls the print functions for the player's boards
void Game::printPlayerBoards(class Player player) {
	player.printFiringBoard();
	player.printShipBoard();
}

//Calls the print functions for the computer's boards
void Game::printComputerBoards(class Computer computer) {
	computer.printFiringBoard();
	computer.printShipBoard();
}

//Game loop for player vs. computer
void Game::playerVsComputer() {
	system("cls");
	//Create player and computer objects
	Player player;
	Computer computer;
	//Select difficulty
	computer.difficultySelect();
	//Allow player to place all 5 ships
	for (int i = 0; i < 5; i++) {
		player.placeShips();
	}
	//Loop until either player or computer has no ships remaining
	while (player.shipCount > 0 && computer.shipCount > 0) {
		//Print player's boards
		system("cls");
		printPlayerBoards(player);
		//Player fires a shot at the computer's board
		if (player.continueGame()) 
			player.fireShot(computer.shipBoard);
		else
			goto Lose;
		//Check if computer ship has been sunk
		computer.checkSink();
		//If computer has no ships remaining, player wins
		if (computer.shipCount == 0) {
			system("cls");
			cout << "You win!" << endl;
			wins = wins + 1;
			break;
			}
		//Computer fires a shot at the player's board
		computer.fireShot(player.shipBoard);
		//Check if player ship has been sunk
		player.checkSink();
		//If player has no ships remaining, computer wins
		if (player.shipCount == 0) {
			Lose:
			system("cls");
			cout << "You lose!" << endl;
			losses = losses + 1;
			break;
		}
	}
	//Delete player and computer objects
	player.~Player();
	computer.~Computer();
	system("pause");
	viewStats();
}

//Game loop for player vs. player
void Game::playerVsPlayer() {
	//Create player objects
	Player player1;
	Player player2;
	//Print instructions
	system("cls");
	cout << "Player 1, place your ships" << endl;
	system("pause");
	//Allow player 1 to place ships
	for (int i = 0; i < 5; i++) {
		player1.placeShips();
	}
	//Print instructions
	system("cls");
	cout << "Player 2, place your ships" << endl;
	system("pause");
	//Allow player 2 to place ships
	for (int i = 0; i < 5; i++) {
		player2.placeShips();
	}
	//Loop until either player has no ships remaining
	while (player1.shipCount > 0 && player2.shipCount > 0) {
		//Print player 1's boards
		system("cls");
		cout << "Player 1" << endl;
		system("pause");
		printPlayerBoards(player1);
		//Player 1 fires a shot at player 2's board
		if (player1.continueGame())
			player1.fireShot(player2.shipBoard);
		else
			goto Player1Lose;
		//Check if player 2 ship has been sunk
		player2.checkSink();
		//If player 2 has no ships remaining, player 1 wins
		if (player2.shipCount == 0) {
			Player2Lose:
			system("cls");
			cout << "Player 1 wins!" << endl;
			break;
		}
		//Print player 2's boards
		system("cls");
		cout << "Player 2" << endl;
		system("pause");
		printPlayerBoards(player2);
		//Player 2 fires a shot at player 1's board
		if (player2.continueGame())
			player2.fireShot(player1.shipBoard);
		else
			goto Player2Lose;
		//Check if player 1 ship has been sunk
		player1.checkSink();
		//If player 1 has no ships remaining, player 2 wins
		if (player1.shipCount == 0) {
			Player1Lose:
			system("cls");
			cout << "Player 2 wins!" << endl;
			break;
		}
	}
	//Delete player objects
	player1.~Player();
	player2.~Player();
	system("pause");
}

//Game loop for computer vs. computer
void Game::computerVsComputer() {
	//Create computer objects
	Computer computer1;
	Computer computer2;
	//Select difficulty for computer 1
	system("cls");
	cout << "Computer 1" << endl;
	computer1.difficultySelect();
	//Print computer 1's board
	system("cls");
	cout << "Computer 1's Board" << endl;
	computer1.printShipBoard();
	system("pause");
	//Select difficulty for computer 2
	system("cls");
	cout << "Select difficulty for Computer 2" << endl;
	computer2.difficultySelect();
	//Print computer 2's board
	system("cls");
	cout << "Computer 2's Board" << endl;
	computer2.printShipBoard();
	system("pause");
	//Loop until either computer has no ships remaining
	while (computer1.shipCount > 0 && computer2.shipCount > 0) {
		//Print computer 1's boards
		system("cls");
		cout << "Computer 1" << endl;
		printComputerBoards(computer1);
		system("pause");
		//Computer 1 fires a shot at computer 2's board
		computer1.fireShot(computer2.shipBoard);
		//Check if computer 2 ship has been sunk
		computer2.checkSink();
		//If computer 2 has no ships remaining, computer 1 wins
		if (computer2.shipCount == 0) {
			system("cls");
			cout << "Computer 1 wins!" << endl;
			break;
		}
		//Print computer 2's boards
		system("cls");
		cout << "Computer 2" << endl;
		printComputerBoards(computer2);
		system("pause");
		//Computer 2 fires a shot at computer 1's board
		computer2.fireShot(computer1.shipBoard);
		//Check if computer 1 ship has been sunk
		computer1.checkSink();
		//If computer 1 has no ships remaining, computer 2 wins
		if (computer1.shipCount == 0) {
			system("cls");
			cout << "Computer 2 wins!" << endl;
			break;
		}
	}
	//Delete computer objects
	computer1.~Computer();
	computer2.~Computer();
	system("pause");
}

void Game::viewStats() {
	//Print wins and losses
	system("cls");
	cout << "Wins: " << wins << endl;
	cout << "Losses: " << losses << endl;
	system("pause");
}