/*
Author: Your name here.
Class: CS 120 Programming and Algorithms in C/C++.
File Name: LastName_FirstName_Lab#_Program#.cpp or format indicated by instructions.
Date: Date you created this program.
Description: Describe with a short paragraph the purpose of your program or what it does in general terms.
*/

using namespace std;		       //Using standard library.

#include <fstream>               // Include library for streaming files
#include <iostream>		        //Include library for console Input/Output.
#include <random>              // Include library for pseudo-random number generation.
#include <string>             // Include library for string functions.
#include <vector>            // Include library for vector functions.
#include "Wallet.h"         // Include file to access the players available money.
#include "Roulette.h"      // Include file to access the Roulette game
#include "BlackjackFunction.h"    // Include file to access the BlackJack game

// Function to check if the file already exists or not
bool userExists(const string& fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		return false;
	}
	return file.good();
}

// Function that prints out the service menu
int mainMenu() {
	int menuChoice;

	cout << "\n\n\n					What would you like to do?\n\n";        // Prompting user for a choice

	cout << "					1. BlackJack\n";							    // Option to play Roulette 
	cout << "					2. Roulette\n";					   // Option to show remaining balance
	cout << "					3. Bank\n";			  // Option to output the payout table for each type of bet
	cout << "					4. Leave\n\n					";						 // Option to cash out and leave the game.

	menuChoice = inputChecker(0, 0);

	return menuChoice;

}

void welcomeMenuASCII() {
	
	// Outputs the ASCII Art for the greeting: Welcome To
	cout << "__        __   _                            _       " << endl;
	cout << "\\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___  " << endl;
	cout << " \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\" << endl;
	cout << "  \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |" << endl;
	cout << "   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/ " << "\n\n\n";

	cout << "		 ______  __ __    ___         __   ____  _____ ____  ____    ___      " << endl;
	cout << "		|      ||  |  |  /  _]       /  ] /    |/ ___/|    ||    \\  /   \\     " << endl;
	cout << "		|      ||  |  | /  [_       /  / |  o  (   \\_  |  | |  _  ||     |    " << endl;
	cout << "		|_|  |_||  _  ||    _]     /  /  |     |\\__  | |  | |  |  ||  O  |    " << endl;
	cout << "		  |  |  |  |  ||   [_     /   \\_ |  _  |/  \\ | |  | |  |  ||     |    " << endl;
	cout << "		  |  |  |  |  ||     |    \\     ||  |  |\\    | |  | |  |  ||     |    " << endl;
	cout << "		  |__|  |__|__||_____|     \\____||__|__| \\___||____||__|__| \\___/     " << endl;

}

void welcomeBack() {

	cout << " __        __   _                            ____             _    " << endl;
	cout << " \\ \\      / /__| | ___ ___  _ __ ___   ___  | __ )  __ _  ___| | __" << endl;
	cout << "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ |  _ \\ / _` |/ __| |/ /" << endl;
	cout << "   \\ V  V /  __/ | (_| (_) | | | | | |  __/ | |_) | (_| | (__|   < " << endl;
	cout << "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___| |____/ \\__,_|\\___|_|\\_\\" << endl;

}

string userLogIn(Wallet& chips) {

	fstream userFile;					 // Initializes the userFile
	string userName;				    // Initializes variable to hold userName

	cout << "\n\n\n					Enter your Initials: ";									// Put after Welcome to the Casino. Ask for their Initials.
	cin >> userName;										           // Grab the inputted initials

	// Checks if it is a returning patron, if so then output message welcoming back the patron and then set the balance to their balance in their file.
	if (userExists(userName + "_login.txt")) {

		cout << "\n\n			  Welcome back to the Casino " << userName << ". Please enjoy your time in the Casino.\n";

		userFile.open(userName + "_login.txt", ios::in);

		if (userFile.is_open()) {

			string line;

			while (getline(userFile, line)) { chips.setBalance(stoi(line)); }

			userFile.close();
		}
	}

	// Else Welcome the first time patron and set their balance to the complimentary 100 chips.
	else {

		userFile.open(userName + "_login.txt", ios::out);

		if (userFile.is_open()) {

			cout << "\n\n			  I see that this is your first time here. Here are 100 free chips on the house for you.\n			  Please enjoy your time in the Casino.\n";
			chips.setBalance(100);
			userFile << chips.getBalance();
			userFile.close();
		}

	}
	return userName;
}

void userLogOut(Wallet& chips, string userName) {

	fstream userFile;

	userFile.open(userName + "_login.txt", ios::out);

	if (userFile.is_open()) {
		userFile << chips.getBalance();
		userFile.close();
	}

}

int main() {
	Wallet chips;					   // Initializes the Wallet object chips
	string userName;				  // Initializes a string to hold the users name.
	int menuChoice;					 // Initializes variable to hold the user menu choices.
	
	welcomeMenuASCII();										 // Calls the welcomeMenu() function to display the ASCII art welcome

	userName = userLogIn(chips);                       // Runs the userLogin function to check if the user is first time player or returning player

	// Main game loop
	while (true) {

		menuChoice = mainMenu();						 // Assigns the menuChoice with what the mainMenu function returns.
		
		// Conditional to check if the user chose to play BlackJack
		if (menuChoice == 1) {				

			system("cls");
			startGameBlackJack(chips, chips.getBalance());					// Start BlackJack
			//cout << "FIX_ME: Start BlackJack";

		}
		
		// Conditional to check if the user chose to play BlackJack
		else if (menuChoice == 2) {

			system("cls");
			playRoulette(chips);					// Start Roulette
			welcomeBack();
		}
		
		// Conditional to check if the user chose to look at their balance
		else if (menuChoice == 3) {

			cout << "					Current Balance: " << chips.getBalance() << " chips.\n\n";		
			
		}
		
		// Conditional to check if the user chose to leave the Casino
		else if (menuChoice == 4) {

			cout << "					Have a nice day " << userName << ". Please come again soon.\n\n";
			userLogOut(chips, userName);
			break;
		
		}
	}

	return 0;		   //Terminated without errors.
}