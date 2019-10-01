#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "regex"
using namespace std;

int main() {
    // TODO: Finish the program!
    int numStories = 0;
    int numTotalReplacements = 0;
    bool doMadlib = true;
    cout << "Welcome to CS 106B Mad Libs!\nI will ask you to provide various words \nand phrases to fill in a story. \nAt the end, I will display your story to you.\n\n";
    while(doMadlib){
        bool fileVerified = false;
        // Makes sure that the file exists before moving forward
        string fileName;
        while (!fileVerified){
            fileName = getLine("Mad Lib input file?"); // gets user input for file name
            if (!fileExists((fileName))){
                cout << "Unable to open that file.  Try again.\n";
            }
            else {
                fileVerified = true;
            }
        }
        //Runs through the file and replaces each placeholder with user inputted text
        string line;
        string finalStory;
        ifstream document(fileName);
        int numReplacements = 0;

        // Goes through each line in the file
        while (getline(document, line))
        {
            if (!line.empty()){
                string newLine;
                size_t foundFirst = line.find("<");
                size_t foundSecond = line.find(">");
                //Deals with multiple placeholders in the same line
                while(foundFirst != string::npos && foundSecond != string::npos){
                    string prompt = line.substr(foundFirst + 1, foundSecond - foundFirst - 1);
                    //                cout << line << "\n";
                    //                cout << prompt << "\n";
                    // Deals with vowels
                    if (tolower(prompt.at(0)) == 'a' || tolower(prompt.at(0)) == 'e' || tolower(prompt.at(0)) == 'i' || tolower(prompt.at(0)) == 'o' || tolower(prompt.at(0)) == 'u' ){
                        line = line.replace(foundFirst, foundSecond - foundFirst + 1, getLine("Please enter an " + prompt));
                    }
                    else{
                        line = line.replace(foundFirst, foundSecond - foundFirst + 1, getLine("Please enter a " + prompt));
                    }

                    numReplacements++;
                    foundFirst = line.find("<");
                    foundSecond = line.find(">");
                }
            }
            finalStory.append(line + "\n");
        }

        //Prints the madlib story
        cout << "\nYour Mad Lib story:\n";
        cout << finalStory;
        cout << "\n";

        // Prints the number of replacements
        if (numReplacements == 1){
            cout << numReplacements << "placeholder replaced.\n";
        }
        else{
            cout << numReplacements << "placeholders replaced.\n";
        }
        numTotalReplacements += numReplacements;
        numStories++;
        doMadlib = getYesOrNo("Do another Mad Lib (Y/N)?", "Invalid input, try again.");
    }
    double averageReplacements = numTotalReplacements/numStories;
    cout << "Mad Lib stories you created: " << numStories;
    cout << "\nTotal placeholders replaced: " << numTotalReplacements << " (" << averageReplacements << fixed << setprecision(1) << ")";

    return 0;
}


