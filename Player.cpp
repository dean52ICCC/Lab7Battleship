#include "Player.h"
#include <iostream>
#include <iomanip>
#include <string>

//Constructor
Player::Player() :
	shipBoard(), firingBoard(), row(), col(), shipDirection(), shipSize(), ship() {

	//Set tiles on shipBoard and firingBoard to 0 (empty)
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			shipBoard[i][j] = 0;
			firingBoard[i][j] = 0;
		}
	}
	//Set ship starting values
	ship[0] = {"Carrier", 5, false, false, 0, 0, 0, 0};
	ship[1] = {"Battleship", 4, false, false, 0, 0, 0, 0 };
	ship[2] = {"Cruiser", 3, false, false, 0, 0, 0, 0 };
	ship[3] = {"Submarine", 3, false, false, 0, 0, 0, 0 };
	ship[4] = {"Destroyer", 2, false, false, 0, 0, 0, 0 };
}
//Destructor
Player::~Player() {}

//Prints the shipBoard
void Player::printShipBoard() {
	cout << "Ship Board" << endl;
	//Print column numbers
	for (int i = 0; i < 10; i++) {
		cout << setw(textWidth) << i + 1;
	}
	cout << endl;

	//Print row numbers and board
	for (int i = 0; i < 10; i++) {
		cout << i + 1;
		//Print board
		//0 = Empty, 1 = Ship, 2 = Hit, 3 = Miss
		for (int j = 0; j < 10; j++) {
			if(shipBoard[i][j] == 0)
				cout << setw(textWidth) << "~";
			else if (shipBoard[i][j] == 1)
				cout << setw(textWidth) << "#";
			else if (shipBoard[i][j] == 2)
				cout << setw(textWidth) << "H";
			else if (shipBoard[i][j] == 3)
				cout << setw(textWidth) << "M";
		}
		cout << endl;
	}
	//Print ships remaining
	cout << "Ships remaining: " << shipCount << endl;
}

//Prints the firingBoard
void Player::printFiringBoard() {
	cout << "Firing Board" << endl;
	//Print column numbers
	for (int i = 0; i < 10; i++) {
		cout << setw(textWidth) << i + 1;
	}
	cout << endl;

	//Print row numbers and board
	for (int i = 0; i < 10; i++) {
		cout << i + 1;
		//Print board
		//0 = Empty, 1 = Hit, 2 = Miss
		for (int j = 0; j < 10; j++) {
			if (firingBoard[i][j] == 0)
				cout << setw(textWidth) << "~";
			else if (firingBoard[i][j] == 1)
				cout << setw(textWidth) << "H";
			else if (firingBoard[i][j] == 2)
				cout << setw(textWidth) << "M";
		}
		cout << endl;
	}
}

//Places ships on shipBoard
void Player::placeShips() {
	//Initialize variables
	bool valid = true;
	int row;
	int col;
	int selected;
	string direction;

//Loop for selecting and placing ships
Selection:
	//Clear cin
	cin.clear();
	cin.ignore(10000, '\n');
	//Print shipBoard
	system("cls");
	printShipBoard();
	//Print ship selection menu
	cout << "Select a ship to place" << endl;
	cout << "1. Carrier";
	if (ship[0].placed == true) cout << " (placed)";

	cout << endl << "2. Battleship";
	if (ship[1].placed == true) cout << " (placed)";

	cout << endl << "3. Cruiser";
	if (ship[2].placed == true) cout << " (placed)";

	cout << endl << "4. Submarine";
	if (ship[3].placed == true) cout << " (placed)";

	cout << endl << "5. Destroyer";
	if (ship[4].placed == true) cout << " (placed)";
	cout << endl;

	//Get user input for ship selection
	cin >> selected;
	//Validate input
	if (selected > 5 || selected < 1) {
		cout << "Invalid selection, try again." << endl;
		system("pause");
		goto Selection;
	}
	//Decrement selected to match array index
	selected--;

	//Check if ship has already been placed
	if (ship[selected].placed == true) {
		cout << "Ship already placed, try again." << endl;
		system("pause");
		goto Selection;
	}

	//Output ship information
	cout << "Ship: " << ship[selected].shipName << endl;
	cout << "Size: " << ship[selected].size << endl;

	//Get user input for ship placement
	cout << "Enter the row, column, and direction (right or down) of the ship" << endl;
	cin >> row >> col >> direction;
	//Decrement row and col to match array index
	row--;
	col--;

	//Insert ship into shipBoard facing right
	if (direction == "right") {
		for (int i = 0; i < ship[selected].size; i++) {
			//Check if ship is out of bounds
			if (col + i > 9) {
				cout << "Invalid placement, try again." << endl;
				system("pause");
				goto Selection;
			} //Check if ship overlaps another ship
			else if (shipBoard[row][col + i] > 0) {
				cout << "Invalid placement, try again." << endl;
				system("pause");
				goto Selection;
			}
		}
		//If ship placement is valid, insert ship into shipBoard
			for (int i = 0; i < ship[selected].size; i++) {
				ship[selected].col = col;
				ship[selected].row = row;
				shipBoard[ship[selected].row][ship[selected].col + i] = 1;
				ship[selected].direction = 0;
			}
	} //Insert ship into shipBoard facing down
	else if (direction == "down") {
		//Check if ship is out of bounds
		for (int i = 0; i < ship[selected].size; i++) {
			if (row + i > 9) {
				cout << "Invalid placement, try again." << endl;
				system("pause");
				goto Selection;
			} //Check if ship overlaps another ship
			else if (shipBoard[row + i][col] > 0) {
				cout << "Invalid placement, try again." << endl;
				system("pause");
				goto Selection;
			}
		}
		//If ship placement is valid, insert ship into shipBoard
			for (int i = 0; i < ship[selected].size; i++) {
				ship[selected].col = col;
				ship[selected].row = row;
				shipBoard[ship[selected].row + i][ship[selected].col] = 1;
				ship[selected].direction = 1;
			}
	}
	//If input is invalid, return to selection
	else {
		cout << "Invalid input, try again." << endl;
		system("pause");
		goto Selection;
	}
	//Set ship as placed
	ship[selected].placed = true;
}

