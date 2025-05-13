/*
Author: Your name here.
Class: CS 120 Programming and Algorithms in C/C++.
File Name: Format indicated on the instructions.
Date: Date you created this program.
Description: Describe with a short paragraph what's the purpose of this resource file.
*/

using namespace std;			//Using the standard library.

//Enter includes here.
#include <iostream>		        // Include library for console Input/Output.

#include "Wallet.h"		      // Include the header file for the Wallet class

// Default Constructor for the Wallet class
Wallet::Wallet() {

	balance = 0;
	winnings = 0;

}

// Deteremines if the player has a balance of 0 or lower
int Wallet::areTheyBroke(int currentBalance) {

	// Conditional that checks if the users balance drops to 0 or lower
	if (currentBalance <= 0) {

		cout << "\n\n\n					GAME OVER!! You ran out of chips. Have a nice day.\n\n\n";    // Outputs the game over screen.
		return 0;
	}

}

// Function to set the users balance
void Wallet::setBalance(int userMoney) {

	balance += userMoney;

}

// Function to get the users balance
int Wallet::getBalance() const{

	return balance;

}

// Function to set the users winnings
void Wallet::setWinnings(int justWon) {

	winnings += justWon;

}

// Function to get the users winnings
int Wallet::getWinnings() const{

	return winnings;

}
