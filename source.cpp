/*
	Programmer: James Mars
	Title: Ship Battle
	Date: 11/3/15
	Filename: ship_battle.cpp
	Purpose: A game of ship battle
*/

#include <iostream>
using namespace std;

// prototyping
void inGameTitle(int);					// printout graphics
void instrDisplay(int);
void gameModeDisplayEasy(int);
void gameModeDisplayHard(int);
void topCoords(int);
void bottomCoord(int);
void userMapInit(char);					// maps
void mapEasy(char);
void mapHard(char);
void getCoordInt(int);					// input check
void getInt(int);
void getContinue(int);
// end prototyping

void menuPrint(){						// menu printout

	cout << endl;
	cout << "  -------------------------" << endl;
	cout << "  | .oO  Ship Battle  Oo. |" << endl;
	cout << "  -------------------------" << endl;
	cout << "  |                       |" << endl;
	cout << "  | 1. Play Easy Mode     |" << endl;
	cout << "  | 2. Play Hard Mode     |" << endl;
	cout << "  | 3. Instructions       |" << endl;
	cout << "  | 4. Exit Game          |" << endl;
	cout << "  |                       |" << endl;
	cout << "  -------------------------" << endl;
	cout << endl;
	cout << "  Select an option: ";				
}

void instrDisplay(){							// print instructions

	cout << "Ship Battle Instructions" << endl;
	cout << "------------------------" << endl;
	cout << endl;
	cout << "Ship Battle is a game of strategy." << endl;
	cout << endl;
	cout << "The gameboard is a grid of 10 x 10, 100 positions which" << endl;
	cout << "represent the ocean (~). You must fire on a position of X/Y" << endl;
	cout << "coordinates and attempt to destroy the ENEMY ships (E)." << endl;
	cout << endl;
	cout << "However, you must also avoid hitting and destroying your" << endl;
	cout << "own ships, FRIENDLIES (F). " << endl;
	cout << endl;
	cout << "Each ship takes up 3 spaces. The game is over when either all" << endl;
	cout << "of the ENEMY ships are sunk, or 1 of your FRIENDLY ships are sunk." << endl;
	cout << "If you fire on a position that has no ENEMY or FRIENDLY ships," << endl;
	cout << "an (X) will display a MISS." << endl;
	cout << endl;
	cout << "Easy Mode - Ships are spaced out farther from one another." << endl;
	cout << endl;
	cout << "Hard Mode - Enemy ships are much closer to friendly ships." << endl;
	cout << endl;
}

void userMapInit(char (&oceanArray)[10][10]){			// generate the initial user map

	for (int row = 0; row < 10; row++){					// loop

		for (int column = 0; column < 10; column++){

		oceanArray [row][column] = '~';					// set to ~ for default state
		}
	}
}

void mapEasy(char (&easyArray)[10][10]){			// set ships for easy map

	for(int i = 1; i < 4 ; i++){						// set friendly 1					
		easyArray[i][1] = 'F';
	}

	for(int i = 5; i < 8; i++){							// set friendly 2
		easyArray[8][i] = 'F';
	}

	for(int i = 6; i < 9; i++){							// set enemy 1
		easyArray[i][2] = 'E';
	}

	for(int i = 6; i < 9; i++){							// set enemy 2
		easyArray[4][i] = 'E';
	}
}

void mapHard(char (&hardArray)[10][10]){			// set ships for hard map

	for(int i = 6; i < 9 ; i++){						// set friendly 1
		hardArray[i][7] = 'F';
	}

	for(int i = 0; i < 3; i++){							// set friendly 2
		hardArray[0][i] = 'F';
	}

	for(int i = 1; i < 4; i++){							// set enemy 1
		hardArray[i][1] = 'E';
	}

	for(int i = 6; i < 9; i++){							// set enemy 2
		hardArray[i][6] = 'E';
	}
}

int getInt(){						//input check

	int i;
	bool checkInt = 0;

	while (checkInt == 0)
	{
		cin >> i;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number. ";
		}
		else if (i > 4 || i < 1)						// input range for menu 1-4
		{
			cout << i << " is not a valid menu option. Please try again." << endl;
		}
		else
		{
			checkInt = 1;
			return i;
		}
	}
	return 0;
}

