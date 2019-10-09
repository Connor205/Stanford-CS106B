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
#include "collections.h"
#include "map.h"
#include "deque.h"
#include "random.h"

using namespace std;

void printIntro();
string getFileName();
int getNValue();


map< vector<string>, vector<string>> getMapFromFileVector(string fileName, int N);

bool fullOutput(map<vector<string>, vector<string>> m, int N);
vector<string> getOuput(map< vector<string>, vector<string>> m, int numWords, int N);
string getNextWord(map< vector<string>, vector<string>> m, vector<string> currentWindow);
vector<string> getStartingPoint(map< vector<string>, vector<string>> m);

void printMap(map<vector<string>, vector<string>> m);
void printArray(string array []);
void printVectorString(vector<string> vectorString);

int main() {
    printIntro();
    string fileName = getFileName();
    int N = getNValue();
    map<vector<string>, vector<string>> m = getMapFromFileVector(fileName,N); //generates the map that is used for output
    while(fullOutput(m,N)){ // does the generation and looping
    }

    cout << "Exiting." << endl;
    return 0;
}

bool fullOutput(map<vector<string>, vector<string>> m, int N){
    int numWords = getInteger("# of random words to generate (0 to quit)? ");
    cout << endl;
    if (numWords ==0){
        return false;
    }
    else{
        vector<string> output = getOuput(m, numWords, N);
        cout << " ... ";
        printVectorString(output);
        cout << " ... " << endl << endl;
        return true;
    }
}

void printIntro(){
    cout <<"Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you."<< endl << endl;
}

string getFileName(){
    bool fileVerified = false;
    // Makes sure that the file exists before moving forward
    string fileName;
    while (!fileVerified){
        fileName = getLine("Input file name? "); // gets user input for file name
        if (!fileExists((fileName))){
            cout << "Unable to open that file.  Try again.\n";
        }
        else {
            fileVerified = true;
        }
    }
    return fileName;
}

int getNValue(){
    int N = getInteger("Value of N? "); // gets user input for file name
    return (N);
}

map< vector<string>, vector<string>> getMapFromFileVector(string fileName, int N){
    vector<string> window;
    vector<string> words;
    map< vector<string>, vector<string>> m;
    ifstream file;
    file.open(fileName);
    string word;
    while(file >> word){ // fills the vector<string> from the file
        words.push_back(word);
    }
    vector<string>::iterator addEnd;
    addEnd = words.begin();
    //Deals with the looping issues
    for (int i = 1; i < N; i++){
        words.push_back(*addEnd);
        ++addEnd;
    }

    int wordCount = 1;
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        vector<string> nextWords;
        string currentWord = *it;
        if (wordCount < N){ // if the window hasn't been filled
            window.push_back(currentWord);
        }
        else{
            // check if the window exists and then either adds on or creates new vector<string>
            map<vector<string>,vector<string>>::iterator mapIterator = m.find(window);
            if (mapIterator != m.end()){
                nextWords = mapIterator->second;

            }
            nextWords.push_back(currentWord);
            m[window] = nextWords;
            window.erase(window.begin());
            window.push_back(currentWord);
        }
        wordCount++;
    }
    return m;
}

vector<string> getStartingPoint(map< vector<string>, vector<string>> m){
    int randomPoint = randomInteger(0,m.size());
    map< vector<string>, vector<string>>::iterator itr;
    itr = m.begin();
    for (int i = 0; i < randomPoint; i++){
        ++itr;
    }
    return itr->first;
}

string getNextWord(map< vector<string>, vector<string>> m, vector<string> currentWindow){
    map< vector<string>, vector<string>>::iterator itr;
    itr = m.find(currentWindow);
    vector<string> words = itr->second;
    int randomPoint = randomInteger(0,words.size()-1);
    string nextWord = words[randomPoint];
    return nextWord;
}

vector<string> getOuput(map< vector<string>, vector<string>> m, int numWords, int N){
    vector<string> output;
    vector<string> currentWindow;
    currentWindow = getStartingPoint(m);
    for (int i = 0; i < currentWindow.size(); i++){
        output.push_back(currentWindow[i]);
    }
    for (int i = N-1; i < numWords; i++){
        string nextWord = getNextWord(m, currentWindow);
        output.push_back(nextWord);
        currentWindow.erase(currentWindow.begin());
        currentWindow.push_back(nextWord);
    }
    return output;
}

void printMap(map<vector<string>, vector<string>> m){
    //cout << "ran printmap" << endl;
    map<vector<string>, vector<string>>::iterator it;
    for (it = m.begin(); it != m.end(); ++it){
        //cout << "in forloop";
        vector<string> first = it->first;
        vector<string> second = it->second;
        vector<string>::iterator stringIt;
        for(stringIt = first.begin(); stringIt != first.end(); ++stringIt){
            cout << *stringIt << " ";
        }
        cout << "--> ";
        for(stringIt = second.begin(); stringIt != second.end(); ++stringIt){
            cout << *stringIt << " ";
        }
        cout << endl;

    }

}

void printVectorString(vector<string> vectorString){
    for (vector<string>::iterator it = vectorString.begin(); it!=vectorString.end(); ++it){
        cout << *it << " ";
    }
}

void printArray(string stringArray []){
    int size = stringArray->size();
    cout << "stringarray size: " << size;
    string a [size];
    for (int i = 0; i < size; i++){
        cout << stringArray[i] << endl;
    }
}
