/*************************************************
// Name:: DiceTower
// Description: A simple C++ program that rolls 
// any specified amount of dice with any specified
// amount of sides
// Created by: Aditya Pathak
// Last updated: 2/4/2025
**************************************************/

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <windows.h>
using namespace std;

void SetColor(int textColor, int bgColor);

int main()
{	
	string rollStr= "";

	cout << "###########################################################\n"
		 << "# Welcome to the Dice Tower!                              #\n"
		 << "# Please format your rolls as \"[DICE AMMT]d[DICE SIDES]\"  #\n"
		 << "# Ex: 1d100 would roll 1 dice with 100 sides              #\n" 
		 << "# Enter \"quit\" or \"exit\" to exit the program              #\n"
		 << "###########################################################\n" << endl;

	while (rollStr != "quit" || rollStr != "Quit" || rollStr != "QUIT" || rollStr != "exit" || rollStr != "Exit" || rollStr != "EXIT")
	{
		cout << "What would you like to roll?" << endl;
		cin >> rollStr;

		try {

			if (rollStr == "quit" || rollStr == "Quit" || rollStr == "QUIT" || rollStr == "exit" || rollStr == "Exit" || rollStr == "EXIT")
			{
				SetColor(3, 0);
				cout << "\nHave a good day! : ^)" << endl;
				SetColor(7, 0);
				Sleep(1500);
				return 1;
			}

			int middleIndex = -1;
			int howManyDice = -1;
			int howManySides = -1;
			string diceAmmtStr = "";
			string diceValStr = "";
			mt19937 seed(time(NULL));

			for (int i = 0; i < rollStr.length(); i++)
			{
				//Splits the string in two
				if (rollStr[i] == 'd')
				{
					middleIndex = i;
				}
			}

			for (int i = 0; i < middleIndex; i++)
			{
				//Adds to a new string to use for the ammount of dice
				diceAmmtStr.push_back(rollStr[i]);
			}
			howManyDice = std::atoi(diceAmmtStr.c_str());

			for (int i = middleIndex + 1; i < rollStr.length(); i++)
			{
				//Adds to a new string to use for the dice sides
				diceValStr.push_back(rollStr[i]);
			}
			howManySides = std::atoi(diceValStr.c_str());

			if (howManyDice > INT16_MAX)
			{
				//SetColor(4, 0);
				string e("ERROR: Dice amount exceeds limit. Max dice amount is: 32,767.");
				throw e;
				//cout << "ERROR: Dice ammount exceeds limit. Max dice ammount is: " << INT16_MAX << "\n ***exiting ***" << endl;
				//SetColor(7, 0);
			}

			int rollVal = 0;

			int individualRolls[INT16_MAX];

			if (howManyDice == 0 || howManySides == 0)
			{
				//SetColor(4, 0);
				string e("ERROR: Invalid input. Please provide a valid dice roll command.");
				throw e;
				//SetColor(7, 0);
			}

			//Uses mt19937 for better randomization than rand()
			for (int i = 0; i < howManyDice; i++)
			{
				seed();
				uniform_int_distribution<> range(1, howManySides);
				//Keeps track of each individual roll
				individualRolls[i] = range(seed);
				rollVal += individualRolls[i];
			}
			cout << "\n---------------" << endl;
			cout << "Your roll is:" << endl;

			//Outputs each individual roll if more than one dice is specified
			if (howManyDice > 1)
			{
				for (int i = 0; i < howManyDice; i++)
				{
					cout << individualRolls[i];
					if (i < howManyDice - 1)
					{
						cout << "+";
					}
				}
				cout << endl;
			}
			//Sets a 100 roll to a critical success
			//Uncomment for proper functionality in Call of Cthulu or similar systems
			/*if (rollVal == 100 && howManySides == 100)
			{
				rollVal = 000;
			}*/
			cout << "Total: " << rollVal << endl;
			cout << "---------------\n" << endl;

		}
		catch (string e)
		{
			SetColor(4,0);
			cout << "\n" << e << "\n" << endl;
			SetColor(7, 0);
		}
	}

	return 0;
}
/*************************************************
// Name:: SetColor
// Description: Sets the console
// to display text with a specified
// text and background color
// Parameters: int textColor, int bgColor
// Returns: nothing
**************************************************/
void SetColor(int textColor, int bgColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,
		(bgColor << 4) | textColor);
}