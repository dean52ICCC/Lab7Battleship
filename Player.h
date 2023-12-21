#ifndef Player_h
#define Player_h
#include <string>

using namespace std;
//Player class
class Player {
private:

public:
	//Constructor
	Player();
	//Destructor
	~Player();

	//Struct for ships
	struct Ships {
		string shipName;
		int size;
		bool sunk;
		bool placed;
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
	int shipSize;
	int shipCount = 5;
	int row;
	int col;
	int textWidth = 5;
	string shipDirection;

	//Functions
	//Check if a ship is sunk
	void checkSink();
	//Allow player to place ships
	void placeShips();
	//Fire a shot, requires 2D array of enemy board
	void fireShot(int enemyBoard[10][10]);
	//Print the two boards
	void printFiringBoard();
	void printShipBoard();
	//Ask if player wants to shoot or surrender
	bool continueGame();
};
#endif