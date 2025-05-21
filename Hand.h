/*
Author: Seth Walowski
Class: CS 120 Programming and Algorithms in C/C++.
File Name: Hand.h
Description: Describe with a short paragraph what's the purpose of this resource file.
*/
#ifndef HAND_H
#define HAND_H

using namespace std;

#include <vector>
#include <string>

class Hand {

public:
	void   dealerPlay();                 // function only used for dealer decks, hits if under 17, else stands
	void   initiateHand();				 // function to initate the hand, assigns private values
	void   hit();						 // function to hit, adds new card to private vector
	void   printHand();					 // function to display the hand and name with total amount + special cases (biggest function)
	void   printHandDealer();			 // function to display the hand and name of the dealer with the 2nd card covered as blackjack is played
	void   setHandName(string handName); // function to assign a name to hand

	int    totalValue();				 // function calculates and returns total value of cards, accounting for face cards

	bool   getBlackjackCase();			 // function returns true or false for if this hand has a blackjack
	bool   userBust();					 // fucntion returns true or false for if this hand exceeded 21


private:

	string      name;					 // String to store the name of the hand

	vector<int> hand;					 // vector to store the cards included in the hand
	vector<int> absHand;				 // vector with the same purpose as hand, except stores actual values of cards (11, 12, 13, = 10)

	int         cardVal;				 // integer to store total card value
	int         cardA;					 // integer used with initiate hand to state the first card
	int         cardB;					 // integer used with initiate hand to state the second card

	bool        blackjackCase = false;	 // Boolean declare to determine if a hand has a black jack or not
	bool        bustCase      = false;	 // Boolean declare to determine if a hand passed 21 to busst
	bool        dealerCase    = false;	 // Boolean declare to determine if a dealer will hit or stand, only use with dealer hands

};




#endif
