//A few additional functions

#include "helperFunctions.hpp"
#include <sstream>		// stringstream
#include <string>		// string
#include <iostream>		// cin, cout, getline
#include <cctype>		// tolower


/*******************************************************************************
* Function					void displayIntro()
* Description: Displays the intro the program.
*******************************************************************************/
void displayIntro() {
	printFileContents("REWIND-REVITALIZE.txt");
	std::cout << "\n                        A journaling program\n" <<
				"                   by Team The Unhandled Exceptions\n" <<
				"         Andrew Swaim, Michael Stanley, "
			<< "and Jordan Bartos\n\n\n\n\n" << std::endl;

}

/*******************************************************************************
* Function					char displayMainMenu()
* Description: Displays the main menu for the program. Returns the maximum
* selection in order to validate the user's selection.
*******************************************************************************/
char displayMainMenu() {

	std::cout << "\n\nMAIN MENU\n\n"
		<< "1) Make a new journal entry\n"
		<< "2) REWIND to a happy memory\n"
		<< "3) View lifetime statistics\n"
		<< "4) Entry Search\n"
		<< "5) Exit\n\n";

	return '5';
}


/*******************************************************************************
* Function					char displayMainMenu()
* Description: Displays the main menu for the program. Returns the maximum
* selection in order to validate the user's selection.
*******************************************************************************/
void displayOutro() {

	std::cout << "\n\nHave a wonderful day!\n";
	// TODO: Maybe display a random inspirational quote on exiting?
}

/*******************************************************************************
* Function:			string getPrompt()
* Description: returns a string for a randomly selected prompt. Prompts are
* stored in a text file and the function randomly decides which line to use.
*******************************************************************************/
std::string getPrompt()
{
	//Initialize random number and open prompt file
	int num = rand();
	fstream input;
	std::string prompt;
	input.open("prompts.txt");
	if (!input)
	{
		cout << "File open error" << endl;
		return "No file found";
	}

	//Get random num in range
	num = num % 40 + 1;
	//Loop until the correct line is found
	for (int i = 0; i < num; i++)
	{
		getline(input, prompt);
	}
	input.close();
	return prompt;

}

/*******************************************************************************
 * Function:				void pause()
 * Description: pauses the progress of the program until the user pushes enter.
*******************************************************************************/
void pause()
{
	std::cout << "\n\nPress [Enter] to continue.\n" << std::endl;
	std::string dummyString;
	std::getline(std::cin,dummyString);
}


/*******************************************************************************
 * Function					void clearTheScreen()
 * Description: clears the screen.
*******************************************************************************/
void clearTheScreen()
{
	//this was found at http://stackoverflow.com/questions/17335816/clear-scren
	//-using-c
	std::cout << "\033[2J\033[1;1H";
}

/*******************************************************************************
* Function					char validateMenuChoice(char)
* Description: validates a numerical menu selection made by the user to
* to determine if they selected a valid option. If the selection in the valid
* range from 1 to the max possible selection, returns the selection as a char.
*******************************************************************************/
char validateMenuChoice(char max) {

	bool validChoice = false;	// Error flag
	std::string input;			// To hold a line of user input
	char selection;				// To hold the final menu selection by the user
	std::stringstream ss;		// stringstream for validating user input.

	// Do-while loop will run until the user enters a valid input.
	do {

		// Read a line of input from the user.
		getline(std::cin, input);

		// Load stringstream with the user input.
		ss.str(input);

		// Get first char and make sure nothing is left over.
		if (ss >> selection && !(ss >> input)) {

			// Make sure the selection is in a valid range.
			if (selection >= '1' && selection <= max) {

				validChoice = true;
			}
		}

		// Display error message and loop again if input is invalid.
		if (validChoice == false) {

			std::cout << "\nSorry, you must select an option between"
				<< " 1 and " << max << ". Please re-enter selection.\n";

			// Clear stringstream buffer to prepare for next loop.
			ss.clear();
		}

	} while (validChoice == false);

	return selection;
}

