#ifndef Computer_h
#define Computer_h
#include <string>

using namespace std;
//Computer class
class Computer {
private:

public:
	//Constructor
	Computer();
	//Destructor
	~Computer();

	//Struct for ships
	struct Ships {
		//Variables
		string shipName;
		int size;
		bool sunk;
		int direction;
		int row;
		int col;
		int hits;
	};
	//Array of ships
	Ships ship[5];
	//Arrays for boards
	int shipBoard[10][10];
	int firingBoard[10][10];
	//Variables
	int previousRow;
	int previousCol;
	int successfulShot;
	int shipSize;
	int shipCount = 5;
	int row;
	int col;
	int textWidth = 5;
	int difficulty;
	string shipDirection;

	//Functions
	//Create a random number, requires max number
	int rNumber(int max);
	//Places ships on the board
	void placeShips();
	//Fire a shot, requires 2D array of enemy board
	void fireShot(int enemyBoard[10][10]);
	//Print the two boards
	void printFiringBoard();
	void printShipBoard();
	//Check if a ship is sunk
	void checkSink();
	//Select difficulty
	void difficultySelect();

};
#endif