//Fires a shot at the enemy
void Player::fireShot(int enemyBoard[10][10]) {
Start:
	//Clear cin
	cin.clear();
	cin.ignore(10000, '\n');
	//Get user input for shot
	cout << "Enter the row and column of the shot" << endl;
	cin >> row >> col;
	//Decrement row and col to match array index
	row--;
	col--;
	//Check if shot is out of bounds
	if (row > 9 || row < 0 || col > 9 || col < 0) {
		cout << "Invalid input, try again." << endl;
		system("pause");
		goto Start;
	}
	//Check if spot is a water tile
	if (enemyBoard[row][col] == 0) {
		system("cls");
		firingBoard[row][col] = 2;
		printFiringBoard();
		printShipBoard();
		cout << "Miss!" << endl;
		enemyBoard[row][col] = 3;
	}
	//Check if spot is a ship tile
	else if (enemyBoard[row][col] == 1) {
		system("cls");
		firingBoard[row][col] = 1;
		printFiringBoard();
		printShipBoard();
		cout << "Hit!" << endl;
		enemyBoard[row][col] = 2;
	}
	//Print error if spot has already been fired at and go to start
	else {
		cout << "Already fired there!" << endl;
		system("pause");
		goto Start;
	}
	system("pause");
}

//Check if a ship is sunk
void Player::checkSink() {
	//Loop through ships
	for (int i = 0; i < 5; i++) {
		//Skip if ship is already sunk
		if (ship[i].sunk == true)
			continue;
		else {
			//Reset hits
			ship[i].hits = 0;
			//Loop through ship tiles
			for (int x = 0; x <= ship[i].size; x++) {
				//Check if ship is facing right and if tile is hit
				if (ship[i].direction == 0 && shipBoard[ship[i].row][ship[i].col + x] == 2) {
					ship[i].hits++;
				} 
				//Check if ship is facing down and if tile is hit
				else if (ship[i].direction == 1 && shipBoard[ship[i].row + x][ship[i].col] == 2) {
					ship[i].hits++;
				}
				//If all tiles are hit, set ship as sunk and decrement shipCount
				else if (ship[i].sunk == false && ship[i].hits == ship[i].size) {
					ship[i].sunk = true;
					shipCount--;
					cout << ship[i].shipName << " sunk!" << endl;
					system("pause");
				}
			}
		}
	}
}

//Ask if player wants to shoot or surrender
bool Player::continueGame() {
	//Initialize variables
	int selection = 0;
	//Print menu
	cout << "Make a selection" << endl;
	cout << "1. Fire a shot" << endl;
	cout << "2. Surrender" << endl;
	//Get user input
	Choice:
	cin >> selection;
	//Validate input
	if (selection == 1)
		return true;
	else if (selection == 2) {
		shipCount = 0;
		return false;
	}
	else {
		//Clear cin
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid selection, try again." << endl;
		goto Choice;
	}
}