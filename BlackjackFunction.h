/*
Author: Seth Walowski
Class: CS 120 Programming and Algorithms in C/C++.
File Name: BlackjackFunction.h
Description: Declare functions for the blackjack game
*/
#ifndef BLACKJACKFUNCTION_H  // defining a header file
#define BLACKJACKFUNCTION_H 

#include "Wallet.h"

int  blackjackGame();        // declaring a function blackjackGame with no inputs and returns an integer
int  startGameBlackJack(Wallet& chips, int balance);		 // declaring a fuction menu to run through the menu and reassign balances to wallet class
int  playGame(int balance);  // declaring a void function with no inputs to place a bet into the wallet class
int  validInput(int menu);   // declaring a function validInput that tests the input for both ingame menus for valid inputs 
void welcomeMenu();          // declaring a void funtion with no output that displays the welcome menu for the game

#endif