/*******************************************************************************
* Function					char getYesNoAnswer()
* Description: gets a valid yes or no answer from the user. Returns a 'y' if
* the user answers y/Y or a 'n' if the user answers n/N.
*******************************************************************************/
char getYesNoAnswer() {

	bool validChoice = false;	// Error flag
	std::string input;			// To hold a line of user input
	char answer;				// To hold the answer by the user
	std::stringstream ss;		// stringstream to validate user input

	// Do-while loop will run until the user inputs a valid answer.
	do {

		// Get a line of user input.
		getline(std::cin, input);

		// Load the stringstream with user input.
		ss.str(input);

		// Get the first char and make sure there is nothing left over.
		if (ss >> answer && !(ss >> input)) {

			// Convert to lowercase.
			answer = std::tolower(answer);

			// Check if valid answer.
			if (answer == 'y' || answer == 'n') {

				validChoice = true;
			}
		}

		// If input invalid, display error message and loop again.
		if (validChoice == false) {

			std::cout << "\nSorry, you must enter a 'y' or 'n' answer. "
				<< "Please re-enter answer.\n";

			// Clear stringstream buffer to prepare for next loop.
			ss.clear();
		}

	} while (validChoice == false);

	return answer;
}

/*******************************************************************************
* Function					int validateIntRange(int, int)
* Description: returns an integer between the two passed argument integers
*******************************************************************************/

int validateIntRange(int lower, int upper)
{
	std::string getter;
	bool isValid = false;
	bool isNegative = false;

	do
	{
		cout << endl;
		getline(cin, getter);
		for(unsigned int i = 0; i < getter.length(); i++)
		{
			//If hyphen is in front adjust negative flag
			if(getter[0] == '-' && !isNegative)
			{
				isNegative = true;
				i++;
			}

			//Check all other chars or digit
			if (!(isdigit(getter[i])))
			{
				isValid = false;
				break;
			}
			else
			{
				isValid = true;
			}
		}

		//If it is a digit, break
		if(isValid)
		{
			break;
		}
		cin.clear();
		cout << "Input not valid" << endl;
	} while (!isValid);

	//Convert to int and determine if it is in range
	if(isNegative)
	{
		getter = getter.substr(1, (getter.length() - 1));
	}

	int userInput = std::atoi(getter.c_str());

	if (isNegative)
	{
		userInput *= -1;
	}

	if(userInput >= lower && userInput <= upper)
	{
		isValid = true;
	}
	else
	{
		cout << "Please enter a number between " << lower << " and " << upper << endl;
		cin.clear();
		userInput = validateIntRange(lower, upper);
	}

	return userInput;

}


/*******************************************************************************
 * Function:			int countWords()
 * Description: counts the number of words in the body of the string and returns the int
*******************************************************************************/
int countWords(std::string s)
{
	int len = s.length();
	int words = 1; // Otherwise wouldn't count the last word.
	for(int i = 0; i < len; i++)
	{
		if(i < len - 2)
		{
			if(s.at(i) == ' ' && s.at(i + 1) != ' ')
			{
				words++;
			}
			if(s[i] == '\n')
			{
				words++;
			}
		}
		else
		{
			if(s[i] == '\n')
			{
				words++;
			}
		}
	}
 	return words;
}

/*************************************************************************************
 * Function			void encryptString(string to encrypt, int key)
 * Description: takes a string by reference and applies an encryption key to the string
 * by XORing each character of the string by the key. It can also be used to apply
 * the reversing the encryption
**************************************************************************************/
void encryptString(std::string& toEncrypt, int key)
{
	for(unsigned int i = 0; i < toEncrypt.length(); ++i)
	{
		toEncrypt.at(i) ^= key;
	}
}


/**************************************************************************************
 * Function			printFileContents(string)
 * Prints all the contents of a file
**************************************************************************************/
void printFileContents(std::string str)
{
	std::string printString;
	std::ifstream ifs(str);

	if(ifs)
	{
		while(ifs && ifs.peek() != EOF)
		{
			getline(ifs,printString);
			std::cout << printString << std::endl;
		}

	}

}

/*******************************************************************************
 * Function:			bool validateInput(string,int)
 * Description: Takes a string to be validated and an int that is the maximum
 * allowable length of the string. Returns true if the supplied string does not
 * contain any characters besides alphanumeric characters and '-' or '_' and is
 * less than or equal to the maximum length. Otherwise returns false.
********************************************************************************/
bool validateInput(std::string inputString, int maxLength)
{
	//inputString must be greater than 0 characters long and less than or equal
	//to maximum allowable length
	if(inputString.length() > 0 && inputString.length() <= maxLength)
	{
		for(unsigned int i = 0; i < inputString.length(); ++i)
		{
			if(inputString.at(i) < 65 && inputString.at(i) != '-')
			{
				 return false;
			}
			else if(inputString.at(i) > 90 && inputString.at(i) < 97 && inputString.at(i) != '_')
			{
				return false;
			}
			else if(inputString.at(i) > 122 && inputString.at(i) != '_'
					&& inputString.at(i) != '-')
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}
