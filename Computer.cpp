#include "Computer.h"
#include <iostream>
#include <iomanip>
#include <string>

//Constructor
Computer::Computer() {
	//Set random seed
	srand(time(NULL));

	//Set tiles on shipBoard and firingBoard to 0 (empty)
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			shipBoard[i][j] = 0;
			firingBoard[i][j] = 0;
		}
	}
	//Set ship starting values
	ship[0] = { "Carrier", 5, false, 0, 0, 0, 0 };
	ship[1] = { "Battleship", 4, false, 0, 0, 0, 0 };
	ship[2] = { "Cruiser", 3, false, 0, 0, 0, 0 };
	ship[3] = { "Submarine", 3, false, 0, 0, 0, 0 };
	ship[4] = { "Destroyer", 2, false, 0, 0, 0, 0 };

	placeShips();
}
//Destructor
Computer::~Computer() {}

//Generates a random number between 0 and given max
int Computer::rNumber(int max) {
	return rand() % max;
}

//Allows player to select a difficulty
void Computer::difficultySelect() {
	cout << "Select a difficulty." << endl;
	cout << "1. Easy" << endl;
	cout << "2. Medium" << endl;
	cout << "3. Hard" << endl;
	cout << "4. Impossible" << endl;
	cin >> difficulty;
}

//Prints the shipBoard
void Computer::printShipBoard() {
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
			if (shipBoard[i][j] == 0)
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

}

