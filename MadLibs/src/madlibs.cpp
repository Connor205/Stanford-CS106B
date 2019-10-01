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
    cout << "Welcome to CS 106B Mad Libs!\nI will ask you to provide various words \nand phrases to fill in a story. \nAt the end, I will display your story to you.\n\n";
    bool fileVerified = false;
    // Makes sure that the file exists before moving forward
    string fileName;
    while (!fileVerified){
        fileName = getLine("Mad Lib input file?");
        if (!fileExists((fileName))){
            cout << "Unable to open that file.  Try again.\n";
        }
        else {
            fileVerified = true;
        }
    }
    string line;
    ifstream finalStory;
    ifstream document(fileName);
    while (getline(document, line))
    {
        if (!line.empty()){
            size_t foundFirst = line.find("<");
            size_t foundSecond = line.find("<");
            if (foundFirst != string::npos && foundSecond != string::npos){

            }
            line.find("<");
        }
    }



    cout << line[1];
//    string text = readEntireFile(fileName);
//    cout << text;


    return 0;
}


