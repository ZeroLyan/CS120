/*
Author: Jaymz George
Class: CS 120 Programming and Algorithms in C/C++.
File Name: Roulette.cpp
Date: 05/04/2025
Description: This program allows the user to play the game of Roulette.
*/

using namespace std;		  //Using standard library.

// Include libraries used here.
#include <iostream>		   //Include library for console Input/Output.
#include <random>         // Include library for pseudo-random number generation.
#include <string>        // Include library for string functions.
#include <vector>       // Include library for vector functions.
#include "Wallet.h"    // Include file to access the players available money.
#include "Roulette.h" // Include file to access the functions for the game

// Randomly generates a number from -1 - 36 and returns that value. In this case -1 is used to represent the 00 result.
int rollTheWheel() {

	srand(time(0));                              // Seeds the program to acheive the pseudo-random generation

	int rouletteWheel[38];						// Initialize an int array to hold all the possible outcomes
	
	for (int i = 0; i < 37; ++i) {			   // For loop to add the ints 0-36 into the array

		rouletteWheel[i] = i;

	}

	rouletteWheel[37] = -1;					 // Adds -1 to the end which represents the 00 
	 
	int winnerWinner = rand() % 38;			// Picks a random number 0-37. Winner is the element at that index.

	return rouletteWheel[winnerWinner];    // Returns the element at that index

}

// Takes in result from rollTheWheel and outputs the coressponding color
string getColor(int result) {

	if (result == -1 || result == 0) {                   // Conditional to check for either 0 or -1 to set color to green

		return "Green";

	}

	else if ((result >= 1 && result <= 10) || (result >= 19 && result <= 28)) {          // Conditional to check the ranges for odd being red and even being black         

		if (result % 2 != 0) {

			return "Red";

		}

		else {

			return "Black";

		}

	}

	else if ((result >= 11 && result <= 18) || (result >= 29 && result <= 36)) {          // Conditional to check the ranges for odd being black and even being red

		if (result % 2 == 0) {                                                           // Conditional to check for even numbers

			return "Red";

		}

		else {

			return "Black";

		}

	}

}

// Returns the winnings based off the bet made.
double calcWinnings(int betType, int betAmnt) {

	switch (betType) {

		case 1:

			return betAmnt * 35;                         // Single number bet pays 35 to 1. Also called “straight up.”

		case 2:

			return betAmnt * 17;                        // Double number bet pays 17 to 1. Also called a “split.”

		case 3:

			return betAmnt * 11;                       // Three number bet pays 11 to 1. Also called a “street.”

		case 4:

			return betAmnt * 8;                       // Four number bet pays 8 to 1. Also called a “corner bet.”

		case 5:

			return betAmnt * 6;                      // Five number bet pays 6 to 1. Only one specific bet which includes the following numbers : 0 - 00 - 1 - 2 - 3.

		case 6:

			return betAmnt * 5;                     // Six number bets pays 5 to 1. Example : 7, 8, 9, 10, 11, 12. Also called a “line.”

		case 7:

			return betAmnt * 2;                    // Twelve numbers or dozens(first, second, third dozen) pays 2 to 1.

		case 8:

			return betAmnt * 2;                   // Column bet(12 numbers in a row) pays 2 to 1.

		case 9:
			
			return betAmnt;                      // 18 numbers(1 - 18) pays even money.
		
		case 10:
			
			return betAmnt;                     // 18 numbers(19 - 36) pays even money.
		
		case 11:
			
			return betAmnt;                    // Red or black pays even money.
		
		case 12:
			
			return betAmnt;                  // Odd or even bets pay even money 
	}

}

// Prints out the results screen
void printResults(int rolledNum, string numColor) {

	if (rolledNum == -1) {

		cout << "\n\n					Rolled: 00 " << numColor;                                 // Checking for the -1 to output the proper 00 result

	}

	else {

		cout << "\n\n					Rolled: " << rolledNum << " " << numColor;			  // Printing out the result and its appropriate color

	}
}

