// Caedmon DelVecchio
// CaedmonDelvecchioAdventurer.cpp
// thursday

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>

// ****************** function prototypes **************************
std::string worldConstruction();											// Makes the world text file readable to the program
void introDisplay();														// Displays intro and instructions
void userInputParse(std::string input);										// Interprets user's input and performs according action
int idLookup(std::string idSearch);											// Searches for line with id in world's XML
bool parentLookup(std::string parentSearch, std::string holdingSearch);		// Checks if searched object is a child of current location in the world's XML
bool requireLookup(std::string idSearch);									// Checks if area needs a key to enter
std::string textParse(std::string stringSearch);							// Displays text of heading location from XML

// ****************** variable declarations **************************
std::ifstream infile("blankField.xml");			// XML world data
std::ifstream infileWorld("blankField.txt");	// TXT world structure
std::ifstream infileVerb("verbs.txt");			// TXT list of verbs and synonyms
std::string playerLoc = "";						// Player's location in the world
std::string inventory[3] = {"nil","nil","nil"}; // Items player is holding
std::string world[10][10];						// World data in 2D array

int main()
{
	// ****************** variable declarations **************************
	std::string input = "";		// User's input
	std::string finish = "";	// ID of final zone

	finish = worldConstruction();
	introDisplay();

	while (input != "quit")
	{
		std::getline(std::cin, input);

		if (input != "quit")
		{
			userInputParse(input);
		}

		if (playerLoc == finish)
		{
			std::cout << "Congratulations, you've beaten the game!" << std::endl;

			break;
		}

	}
	
	std::cout << "Thanks for playing!" << std::endl;

	infile.close();
	infileVerb.close();
	infileWorld.close();
	system("pause");
	return 0;
}// End of main

std::string worldConstruction()
{
	// ****************** variable declarations **************************
	std::string worldBuffer = "";	// For input from the world txt
	std::string finish = "";		// ID of final zone

	for (int i = 0; i < 10; i++)
	{

		for (int j = 0; j < 10; j++)
		{
			infileWorld >> worldBuffer;
			world[i][j] = worldBuffer;
		}

	}

	infileWorld >> playerLoc;
	infileWorld >> finish;

	return finish;
}// end of worldConstruction

void introDisplay()
{
	std::cout << "   _       _                 _                       " << std::endl;
	std::cout << "  /_\\   __| |_   _____ _ __ | |_ _   _ _ __ ___ _ __ " << std::endl;
	std::cout << " //_\\\\ / _` \\ \\ / / _ \\ '_ \\| __| | | | '__/ _ \\ '__|" << std::endl;
	std::cout << "/  _  \\ (_| |\\ V /  __/ | | | |_| |_| | | |  __/ |   " << std::endl;
	std::cout << "\\_/ \\_/\\__,_| \\_/ \\___|_| |_|\\__|\\__,_|_|  \\___|_|   " << std::endl;
	std::cout << "\nYou have woken up, unaware you were asleep in the first place. You must discover what lies in the land you have been thrust into." << std::endl;
	std::cout << "\nType a verb such as go or walk and then a direction such as north or east to go that direction." << std::endl;
	std::cout << "Type \"Look\" and then an object name to examine an object." << std::endl;
	std::cout << "Type a verb such as \"grab\" and then an object to put that object in your inventory." << std::endl;

	system("pause");
	system("cls");
}

