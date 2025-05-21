/*
Author: Seth Walowski
Class : CS 120 Programming and Algorithms in C / C++.
File Name : BlackjackFunction.cpp
Description : Defines the functions for the blackjack game
*/

#include <iostream>						// IO stream commands for cin and cout
#include "BlackjackFunction.h"			// Including the header file for blackjack
#include "Hand.h"						// Including the Hand header for hand class use
#include "Wallet.h"

using namespace std;					// I dont wanna type out std:: all the time

int blackjackGame() {					// big function, this is the game

	Hand hand1;							// declaring two hands, hand1
	Hand hand2;							// and hand 2

	int userNum;						// also delcares a variable for user input
	int winCase = 2;					// declared variable to return to the game function for calculating winnings

	hand1.setHandName("Dealer");		// sets the name of hand 1 to dealer
	hand1.initiateHand();				// initiates the hand for the class to function

	hand2.setHandName("User");			// sets the name of hand 2 to the user
	hand2.initiateHand();				// initiates the hand for the class to function

	system("cls");						// after doing the initializing, we clear console to show a blank screen to print the game

	hand1.printHandDealer();			// prints the dealer initiated hand with 2nd card covered

	cout << endl << endl;				// puts space between the two hands

	hand2.printHand();					// prints the user initiated hand



	if ((hand1.getBlackjackCase() == false) && (hand2.getBlackjackCase() == false)) {

		/*
		This is where the fun happens, the game, first the if statement checks for a blackjack. no blackjack means we can continue to a do while function
		the do function shows the options for the user, this needs to be ran at least once, hence the do while command. Then it takes in a user input,
		running it through the input checker. Each statement will be explained as needed.
		*/

		do {
			cout << "\nYour turn\nPress 1 to hit\nPress 2 to stand\n";
			userNum = validInput(2);		// runs valid input function to test the users input for an invalid input

			if (userNum == 1) {				// user requests to hit
				system("cls");				// clears console for next hand print
				hand2.hit();				// runs the hit command on the hand class

				hand1.printHandDealer();			// prints dealer's hand with 2nd card covered


				cout << endl << endl;		// space between hands

				hand2.printHand();			// prints the users hand with the hit statement
			}
			else if (userNum == 2) {		// user requests to stand

				// when the user requests to stand, i run these few commands to loop the hand as the dealer finishes the play

				system("cls");

				hand1.printHand();			// prints the dealer hand with the 2nd card shown since the player stands

				cout << endl << endl;		// space between hands

				hand2.printHand();			// prints user's finished hand

				system("pause");
				
				
				while (hand1.totalValue() < 17) {
					hand1.dealerPlay();
					system("cls");
					hand1.printHand();
					cout << endl << endl;
					hand2.printHand();
					system("pause");
				}

				// because the user stands, its time for win cases

				if ((hand2.userBust() == false) && (hand1.userBust() == false)) {

					// this checks if neither parties busted, bust results in automatic wins without value comparison

					if (hand2.totalValue() > hand1.totalValue()) {		// if user hand is greater than dealers, the player wins
						cout << "Stand, Player wins!\n";
						winCase = 1;
					}
					else if (hand2.totalValue() < hand1.totalValue()) {	// if dealers hand is greater than users, the dealer wins
						cout << "Stand, Dealer wins\n";
						winCase = 0;
					}
					else if (hand1.totalValue() == hand2.totalValue()) {
						cout << "Stand, Push! no winner\n";
						winCase = 2;
					}
				}	// if the dealer busts, the player wins by default
				else if ((hand1.userBust() == true) && (hand2.userBust() == false)) {
					cout << "Stand, Dealer busts, player wins!\n";
					winCase = 1;
				}	// if the user busts, the dealer wins by default
				else if ((hand1.userBust() == false) && (hand2.userBust() == true)) {
					cout << "Stand, Player busts, dealer wins\n";
					winCase = 0;
				}
				

				cout << endl;
				system("pause");		// pause and clear console, returning to the main menu after a win case
				system("cls");

				return winCase;

			}
		} while (userNum == 1);			// this while case ensures this loop is repeated if the player chooses to hit, only exiting the loop when standing
	}
	else if (hand2.getBlackjackCase() == true) {

		// this goes back to the black jack case, the user hands is checked first as they get priority

		cout << "\nPlayer wins\n";
		winCase = 1;

		system("pause");
		system("cls");

		return winCase;		// return to main menu, player won
	}
	else if (hand1.getBlackjackCase() == true) {

		// if the player didnt get a blackjack, this checks if the dealer got a blackjack

		cout << "\nDealer wins\n";
		winCase = 0;

		system("pause");
		system("cls");

		return winCase;		// return to main menu, dealer won

	}
}