// Determines if the player won.
int didTheyWin(int betType, vector<int> userPick, int betAmnt, int result, int even = 99, string colorBet = "", string colorResult = "") {
	
	// Conditional to check for bet types that check against a single thing. (1 num, odd or even, red or black.)
	if ((betType == 1 || betType > 10 )) { 
		// Nested conditional to check if the user correctly guessed the number, red, black, odd, or even.
		if ((result == userPick[0]) || ((even == 2) && (result % 2 == 0)) || ((even == 1) && (result % 2 != 0)) || (colorBet == colorResult)) {   
			int winnings = calcWinnings(betType, betAmnt);								// Calculates the users winnings														
			printResults(result, colorResult);										   // Prints the results of the roll					  
			cout << "\n\n\n					You Won: $" << winnings;				  // Prints out how much user won
			return winnings;														 // Returns the amount won
		}
	}

	// Conditional to check if the user chose a bet that has more than a singular element that needs to be checked.
	else if ((betType > 1 && betType < 11)) {

		// For loop to check each element of the userPicks vector
		for (int i = 0; i < userPick.size(); ++i) {

			// Nested conditional to check if the used chose a correct number
			if (result == userPick[i]) {										
				int winnings = calcWinnings(betType, betAmnt);						// Calculates the users winnings	
				printResults(result, colorResult);								   // Prints the results of the roll	
				cout << "\n\n\n					You Won: $" << winnings;		  // Prints out how much user won
				return winnings;												 // Returns the amount won
			}
		}

	}

	// If the user loses this executes.
	int losses = -betAmnt;												   // Calculates the users losses	
	printResults(result, colorResult);									  // Prints the results of the roll	
	cout << "\n\n					You Lost: $" << betAmnt << "";		 // Prints out how much user lost
	return losses;														// Returns the amount lost

}

// Function to check the user inputs for errors
int inputChecker(int menuNum, int balance) {
	
	int menuChoice;

	// Try Catch statements to catch possible errors that the user can input
	try {
		cin >> menuChoice;          // Grabs the user's choice.

		// Conditionals to check for various invalid inputs and if one is found they throw an invalid_arguement exception
		if (cin.fail() == true) { throw invalid_argument("Wrong Input Detected.");}													// Conditional to check for user not entering an int
																																   
		else if (menuNum == 3) if (menuChoice < -1 || menuChoice > 36) { throw invalid_argument("Wrong Input Detected."); }		  // Condtional to check for wrong number chosen for a number to bet on
																																 
 		else if (menuNum == 4) { if (menuChoice > balance) { throw invalid_argument("Wrong Input Detected."); } }				// Conditional to check if the user tried to bet more chips than they had
	}

	// Catch statement to catch any invalid_argument exceptions
	catch (const invalid_argument& e) {

		cerr << "\n\n\n             Error: " << e.what() << " Please input a correct choice. ";      // Outputs error message
		cin.clear();																			    // Clears fail status from cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n');									   // Clears cin buffer
		system("pause");																		  // Pauses to show the error message
		system("cls");																			 // Clears the screen to not fill the console with error messages
		menuChoice = 100;																		// Sets menuChoice to a number out of range for the second conditional to work properly
		if (menuNum == 4) {																	   // Sets menuChoice to a number greater than the users balance to for the third conditional to work properly

			menuChoice = balance + 1;
		}

	}
	
	return menuChoice;			// Returns a correct menu choice if no exception is caught

}

// Function that prints out the service menu
int serviceMenu() {
	int menuChoice;

	cout << "\n\n\n					How may I be of service?\n\n";        // Prompting user for a choice

	cout << "					1. Play\n";							    // Option to play Roulette 
	cout << "					2. Show balance\n";					   // Option to show remaining balance
	cout << "					3. Show payout table\n";			  // Option to output the payout table for each type of bet
	cout << "					4. Cash out\n\n					";						 // Option to cash out and leave the game.

	menuChoice = inputChecker(0, 0);

	return menuChoice;

}

