/*
Author: Your name here.
Class: CS 120 Programming and Algorithms in C/C++.
File Name: Use the format indicated for headers.
Date: Date you created this file.
Description: This class will be used to store and dynamically update the players balance
*/

#ifndef Roulette_H		
#define Roulette_H         

using namespace std;		//Using the standard library.
#include <iostream>		   //Include library for console Input/Output.
#include <random>         // Include library for pseudo-random number generation.
#include <string>        // Include library for string functions.
#include <vector>       // Include library for vector functions.
#include "Wallet.h"    // Include file to access the players available money.

int rollTheWheel();
string getColor(int result);
double calcWinnings(int betType, int betAmnt);
void printResults(int rolledNum, string numColor);
int didTheyWin(int betType, vector<int> userPick, int betAmnt, int result, int even, string colorBet, string colorResult);
int inputChecker(int menuNum, int balance);
int serviceMenu();
int betMenu();
void getBetNums(vector<int>& userBet);
int getChipBet(int balance);
int playRoulette(Wallet& chips);

#endif