int getCoordInt(){					// input check for coords

	int i;
	bool checkInt = 0;

	while (checkInt == 0)
	{
		cin >> i;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number from 1 - 10. ";
		}
		else if (i > 10 || i < 1)						// range check for coords 1-10
		{
			cout << i << " is not a valid menu option. Please try again." << endl;
		}
		else
		{
			checkInt = 1;
			return i;
		}
	}
	return 0;
}

char getContinue(){						//input check

	char i;
	bool checkInt = 0;

		while (checkInt == 0)
		{
			cin >> i;
			if (!cin){
				cin.clear();
				cin.ignore(50, '\n');
			}
			else if (i == 'Y' || i == 'N' || i == 'y' || i == 'n'){
				checkInt = 1;
				return i;
			}
			else{
				cout << "Invalid input" << endl;	
				cout << "Please enter Y or N" << endl;
				cin.clear();
				cin.ignore(50, '\n');
			}
		}
		return 0;
}	

void inGameTitle(){								// print top title

	cout << "  Ship Battle - ";
}

void gameModeDisplayEasy(){						// print game mode in title - easy
	cout << "EASY" << endl;
	cout << "  ------------------" << endl;
}

void gameModeDisplayHard(){						// print game mode in title - hard
	cout << "HARD" << endl;
	cout << "  ------------------" << endl;
}

void topCoords(){										// print top coord bar
	cout << endl;
	cout << "   1 2 3 4 5 6 7 8 9 10 - X " << endl;
	cout << "  ---------------------    " << endl;
}

void bottomCoord(){										// print bottom coord bar
	cout << "| ---------------------    " << endl;
	cout << "Y" << endl;
	cout << endl;
}