void userInputParse(std::string input)
{
	// ****************** variable declarations **************************
	std::string verb = "";			// User inputted verb
	std::string noun = "";			// User inputted noun
	std::string verbSearch = "";	// Line of data from verbs TXT
	std::string verbResult = "";	// Universal verb synonym

	infileVerb.clear();
	infileVerb.seekg(0);

	verb = input.substr(0, input.find(" "));
	noun = input.substr(input.find(" ") + 1, input.length());

	while (!infileVerb.eof())
	{
		std::getline(infileVerb, verbSearch);

		if (verbSearch.find(verb) != std::string::npos)
		{
			verbResult = verbSearch.substr(0, verbSearch.find(" "));
			break;
		}
		else
		{
			verbResult = "error";
		}

	}

	if (verbResult == "go")
	{

		if (noun == "north")
		{

			for (int i = 0; i < 10; i++)
			{

				for (int j = 0; j < 10; j++)
				{

					if (world[i][j] == playerLoc)
					{

						if (i - 1 >= 0 && !requireLookup(world[i - 1][j]) && world[i - 1][j] != "nil" && world[i - 1][j] != "")
						{
							playerLoc = world[i - 1][j];
							std::cout << textParse(playerLoc) << std::endl;
							return;
						}
						else
						{
							std::cout << "You are unable to go that way." << std::endl;
						}

					}

				}

			}

		}
		else if (noun == "south")
		{

			for (int i = 0; i < 10; i++)
			{

				for (int j = 0; j < 10; j++)
				{

					if (world[i][j] == playerLoc)
					{

						if (i + 1 <= 19 && !requireLookup(world[i + 1][j]) && world[i + 1][j] != "nil" && world[i + 1][j] != "")
						{
							playerLoc = world[i + 1][j];
							std::cout << textParse(playerLoc) << std::endl;
							return;
						}
						else
						{
							std::cout << "You are unable to go that way." << std::endl;
						}

					}

				}

			}

		}
		else if (noun == "east")
		{

			for (int i = 0; i < 10; i++)
			{

				for (int j = 0; j < 10; j++)
				{

					if (world[i][j] == playerLoc)
					{

						if (j + 1 <= 19 && !requireLookup(world[i][j + 1]) && world[i][j + 1] != "nil" && world[i][j + 1] != "")
						{
							playerLoc = world[i][j + 1];
							std::cout << textParse(playerLoc) << std::endl;
							return;
						}
						else
						{
							std::cout << "You are unable to go that way." << std::endl;
						}

					}

				}

			}

		}
		else if (noun == "west")
		{

			for (int i = 0; i < 10; i++)
			{

				for (int j = 0; j < 10; j++)
				{

					if (world[i][j] == playerLoc)
					{

						if (j - 1 >= 0 && !requireLookup(world[i][j - 1]) && world[i][j - 1] != "nil" && world[i][j - 1] != "")
						{
							playerLoc = world[i][j - 1];
							std::cout << textParse(playerLoc) << std::endl;
							return;
						}
						else
						{
							std::cout << "You are unable to go that way." << std::endl;
						}

					}

				}

			}

		}

	}
	else if (verbResult == "look")
	{

		if (idLookup(noun) != std::string::npos && parentLookup(playerLoc, noun) == true)
		{
			std::cout << textParse(noun) << std::endl;
		}
		else
		{
			std::cout << "There is no " << noun << " to look at." << std::endl;
		}

	}
	else if (verbResult == "grab")
	{
		if (idLookup(noun) != std::string::npos && parentLookup(playerLoc, noun) == true)
		{

			if (noun == "key")
			{

				if (inventory[1] != "key")
				{
					inventory[1] = "key";
					std::cout << textParse(noun) << std::endl;
				}
				else
				{
					std::cout << "You already have that!" << std::endl;
				}

			}

		}
		else
		{
			std::cout << "You can't grab that!" << std::endl;
		}

	}
	else if (verb == "help")
	{
		std::cout << "Type a verb such as go or walk and then a direction such as north or east to go that direction." << std::endl;
		std::cout << "Type \"Look\" and then an object name to examine an object." << std::endl;
		std::cout << "Type a verb such as \"grab\" and then an object to put that object in your inventory." << std::endl;
	}
	else
	{
		std::cout << "Sorry, I don't understand you. Type \"Help\" if you need help." << std::endl;
	}
}// end of userInputParse

int idLookup(std::string idSearch)
{
	// ****************** variable declarations **************************
	std::string lineData = "";	// Line of data from world XML
	std::string output = "";	// ID from line of data

	infile.clear();
	infile.seekg(0);

	while (!infile.eof())
	{

		try
		{
			std::getline(infile, lineData);
			output = lineData.substr(lineData.find("id=\"" + idSearch) + 4, idSearch.length());

			if (output == idSearch)
			{
				return lineData.find(idSearch);
			}

		}
		catch (...)
		{
			output = "ID Not Found";
		}
	}

	return 0;

}// end of idLookup

bool parentLookup(std::string parentSearch, std::string holdingSearch) // Returns true if item found in current location
{
	// ****************** variable declarations **************************
	std::string lineData = "";		// Line of data
	std::string parentOutput = "";	// Parent from line of data
	std::string holdingOutput = ""; // Held object from line of data

	infile.clear();
	infile.seekg(0);

	while (!infile.eof())
	{
		std::getline(infile, lineData);
			
		try
		{
			parentOutput = lineData.substr(lineData.find("parent=\"" + parentSearch) + 8, parentSearch.length());
			holdingOutput = lineData.substr(lineData.find("holding=\"" + parentSearch) + 9, parentSearch.length());

			if (parentOutput == parentSearch && holdingOutput == holdingOutput)
			{
				return true;
			}

		}
		catch (...)
		{

		}

	}

	return false;

}// end of parentLookup

bool requireLookup(std::string idSearch) // Check XML if the location is locked
{
	// ****************** variable declarations **************************
	std::string lineData = "";	// Line of data from world XML
	std::string output = "";	// ID from line of data

	infile.clear();
	infile.seekg(0);

	while (!infile.eof())
	{

		try
		{
			std::getline(infile, lineData);
			output = lineData.substr(lineData.find("id=\"" + idSearch) + 4, idSearch.length());

			if (output == idSearch)
			{

				if (lineData.find("require=\"") != std::string::npos && inventory[1] != lineData.substr(lineData.find("require=\"" + inventory[1]) + 9, inventory[1].length()))
				{
					return true;
				}
				else
				{
					return false;
				}

			}

		}
		catch (...)
		{
			output = "ID Not Found";
		}

	}

	return false;
}// end of requireLookup

std::string textParse(std::string stringSearch)
{
	// ****************** variable declarations **************************
	std::string lineData = ""; // Line of data from world XML

	idLookup(stringSearch);

	while (!infile.eof())
	{

		try
		{
			std::getline(infile, lineData);
			return lineData.substr(lineData.find(">") + 1, lineData.find("</text>") - lineData.find(">") - 1);
		}
		catch (...)
		{

		}

	}

	return "";
}// end of textParse