// Function that prints out the bet menu
int betMenu() {
	int menuChoice;

	while (true) {
		cout << "\n\n\n					What kind of bet would you like to make?" << "\n\n";
		cout << "					1. Single Number		7.  Dozen" << endl;
		cout << "					2. Two Numbers			8.  Column" << endl;
		cout << "					3. Three Numbers		9.  Front Half" << endl;
		cout << "					4. Four Numbers			10. Back Half" << endl;
		cout << "					5. Five Numbers			11. Odd or Even" << endl;
		cout << "					6. Six Numbers			12. Red or Black\n\n					";

		menuChoice = inputChecker(0, 0);
		if (menuChoice < 13 && menuChoice > 0) { break; }
	}

	return menuChoice;
}

// Function that takes in a int vector by reference that holds the user's chosen numbers to bet on and fills it to the corresponding length the user chose.
void getBetNums(vector<int>& userBet) {
	int bet;
	
	while (true) {
		cout << "\n\n\n					Choose a number 0-36, to choose 00 please input -1: ";								// Prompt user for a number

		bet = inputChecker(0, 0);
		userBet.push_back(bet);
		if (bet > -2 && bet < 37) { break; }

	}
}

// Function to get the amount of chips the user wants to bet.
int getChipBet(int balance) {
	int betAmnt;

	while (true) {
		cout << "\n\n\n					How much would you like to bet: ";							// Prompt user for a bet and store it
		betAmnt = inputChecker(4, balance);

		if (betAmnt <= balance) { break; }
	}
	return betAmnt;

}