int main(){												// main function

	int choice1, choice2, menuOption, row, column, ship1Sunk, ship2Sunk;
	bool endProgram = 0, gameRun = 0, inputCheck = 0, lose = 0;
	char x, y, cont, userMap[10][10], easyMap[10][10], hardMap[10][10], currentGame[10][10];

	while (!endProgram){

		menuPrint();					// print menu
		menuOption = getInt();			// check input for menu
		cout << endl;

		switch(menuOption)				// menu option selection
		{
		case 1:								// play easy mode

			lose = 0;						// set initial states
			gameRun = 1;
			ship1Sunk = 0;
			ship2Sunk = 0;

			userMapInit(currentGame);				// print user ocean
			mapEasy(easyMap);						// call easy map into main

			while(gameRun == 1)							// set running game state
			{	
			inGameTitle();							// print game title
			gameModeDisplayEasy();					// print game mode
			topCoords();							// print top coord
			
			for (int row = 0; row < 10; row++){			// loop to print map
				
				if(row < 9){
					
					cout << row + 1 << "  ";
					}
					else{
						cout << row + 1 << " ";	
					}
	
				for (int column = 0; column < 10; column++){
				
				cout << currentGame[row][column] << " ";				// print current map
				}
				cout << endl;
			}

			bottomCoord();												// print bottom coord

			cout << "Enter your X / Y coordinates: " << endl;			// user input
			cout << "X: ";
			choice2 = getCoordInt() - 1;								// input check
			cout << "Y: ";
			choice1 = getCoordInt() - 1;								// input check
			cout << endl;

			if (easyMap[choice1][choice2] == 'E')						// evaluate if the hit was an enemy
			{
				cout << "\a";											// play sound

				currentGame[choice1][choice2] = 'E';					// change map to print enemy hit

				cout << "* You hit an enemy ship! *" << endl;			// printout	successful hit
				cout << endl;

				cout << "Continue Playing? (Y/N)" << endl;				// prompt user to continue or quit
				cont = getContinue();

				if(cont == 'N' || cont == 'n'){
					gameRun = 0;
				}
				else{
					gameRun = 1;	
				}

				if(currentGame[6][2] == 'E' && currentGame[7][2] == 'E' && currentGame[8][2] == 'E'){	// evaluate if enemy ship 1 is sunk
	
					cout << "\a";										// play sound
					cout << "\a";										// play sound
					cout << "\a";										// play sound

					cout << "* You sunk an enemy ship! *" << endl;		// print out successful sinking of an enemy ship
					cout << endl;
					ship1Sunk = 1;										// set value of sunk enemy ship 1
				}

				if(currentGame[4][6] == 'E' && currentGame[4][7] == 'E' && currentGame[4][8] == 'E'){	// evaluate if enemy ship 2 is sunk

					cout << "\a";										// play sound
					cout << "\a";										// play sound
					cout << "\a";										// play sound

					cout << "* You sunk an enemy ship! *" << endl;		// print out successful sinking of an enemy ship
					cout << endl;
					ship2Sunk = 1;										// set value of sunk enemy ship 2
				}		
			}
			else if (easyMap[choice1][choice2] == 'F')					// evaluate if the hit was a friendly
			{
				cout << "\a";											// play sound

				currentGame[choice1][choice2] = 'F';					// change map to print friendly hit

				cout << "** You hit a friendly ship! **" << endl;		// printout	successful friendly hit
				cout << endl;

				cout << "Continue Playing? (Y/N)" << endl;				// prompt user to continue or quit
				cont = getContinue();

				if(cont == 'N' || cont == 'n'){
					gameRun = 0;
				}
				else{
					gameRun = 1;	
				}

				if((currentGame[1][1] == 'F' && currentGame[2][1] == 'F' && currentGame[3][1] == 'F') || (currentGame[8][5] == 'F' && currentGame[8][6] == 'F' && currentGame[8][7] == 'F')){	// evaluate if either of friendly ships were sunk

					cout << "\a";										// play sound
					cout << "\a";										// play sound
					cout << "\a";										// play sound
		
					cout << "** You sunk a friendly ship! **" << endl;	// printout friendly ship sunk
					cout << endl;

					lose = 1;											// change game state for loss
				}
			}
			else{
				currentGame[choice1][choice2] = 'X';					// set map state for a miss
				cout << "~ Splash... You missed! ~" << endl;			// printout miss
				cout << endl;

				cout << "Continue Playing? (Y/N)" << endl;				// prompt user to continue or quit
				cont = getContinue();

				if(cont == 'N' || cont == 'n'){
					gameRun = 0;
				}
				else{
					gameRun = 1;	
				}
			}

			if(ship1Sunk == 1 && ship2Sunk == 1){						// print out if both enemy ships are sunk - win

					for (int row = 0; row < 10; row++){			// loop to print map
						if(row < 9){
							cout << row + 1 << "  ";
						}
						else{
							cout << row + 1 << " ";	
						}
						for (int column = 0; column < 10; column++){
							cout << currentGame[row][column] << " ";				// print current map
						}
						cout << endl;
					}
					cout << endl;

				cout << "Congratulations! You sunk all the enemy ships!" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "                  You Win!   " << endl;
				cout << endl;
				gameRun = 0;											// end game
				}
			else if(lose == 1){											// printout if a friendly ship is sunk - lose

					for (int row = 0; row < 10; row++){			// loop to print map
						if(row < 9){
							cout << row + 1 << "  ";
						}
						else{
							cout << row + 1 << " ";	
						}
						for (int column = 0; column < 10; column++){
							cout << currentGame[row][column] << " ";				// print current map
						}
						cout << endl;
					}
					cout << endl;

				cout << "Uh oh! You sunk one of your own ships. :(" << endl;
				cout << "You Lose" << endl;
				cout << endl;
				gameRun = 0;											//end game
				}
			}

			break;

		case 2:								// play hard mode

			lose = 0;						// set initial states
			gameRun = 1;
			ship1Sunk = 0;
			ship2Sunk = 0;

			userMapInit(currentGame);						// print user ocean
			mapHard(hardMap);								// call hard map into main

			while(gameRun == 1)								// set game state
			{	
			inGameTitle();									// print game title
			gameModeDisplayHard();							// print game mode
			topCoords();									// print top coord
			
			for (int row = 0; row < 10; row++){				// loop to print map
				if(row < 9){
					cout << row + 1 << "  ";
				}
				else{
					cout << row + 1 << " ";	
				}
				for (int column = 0; column < 10; column++){
				cout << currentGame[row][column] << " ";			// print current map
				}
				cout << endl;
			}

			bottomCoord();											// print bottom coord

			cout << "Enter your X / Y coordinates: " << endl;		// user input
			cout << "X: ";
			choice2 = getCoordInt() - 1;							// input check
			cout << "Y: ";
			choice1 = getCoordInt() - 1;							// input check
			cout << endl;

			if (hardMap[choice1][choice2] == 'E')					// evaluate if the hit was an enemy ship
			{
				cout << "\a";										// play sound

				currentGame[choice1][choice2] = 'E';				// change map to print enemy hit

				cout << "* You hit a enemy ship! *" << endl;			// printout successful hit
				cout << endl;

				cout << "Continue Playing? (Y/N)" << endl;				// prompt user to continue or quit
				cont = getContinue();

				if(cont == 'N' || cont == 'n'){
					gameRun = 0;
				}
				else{
					gameRun = 1;	
				}


				if(currentGame[1][1] == 'E' && currentGame[2][1] == 'E' && currentGame[3][1] == 'E'){	// evaluate if enemy ship 1 is sunk

					cout << "\a";										// play sound
					cout << "\a";										// play sound
					cout << "\a";										// play sound

					cout << "* You sunk an enemy ship! *" << endl;		// print out successful sinking of an enemy ship
					cout << endl;
					ship1Sunk = 1;										// set value of sunk enemy ship 1
				}

				if(currentGame[6][6] == 'E' && currentGame[7][6] == 'E' && currentGame[8][6] == 'E'){	// evaluate if enemy ship 2 is sunk

					cout << "\a";										// play sound
					cout << "\a";										// play sound
					cout << "\a";										// play sound

					cout << "* You sunk an enemy ship! *" << endl;		// print out successful sinking of an enemy ship
					cout << endl;
					ship2Sunk = 1;										// set value of sunk enemy ship 2
				}		
			}
			else if (hardMap[choice1][choice2] == 'F')					// evaluate if the hit was a friendly ship
			{
				cout << "\a";											// play sound

				currentGame[choice1][choice2] = 'F';					// change map to print friendly hit

				cout << "** You hit a friendly ship! **" << endl;		// printout	successful friendly hit
				cout << endl;

				cout << "Continue Playing? (Y/N)" << endl;				// prompt user to continue or quit
				cont = getContinue();

				if(cont == 'N' || cont == 'n'){
					gameRun = 0;
				}
				else{
					gameRun = 1;	
				}

				if((currentGame[6][7] == 'F' && currentGame[7][7] == 'F' && currentGame[8][7] == 'F') || (currentGame[0][0] == 'F' && currentGame[0][1] == 'F' && currentGame[0][2] == 'F')){

					cout << "\a";										// play sound
					cout << "\a";										// play sound
					cout << "\a";										// play sound

					cout << "** You sunk a friendly ship! **" << endl;	// printout friendly ship sunk
					lose = 1;											// change game state for loss
				}
			}
			else{
				currentGame[choice1][choice2] = 'X';					// set map state for a miss
				cout << "~ Splash... You missed! ~" << endl;			// printout miss
				cout << endl;

				cout << "Continue Playing? (Y/N)" << endl;				// prompt user to continue or quit
				cont = getContinue();

				if(cont == 'N' || cont == 'n'){
					gameRun = 0;
				}
				else{
					gameRun = 1;	
				}
			}


			if(ship1Sunk == 1 && ship2Sunk == 1){						// printout if both enemy ships are sunk - win

					for (int row = 0; row < 10; row++){			// loop to print map
						if(row < 9){
							cout << row + 1 << "  ";
						}
						else{
							cout << row + 1 << " ";	
						}
						for (int column = 0; column < 10; column++){
							cout << currentGame[row][column] << " ";				// print current map
						}
						cout << endl;
					}
					cout << endl;

				cout << "Congratulations! You sunk all the enemy ships!" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "                  You Win!   " << endl;
				cout << endl;
				gameRun = 0;											// end game
				}
			else if(lose == 1){											// printout if a friendly ship is sunk - lose
					for (int row = 0; row < 10; row++){			// loop to print map
						if(row < 9){
							cout << row + 1 << "  ";
						}
						else{
							cout << row + 1 << " ";	
						}
						for (int column = 0; column < 10; column++){
							cout << currentGame[row][column] << " ";				// print current map
						}
						cout << endl;
					}
					cout << endl;

				cout << "Uh oh! You sunk one of your own ships. :(" << endl;
				cout << "You Lose" << endl;
				cout << endl;
				gameRun = 0;											// end game
				}
			}

			break;

		case 3:								// instructions menu option

			instrDisplay();						// instructions display

			break;	

		case 4:								// exit program

		 	cout << "Thank You for playing Ship Battle." << endl;
			endProgram = 1;					// end game
			cout << endl;

			break;
		}

	}
	return 0;
}
