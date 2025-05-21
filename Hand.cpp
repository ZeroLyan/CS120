/*
Author: Seth Walowski
Class: CS 120 Programming and Algorithms in C/C++.
File Name: Hand.cpp
Description: This resource file is used to define all functions from the header file Hand. The hand class is the biggest class object in the casino
*/

using namespace std;


#include <iostream>		// IO stream for cin cout operations
#include <vector>		// vector class to create and manipulate vectors (used in random card function, and hands)
#include <cmath>		// cmath for modulo
#include <ctime>		// time libary for true randomness generation
#include "Hand.h"		// including hand header file which includes declarations

int randCard() {							// this function returns a random card

	/*
	The random card function generates a random number from 1 to 13.
	First, a vector is formed with each possible card value, then a random mumber is assigned using the seed and time function.
	Finally, a modulo command is ran with the random number to generate a random number between 1 and 13 to index the card deck vector
	*/

	const int deckOfCards[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };	// vector of 13 cards
	//not allowed to index using loops so this declares a constant integer of 13 cards
	srand(time(0) + rand());													//random number generator
	int randomCard = deckOfCards[rand() % 13];									// indexing card deck with random number

	return randomCard;															//returns random number
}

void Hand::setHandName(string handName) {	// this function is used by the main function to set a hand name for print purposes
	name = handName;						// assinging input with private variable
}

void Hand::initiateHand() {					// this function initates a hand. MUST BE RAN FOR THE HAND CLASS OBJECT TO FUNCTION PROPERLY

	/*
	The initiate hand function not only starts the hand, but runs through a boolean case as well. It starts by generating two random cards
	and adding it to the vector hand. Then, the two values are compared to test for a blackjack.
	*/

	cardA = randCard();						// Assinging first  card to a random card
	cardB = randCard();						// Assigning second card to a random card

	hand = { cardA, cardB };				// initates the hand vector

	
	if (((cardB == 1) && (cardA >= 10)) || ((cardA == 1) && (cardB >= 10))) {
		// tests for a blackjack
		blackjackCase = true;				// if true, flips the boolean

	}
}

int  Hand::totalValue() {					// this function adds the cards in hand

	/*
	This function uses a for loop to proceeduraly add the elements of a vector and correct values. It starts by initating a value for card value
	and setting the absolute hand value vector to the original hand vector. Then, the function uses a for loop that repeats as many times as there
	are cards in hand. This look checks for values greater than 10, and corrects them to the value of 10. Then another for loop is used to add each
	value to the total card value.
	*/

	cardVal = 0;							// declares a value for card val to allow manipulation
	absHand = hand;							// assigns absolute value hand to hand

	for (int i = 0; i < hand.size(); i++) {	// for loop to check/correct cards, runs as long as hand size
		     if (hand[i] == 11) {			// if this card is a jack
			absHand[i] = 10;				// sets that card to a value of 10
		}
		else if (hand[i] == 12) {			// if this card is a queen
			absHand[i] = 10;				// sets that card to a value of 10
		}
		else if (hand[i] == 13) {			// if this card is a king
			absHand[i] = 10;				// sets that card to a value of 10
		}
	}

	for (int i = 0; i < hand.size(); i++) {	// for loop to proceedurally add card values together, runs as long as hand size
		cardVal += absHand[i];				// equals plus operator to add abs hand at that value of i to the already declared card value

	}

	return cardVal;							// returns the card value if function is called

}

bool Hand::userBust() {						// boolean function to determine bust case

	if (totalValue() > 21) {				// runs total value command, checks if its over 21
		return  true;						// if so, return true
	}
	else {
		return false;						// if not, return false
	}
}

bool Hand::getBlackjackCase() {				// boolean function to return blackjack case
	return blackjackCase;					// since the blackjack boolean is already checked during the hand initiate, simply returns that private variable
}

void Hand::hit() {							// function performs a hit if requested by main function
	int card = randCard();					// declares a new temporary card variable to be equal to a new random card

	hand.push_back(card );					// appends the hand vector with the new card

	bustCase = userBust();					// automatically runs bust case for print function

}

void Hand::dealerPlay() {					// function to determine what the dealer will do if this hand is for a dealer

	if (cardVal < 17) {						// checks if the total value of cards is under 17
		hit();								// hits if 16 or under
	}
	else {									// case for if the dealer is over 16
		dealerCase = true;					// flips the boolean case for the dealer to stop playing
	}
}

void Hand::printHand() {					// prints the hand

	/*
	largest and most complicated function, used to neatly print out all required hand details to the console
	also checks for boolean cases for display purposes
	*/



	cout << name << "'s hand:\n";			// prints the name of the hand

	for (int i = 0; i < hand.size(); i++) {	// uses a for loop to replace 1, 11, 12, and 13 with face cards, then prints the numbers regularly

		if (hand[i] == 11) {				// checks for a jack
			cout << "J ";					// prints a J instead of 11
		}
		else if (hand[i] == 12) {			// checks for a queen
			cout << "Q ";					// prints a Q instead of 12
		}
		else if (hand[i] == 13) {			// checks for a king
			cout << "K ";					// prints a K instead of 13
		}
		else if (hand[i] == i)  {			// checks for an ace
			cout << "A ";					// prints A instead of 1
		}
		else {								// used for the number cards, non face cards
			cout << hand[i] << " ";			// prints that number followed by a space
		}
	}

	cout << "\nTotal: " << totalValue() << endl;	// under the card value, this prints the total value of the hand

	if (blackjackCase == true) {					// checks for the blackjack case
		cout << "blackjack! " << name << " wins\n";	// prints win case to console
	}
	
	if (bustCase == true)      {					// checks if the user busts, bust case automatically ran by hit function
		cout << "bust!\n";							// if true, outputs to console
	}

	if (dealerCase == true)    {					// checks if the dealer didnt hit
		cout << "dealer stands";					// outputs that the dealer stands to the console
	}
	

}

void Hand::printHandDealer() {

	cout << name << "'s hand:\n";			// prints the name of the hand

	if (blackjackCase == true) {
		printHand();
	}
	else {
		switch (cardA) {
		case 11:
			cout  << "J ";
			break;
		case 12:
			cout  << "Q ";
			break;
		case 13:
			cout  << "K ";
			break;
		case  1:
			cout  << "A ";
			break;
		default:
			cout << cardA;
			break;
		}
		cout << "[]" << endl;
	}

}