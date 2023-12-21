#ifndef Game_h
#define Game_h

//Game class
class Game {
	public:
		//Constructor
		Game();
		//Destructor
		~Game();

		//Variables
		int difficulty;
		int wins = 0;
		int losses = 0;

		//Functions
		//Game loop for player vs. computer
		void playerVsComputer();
		//Game loop for player vs. player
		void playerVsPlayer();
		//Game loop for computer vs. computer
		void computerVsComputer();
		//Print the menu
		void printMenu();
		//Print the boards
		void printPlayerBoards(class Player player);
		void printComputerBoards(class Computer computer);
		//View Singleplayer wins and losses
		void viewStats();
};
#endif