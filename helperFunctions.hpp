//header file for some helper functions
#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include "Entry.hpp"

// Display messages or prompts.
void displayIntro();
char displayMainMenu();
void displayOutro();
std::string getPrompt();

// Utility functions.
void clearTheScreen();
void pause();
void encryptString(std::string&, int);
void printFileContents(std::string);

// Validation functions.
char validateMenuChoice(char);
char getYesNoAnswer();
int validateIntRange(int, int);
std::string getPrompt();
int countWords(std::string);
bool validateInput(std::string,int);

#endif
