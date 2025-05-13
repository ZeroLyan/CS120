/*
Author: Your name here.
Class: CS 120 Programming and Algorithms in C/C++.
File Name: Use the format indicated for headers.
Date: Date you created this file.
Description: This class will be used to store and dynamically update the players balance
*/

#ifndef Wallet_H		
#define Wallet_H         

using namespace std;		//Using the standard library.
	
class Wallet {	            // Wallet class to contain the players balance
	
   public:			            
	   Wallet();											// Default Constructor
	   void setBalance(int userMoney);					   // Function to set the users balance
	   int getBalance() const;							  // Function to get the users balance
	   void setWinnings(int justWon);					 // Function to set the users winnings
	   int getWinnings() const;							// Function to get the users winnings
	   int areTheyBroke(int currentBalance);           // Function to check if the users balance hits 0 or lower
													   												  
   private:											 
	   int balance;									// Private variable to hold the users balance
	   int winnings;							   // Private variable to hold the users winnings
};

#endif