int startGameBlackJack(Wallet& chips, int balance) {							// menu function, my artwork and life dedication (joke)
	/*
	This main function runs the game, ive spent hours cleaning it up and setting up separate functions outside of the main to clean up
	this code, making it readable and beautiful. This main function is simply a grouping of if statement that calls other functions.
	*/
	int winnings = chips.getWinnings();					// declares a winnings variable for the game, defaults to zero.

	welcomeMenu();						// displays the welcome menu function defined in another file
	int userNum = validInput(1);	// sets the user number to go through the valid input for menu one
	bool finish = false;			// sets the finish case to false so the following loop works
	try {							// try case to catch a rare failure case
		if (userNum == 1) {			// if the inputted number for the menu is 1, turns the blackjack game, returns finished and re runs the main function

			winnings = playGame(chips.getBalance());

			chips.setBalance(winnings);

			cout << "\n\n\n WINNINGS:  " << winnings << "\n\n\n";

			system("pause");
			system("cls");

			startGameBlackJack(chips, chips.getBalance());

		}
		else if (userNum == 2) {	// if the inputted number for the main menu is 2, runs the balance class and displays total winnings
			cout << "\n Balance: " << balance << endl << endl;
			system("pause");		// pauses console
			system("cls");			// clears the console
			startGameBlackJack(chips, chips.getBalance());					// re runs the main menu function

		}

		else if (userNum == 3) {	// 3 is the leave game optiom
			cout << "Thank you for playing!\n";
			return balance;				// returns 0 to show program exited with no errors

		}
		else {						// in a rare case the catch was not caught, this catches the failure
			throw runtime_error("Menu function did not return a valid integer, Restart Program");
		}
	}
	catch (runtime_error& e) {		// catches the runtime error
		cout << "\nError!: " << e.what() << endl;
	}								// displays the error to the console
}

int playGame(int balance) {
	int betAmount;
	int winnings = 0;
	int winCase  = 2;

	system("cls");

	cout << "balance: " << balance << "\nPlease place your bet:\n";
	while (true) {
		betAmount = validInput(3);
		if (balance >= betAmount) {
			break;
		}
		else {
			cout << "\nInsufficient Balance, please enter another bet amount:\n";
		}
	}

	cout << "\nyou entered: " << betAmount << endl;

	system("pause");

	winCase = blackjackGame();

	try {
		if (winCase == 0) {
			winnings = -1 * betAmount;
			return winnings;
		}
		else if (winCase == 1) {
			winnings = 2 * betAmount;
			return winnings;
		}
		else if (winCase == 2) {
			return winnings;
		}
		else {
			throw invalid_argument("function blackjackGame did not return an integer 0 through 2");
		}
	}
	catch (const invalid_argument& e) {
		cout << "ERROR: " << e.what() << "\nPlease restart program\n";
	}

	
	
}

int validInput(int menu) {

	/*
	This function serves as an input checker to ensure the user enters a valid input. It uses an input integer as a "menu choice"
	instead of having two functions to check each blackjack menu, we have one function with two options
	the integer returned is a guarenteed valid integer for the requested menu
	*/

	int input;				// declares an integer for user input
	bool catchCase = true;	// declares a catch case boolean and defaults it to true for the following while loop to function

	while (catchCase == true) {
		try {													// starts the try catch scenario

			cin >> input;										// takes the input from user

			if (cin.fail() == true) {							// cin fails tests if the buffer holds anything that isnt an integer
				throw invalid_argument("Invalid Input. ");		// throws invalid input to the catch case
			}
			else if (menu == 1) {								// if an integer is held (no cin fail) this checks which menu the function calls for
				if (!((input < 4) && (input > 0))) {			// menu one is the main menu, must be a value between 1 and 4.
					throw invalid_argument("Invalid Input. ");	// if not in these parameters, throws an invalid argument to the catch case
				}
			}
			else if (menu == 2) {								// menu two is the black jack game
				if ((input > 2) || (input < 0)) {				// must be rather a 1 or a 2, this checks if thats not the input
					throw invalid_argument("Invalid Input. ");	// if the user number does not match the parameters, throws an invalid argument to catch case
				}
			}
			else if (menu == 3) {
				if (input < 1) {
					throw invalid_argument("Invalid Input. ");
				}
			}

			catchCase = false;									// the while function constantly repeats the try catch case, if no error is present, this exists the while loop by switching the boolean

		}
		catch (const invalid_argument& e) {						// catches the invalid argument case at e to generate a error code
			cout << "Error: " << e.what() << "Please enter a valid option\n";
																// outputs the error and asks for another option
			cin.clear();										// then clears the console
			cin.ignore(numeric_limits<streamsize>::max(), '\n');// this comman clears the console in buffer
			system("pause");									// pauses console for user to continue
			catchCase = true;									// makes sure ther catch case boolean is set to true if a catch case is caught.
		}
	}

	return input;												// after a valid input is recieved from user, this command returns that input to the main function
}

void welcomeMenu() {
	cout << "Welcome to:" << endl << endl;

	cout << "__________ .__                    __         ____.                 __     __________ .__   .__   __       " << endl;
	cout << "\\______   \\|  |  _____     ____  |  | __    |    |_____     ____  |  | __ \\______   \\|  |  |__|_/  |_ ________" << endl;
	cout << " |    |  _/|  |  \\__  \\  _/ ___\\ |  |/ /    |    |\\__  \\  _/ ___\\ |  |/ /  |    |  _/|  |  |  |\\   __\\\\___   /" << endl;
	cout << " |    |   \\|  |__ / __ \\_\\  \\___ |    < /\\__|    | / __ \\_\\  \\___ |    <   |    |   \\|  |__|  | |  |   /    / " << endl;
	cout << " |______  /|____/(____  / \\___  >|__|_ \\\\________|(____  / \\___  >|__|_ \\  |______  /|____/|__| |__|  /_____ \\" << endl;
	cout << "        \\/            \\/      \\/      \\/               \\/      \\/      \\/         \\/                        \\/" << endl;

	cout << "Please select an option" << endl;

	cout << "1. Play" << endl << "2. Show Balance" << endl << "3. Quit" << endl;

}