//Prints the firingBoard
void Computer::printFiringBoard() {
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

//Places ships on the shipBoard
void Computer::placeShips() {
	//Initialize variables
	bool valid = true;
	int direction;

	//Loop through each ship
	for (int x = 0; x < 5; x++) {
	Loop:
		//Reset valid
		valid = true;
		//Select a random direction
		direction = rNumber(2);

		//Select a random row and column
		ship[x].row = rNumber(10);
		ship[x].col = rNumber(10);

		//Insert ship into shipBoard facing right
		if (direction == 0) {
			for (int i = 0; i < ship[x].size; i++) {
				//Check if ship is out of bounds
				if (ship[x].col + i > 9) {
					valid = false;
					goto Loop;
				} //Check if ship overlaps another ship
				else if (shipBoard[ship[x].row][ship[x].col + i] > 0) {
					valid = false;
					goto Loop;
				}
			}
			//If ship placement is valid, insert ship into shipBoard
			if (valid == true) {
				for (int i = 0; i < ship[x].size; i++) {
					shipBoard[ship[x].row][ship[x].col + i] = 1;
					ship[x].direction = 0;
				}
			}
		} //Insert ship into shipBoard facing down
		else if (direction == 1) {
			//Check if ship is out of bounds
			for (int i = 0; i < ship[x].size; i++) {
				if (ship[x].row + i > 9) {
					valid = false;
					goto Loop;
				} //Check if ship overlaps another ship
				else if (shipBoard[ship[x].row + i][ship[x].col] > 0) {
					valid = false;
					goto Loop;
				}
			}
			//If ship placement is valid, insert ship into shipBoard
			if (valid == true) {
				for (int i = 0; i < ship[x].size; i++) {
					shipBoard[ship[x].row + i][ship[x].col] = 1;
					ship[x].direction = 1;
				}
			}
		}
	}
}

//Fires a shot at the enemy
void Computer::fireShot(int enemyBoard[10][10]) {
	//Initialize variables
	int row = 0;
	int col = 0;
	Fire:
	//Easy Difficulty
	if (difficulty == 1) {
		//Select a random row and column
		row = rNumber(10);
		col = rNumber(10);
		//Check if tile is water
		if (enemyBoard[row][col] == 0) {
			goto Miss;
		}
		//Check if tile is a ship
		else if (enemyBoard[row][col] == 1) {
			goto Hit;
		}
		//Invalid shot and go again
		else {
			goto Fire;
		}
	}
	//Medium Difficulty
	else if (difficulty == 2) {
		//If previous shot was a hit, fire around it
		if (successfulShot == 1) {
			//Select up/down or left/right
			//Up/Down
			if (rNumber(2) == 0) {
				//Select up or down
				if (rNumber(2) == 0)
					row = previousRow - 1;
				else
					row = previousRow + 1;
				col = previousCol;
			}
			//Left/Right
			else {
				//Select left or right
				if (rNumber(2) == 0)
					col = previousCol - 1;
				else
					col = previousCol + 1;
				row = previousRow;
			}
		}
		//If previous shot was a miss, fire randomly
		else if (successfulShot == 0) {
			row = rNumber(10);
			col = rNumber(10);
		}
		//Check if tile is water
		if (enemyBoard[row][col] == 0) {
			successfulShot = 0;
			goto Miss;
		}
		//Check if tile is a ship
		else if (enemyBoard[row][col] == 1) {
			previousCol = col;
			previousRow = row;
			successfulShot = 1;
			goto Hit;
		}
		//Invalid shot and go again
		else {
			successfulShot = 0;
			goto Fire;
		}
	}
	//Hard Difficulty
	else if (difficulty == 3) {
		//If previous shot was a hit, fire around it
		if (successfulShot == 1) {
			//Select up/down or left/right
			//Up/Down
			if (rNumber(2) == 0) {
				//Select up or down
				if (rNumber(2) == 0)
					row = previousRow - 1;
				else
					row = previousRow + 1;
				col = previousCol;
			}
			//Left/Right
			else {
				//Select left or right
				if (rNumber(2) == 0)
					col = previousCol - 1;
				else
					col = previousCol + 1;
				row = previousRow;
			}
		}
		//If previous shot was a miss, fire randomly
		else {
			//20% chance to select a random ship tile to fire at
			if (rNumber(10) < 2) {
				//Select a random tile
				row = rNumber(10);
				col = rNumber(10);
				//Loop until a ship tile is selected
				while (enemyBoard[row][col] != 1) {
					row = rNumber(10);
					col = rNumber(10);
				}
			}
			//80% chance to fire at a random tile
			else {
				row = rNumber(10);
				col = rNumber(10);
			}
		}
		//Check if tile is water
		if (enemyBoard[row][col] == 0) {
			successfulShot = 0;
			goto Miss;
		}
		//Check if tile is a ship
		else if (enemyBoard[row][col] == 1) {
			previousCol = col;
			previousRow = row;
			successfulShot = 1;
			goto Hit;
		}
		//Invalid shot and go again
		else {
			successfulShot = 0;
			goto Fire;
		}
	}
	//Impossible Difficulty
	else if (difficulty == 4) {
		//10% chance to fire at a random tile
		if (rNumber(10) < 1) {
			//Select a random tile
			row = rNumber(10);
			col = rNumber(10);
			//Check if tile is water
			if (enemyBoard[row][col] == 0) {
				goto Miss;
			}
			//Check if tile is a ship
			else if (enemyBoard[row][col] == 1) {
				goto Hit;
			}
		}
		//90% chance to fire at a ship tile
		else {
			//Loop through shipBoard
			for (int i = 0; i < 10; i ++) {
				for (int j = 0; j < 10; j++) {
					//If a ship tile is found, fire at it
					if (enemyBoard[i][j] == 1) {
						row = i;
						col = j;
						goto Hit;
					}
				}
			}
		}
	}
//Display hit or miss
Hit:
	//Print location of shot and that it was a hit
	cout << "Firing at " << row + 1 << ", " << col + 1 << endl;
	cout << "Hit!" << endl;
	//Update boards
	firingBoard[row][col] = 1;
	enemyBoard[row][col] = 2;
	goto End;
Miss:
	//Print location of shot and that it was a miss
	cout << "Firing at " << row + 1 << ", " << col + 1 << endl;
	cout << "Miss!" << endl;
	//Update boards
	firingBoard[row][col] = 2;
	enemyBoard[row][col] = 3;
	goto End;
End:
	system("pause");
}

//Check if a ship is sunk
void Computer::checkSink() {
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