// Outputs the welcome menu for the game.
int playRoulette(Wallet& chips) {

	int menuChoice;			// Holds the what number is picked in the menu
	int userPick;
	int betAmnt;

	// Outputs the ASCII Art for the greeting: Welcome To
	cout << "__        __   _                            _       " << endl;
	cout << "\\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___  " << endl;
	cout << " \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\" << endl;
	cout << "  \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |" << endl;
	cout << "   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/ " << "\n\n\n";

	// Outputs the ASCII Art for the title: When In Rome Roulette
	cout << "__        ___                  ___         ____                        ____             _      _   _       " << endl;
	cout << "\\ \\      / / |__   ___ _ __   |_ _|_ __   |  _ \\ ___  _ __ ___   ___  |  _ \\ ___  _   _| | ___| |_| |_ ___ " << endl;
	cout << " \\ \\ /\\ / /| '_ \\ / _ \\ '_ \\   | || '_ \\  | |_) / _ \\| '_ ` _ \\ / _ \\ | |_) / _ \\| | | | |/ _ \\ __| __/ _ \\" << endl;
	cout << "  \\ V  V / | | | |  __/ | | |  | || | | | |  _ < (_) | | | | | |  __/ |  _ < (_) | |_| | |  __/ |_| ||  __/" << endl;
	cout << "   \\_/\\_/  |_| |_|\\___|_| |_| |___|_| |_| |_| \\_\\___/|_| |_| |_|\\___| |_| \\_\\___/ \\__,_|_|\\___|\\__|\\__\\___|" << endl;
	
	// Main game loop using while (true) method to initiate an infinite loop that breaks under certain conditions
	while (true) {

		int rollResult = rollTheWheel();                                // Uses the rollTheWheel function to "roll the wheel" and get a result
		string resultColor = getColor(rollResult);					   // Uses the result to determine the right color for the number.
		string colorBet;											  // Stores the color that the user bets on
		vector<int> userBet;										 // Vector to store all the numbers the user bets on
		int even;													// Variable to determine whether the user bet on odds or evens.	
		int winnings;
		
		
		if (chips.areTheyBroke(chips.getBalance()) == 0) { break; }          // Conditional to check the players balance and breaks the loop if the areTheyBroke function returns 0.

		menuChoice = serviceMenu();										 // Calls the service menu to continue the game.
		
		// Choice 1: Outputs the betting menu and plays the game.
		if (menuChoice == 1) {

			menuChoice = betMenu();

			// Single Number Bet: Prompts the user to choose a number then pushes it into the initialized vector and checks if the player won.
			if (menuChoice == 1) {

				getBetNums(userBet);																				// Calls the function to allow the user to select their bet

				betAmnt = getChipBet(chips.getBalance());														  // Sets the amount of chips the user bets to what the getChipBet function returns 

				chips.setBalance(-betAmnt);																		// Adjusts players balance by how much they bet

				winnings = didTheyWin(1, userBet, betAmnt, rollResult, 99, colorBet, resultColor);			  // Sets the winnings to what the didTheyWin function returns
				chips.setWinnings(winnings);																 // Adjusts the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }											// If the user won chips then adjust the balance accordingly
			
			}

			// Two Number Bet: Prompts the user to choose two numbers then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 2) {

				for (int i = 0; i < 2; ++i) {																		    // For loop to get multiple bets from the user
																													 
					getBetNums(userBet);																			  // Calls the getBetNums function to push the bets into the vector passed by reference

				}

				betAmnt = getChipBet(chips.getBalance());														  // Sets the amount of chips the user bets to what the getChipBet function returns
																												 
				chips.setBalance(-betAmnt);																		// Adjusts players balance by how much they bet
																											   
				winnings = didTheyWin(2, userBet, betAmnt, rollResult, 99, colorBet, resultColor);			  // Sets the winnings to what the didTheyWin function returns
				chips.setWinnings(winnings);																 // Adjusts the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }											// If the user won chips then adjust the balance accordingly

			}

			// Three Numbers Bet: Prompts the user to choose three numbers then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 3) {

				for (int i = 0; i < 3; ++i) {																		    // For loop to get multiple bets from the user
																													 
					getBetNums(userBet);																			  // Calls the getBetNums function to push the bets into the vector passed by reference

				}

				betAmnt = getChipBet(chips.getBalance());														  // Sets the amount of chips the user bets to what the getChipBet function returns

				chips.setBalance(-betAmnt);																		// Adjusts players balance by how much they bet

				winnings = didTheyWin(3, userBet, betAmnt, rollResult, 99, colorBet, resultColor);			  // Sets the winnings to what the didTheyWin function returns
				chips.setWinnings(winnings);																 // Adjusts the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }											// If the user won chips then adjust the balance accordingly

			}

			// Four Numbers Bet: Prompts the user to choose four numbers then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 4) {

				for (int i = 0; i < 4; ++i) {																	    // For loop to get multiple bets from the user
																												 
					getBetNums(userBet);																		  // Calls the getBetNums function to push the bets into the vector passed by reference

				}

				betAmnt = getChipBet(chips.getBalance());													  // Sets the amount of chips the user bets to what the getChipBet function returns

				chips.setBalance(-betAmnt);																	// Adjusts players balance by how much they bet

				winnings = didTheyWin(4, userBet, betAmnt, rollResult, 99, colorBet, resultColor);		  // Sets the winnings to what the didTheyWin function returns
				chips.setWinnings(winnings);															 // Adjusts the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }										// If the user won chips then adjust the balance accordingly

			}

			// Five Numbers Bet: Prompts the user to choose five numbers then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 5) {

				for (int i = 0; i < 5; ++i) {																		    // For loop to get multiple bets from the user
																													 
					getBetNums(userBet);																			  // Calls the getBetNums function to push the bets into the vector passed by reference

				}

				betAmnt = getChipBet(chips.getBalance());														  // Sets the amount of chips the user bets to what the getChipBet function returns

				chips.setBalance(-betAmnt);																		// Adjusts players balance by how much they bet

				winnings = didTheyWin(5, userBet, betAmnt, rollResult, 99, colorBet, resultColor);			  // Sets the winnings to what the didTheyWin function returns
				chips.setWinnings(winnings);																 // Adjusts the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }											// If the user won chips then adjust the balance accordingly

			}

			// Six Number Bet: Prompts the user to choose six numbers then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 6) {

				for (int i = 0; i < 6; ++i) {																	    // For loop to get multiple bets from the user
																												 
					getBetNums(userBet);																		  // Calls the getBetNums function to push the bets into the vector passed by reference

				}

				betAmnt = getChipBet(chips.getBalance());													  // Sets the amount of chips the user bets to what the getChipBet function returns

				chips.setBalance(-betAmnt);																	// Adjusts players balance by how much they bet

				winnings = didTheyWin(6, userBet, betAmnt, rollResult, 99, colorBet, resultColor);		  // Sets the winnings to what the didTheyWin function returns
				chips.setWinnings(winnings);															 // Adjusts the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }										// If the user won chips then adjust the balance accordingly

			}

			// Dozen Number Bet: Prompts the user to choose a dozen group then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 7) {

				cout << "\n\n\n					Choose a dozen 1, 2, or 3: ";											// Prompts the user to choose one of the available dozens
				userPick = inputChecker(0, 0);																		   // Sets userPick equal to what the inputChecker function returns
				if (userPick == 1) {																				  // Conditional to check for the first dozen
					for (int i = 1; i < 13; ++i) { userBet.push_back(i); }											 // For loop to push the first dozen numbers into the userBet vector
				}
				else if (userPick == 2) {																		   // Conditional to check for the second dozen
					for (int i = 13; i < 25; ++i) { userBet.push_back(i); }										  // For loop to push the second dozen numbers into the userBet vector
				}
				else if (userPick == 3) {																	    // Conditional to check for the third dozen
					for (int i = 25; i < 37; ++i) { userBet.push_back(i); }									   // For loop to push the third dozen numbers into the userBet vector
				}

				betAmnt = getChipBet(chips.getBalance());													// Sets betAmnt with the value returned by the getChipBet function.

				chips.setBalance(-betAmnt);																  // Adjusts users balance by what they bet

				winnings = didTheyWin(7, userBet, betAmnt, rollResult, 99, colorBet, resultColor);		// Sets winnings with the value returned by the didTheyWin function
				chips.setWinnings(winnings);														   // Updates the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }									  // If user won chips then adjusts the users balance with the winnings

			}
			
			// Column Number Bet: Prompts the user to choose a column group then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 8) {

				cout << "					Choose a Column 1, 2 , or 3: ";											  // Prompts the user to choose one of the available columns
				userPick = inputChecker(0, 0);																	     // Sets userPick equal to what the inputChecker function returns
				if (userPick == 1) {																			    // Conditional to check for the first column
					for (int i = 1; i < 37; i += 3) { userBet.push_back(i); }									   // For loop to push the first column of numbers into the userBet vector
				}
				else if (userPick == 2) {																	     // Conditional to check for the second column
					for (int i = 2; i < 37; i += 3) { userBet.push_back(i); }								    // For loop to push the second column of numbers into the userBet vector
				}
				else if (userPick == 3) {																      // Conditional to check for the third column
					for (int i = 3; i < 37; i += 3) { userBet.push_back(i); }							     // For loop to push the third column of numbers into the userBet vector
				}

				betAmnt = getChipBet(chips.getBalance());												  // Sets betAmnt with the value returned by the getChipBet function.

				chips.setBalance(-betAmnt);															    // Adjusts users balance by what they bet

				winnings = didTheyWin(8, userBet, betAmnt, rollResult, 99, colorBet, resultColor);	  // Sets winnings with the value returned by the didTheyWin function
				chips.setWinnings(winnings);														 // Updates the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }									// If user won chips then adjusts the users balance with the winnings

			}

			// Front Half Number Bet: Prompts the user they chose the front half of the numbers then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 9) {

				cout << "					You chose the front half. ";							        	// Prompts the user they chose the front half of numbers
																									        
				for (int i = 1; i < 19; ++i) { userBet.push_back(i); }								          // For loop that pushes the first half of numbers into the userBet vector
																									        
				betAmnt = getChipBet(chips.getBalance());											        // Assigns betAmnt with the value returned by the getChipBet function
																									        
				chips.setBalance(-betAmnt);															      // Adjusts the users balance by their bet

				winnings = didTheyWin(9, userBet, betAmnt, rollResult, 99, colorBet, resultColor);		// Assisngs winnings with the value returned by the didTheyWin function
				chips.setWinnings(winnings);														   // Updates the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }									  // If the user won chips then adjust their balance by winnings

			}

			// Back Half Bet: Prompts the user they chose the front half of the numbers then pushes them into the initialized vector using a for loop and checks if the player won.
			else if (menuChoice == 10) {

				cout << "					You chose the back half. ";									      	  // Prompts the user they chose the back half of numbers
																										      
				for (int i = 19; i < 36; ++i) { userBet.push_back(i); }									        // For loop that pushes the back half of numbers into the userBet vector

				betAmnt = getChipBet(chips.getBalance());												      // Assigns betAmnt with the value returned by the getChipBet function

				chips.setBalance(-betAmnt);																    // Adjusts the users balance by their bet

				winnings = didTheyWin(10, userBet, betAmnt, rollResult, 99, colorBet, resultColor);		  // Assisngs winnings with the value returned by the didTheyWin function
				chips.setWinnings(winnings);															 // Updates the users winnings
				if (winnings > 0) { chips.setBalance(winnings); }										// If the user won chips then adjust their balance by winnings

			}

			// Odd or Even Number Bet: Prompts the user to choose Odd or Even and checks if the player won.
			else if (menuChoice == 11) {

				cout << "					1.Odd or 2.Even? ";																	// Prompts the user to pick either Odd or Even
				userPick = inputChecker(0,0);																				   // Assigns userPick with the value returned by the inputChecker function
				userBet.push_back(99);																						  // Pushes arbitrary number into the userBet vector
																															 
				betAmnt = getChipBet(chips.getBalance());																	// Assigns betAmnt with the value returned by the getChipBet function
						
				chips.setBalance(-betAmnt);																				  // Adjusts users balance by the bet amount

				winnings = didTheyWin(11, userBet, betAmnt, rollResult, userPick, colorBet, resultColor);			    // Assigns winnings with the value returned by the didTheyWin function
				chips.setWinnings(winnings);																		   // Updates user's winnings
				if (winnings > 0) { chips.setBalance(winnings); }													  // If the user won chips then update balance with winnings

			}

			// Red or Black Number Bet: Prompts the user to choose Red or Black and checks if the player won.
			else if (menuChoice == 12) {

				cout << "					1. Red or 2. Black? ";													   // Prompts the user to pick either Red or Black
				userPick = inputChecker(0, 0);																		  // Assigns userPick with the value returned by the inputChecker function
				if (userPick == 1) { colorBet = "Red"; }															 // Checks if the user chose to bet on red
				else { colorBet = "Black"; }																		// If they didnt then set it to black
				userBet.push_back(99);																			   // Pushes arbitrary number into the userBet vector
																												  // Assigns betAmnt with the value returned by the getChipBet function
				betAmnt = getChipBet(chips.getBalance());														 
																											    
				chips.setBalance(-betAmnt);																	   // Adjusts users balance by the bet amount
																											
				winnings = didTheyWin(12, userBet, betAmnt, rollResult, 99, colorBet, resultColor);		     // Assigns winnings with the value returned by the didTheyWin function
				chips.setWinnings(winnings);															    // Updates user's winnings
				if (winnings > 0) { chips.setBalance(winnings); }										   // If the user won chips then update balance with winnings

			}

		}
		
		// Outputs players current balance
		else if (menuChoice == 2) {

			cout << "					Current Balance: " << chips.getBalance();				// Finish to show players current balance from the Wallet class.

		}

		// Outputs the current payout table
		else if (menuChoice == 3) {

			cout << "\n\n					Bet Type		||		Payout\n";
			cout << "					------------------------||--------------------\n";
			cout << "					One Number		||		35:1\n";
			cout << "					Two Numbers		||		17:1\n";
			cout << "					Three Numbers		||		11:1\n";
			cout << "					Four Numbers		||		8:1\n";
			cout << "					Five Numbers		||		6:1\n";
			cout << "					Six Numbers		||		5:1\n";
			cout << "					Dozen			||		2:1\n";
			cout << "					Column			||		2:1\n";
			cout << "					Front Half		||		1:1\n";
			cout << "					Back Half		||		1:1\n";
			cout << "					Red			||		1:1\n";
			cout << "					Black			||		1:1\n\n\n\n";
		}

		// Leaves the game.
		else if (menuChoice == 4) {

			cout << "\n\n\n					Have a great day, you won: " << chips.getWinnings() << "\n\n\n\n";       // Finish to show how much money player earned from Roulette
			system("pause");
			system("cls");
			return chips.getBalance();

		}
		
	}
	
}
