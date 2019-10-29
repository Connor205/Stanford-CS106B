#include "boggle.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "lexicon.h"
#include "random.h"
#include "set.h"
#include "shuffle.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "gui.h"
using namespace std;

// function prototype declarations
void intro();
bool checkWord(string word, Lexicon& dictionary, Set<string> wordsList, Grid<char>& board);
bool recusiveHumanWordSearch(Grid<char>& board, Grid<bool>& visited, string word, string currentword, int characterCount, int row, int col);
Grid<bool> copyGrid(Grid<bool> toCopy);
Grid<char> generateRandomGrid(int size);
Grid<char> getGrid(int size);
Set<string> humanPlayersTurn(Grid<char>& board, Lexicon& dictionary);
bool recursiveComputerWordSearch(Grid<char> board, Grid<bool> visited, string currentString, Lexicon& dictionary, Set<string>& words, Set<string> humanWords, int& score, int row, int col);
void printGrid (Grid<char> board);

int main() {
    gui::initialize(BOARD_SIZE, BOARD_SIZE);
    Lexicon dictionary(DICTIONARY_FILE); // creates dictionary
    bool firstTime = true;
    do{
        if (!firstTime){
            gui::initialize(BOARD_SIZE, BOARD_SIZE);
        }
        else{
            intro();
        }
        cout << endl;
        Grid<char> board = getGrid(BOARD_SIZE);
        printGrid(board);
        gui::labelCubes(board);
        Set<string> humanWords = humanPlayersTurn(board, dictionary);
        //cout << "Running Computer Word Search";
        Set<string> computerWords = computerWordSearch(board, dictionary, humanWords);
        firstTime = false;
    }
    while (getYesOrNo("Play again?"));



    // TODO: write the rest of the program!

    cout << "Have a nice day." << endl;
    return 0;
}

// Prints a welcome message that introduces the program to the user.
void intro() {
    cout << "Welcome to CS 106B Boggle!" << endl;
    cout << "This game is a search for words on a 2-D board of letter cubes." << endl;
    cout << "The good news is that you might improve your vocabulary a bit." << endl;
    cout << "The bad news is that you're probably going to lose miserably to" << endl;
    cout << "this little dictionary-toting hunk of silicon." << endl;
    cout << "If only YOU had 16 gigs of RAM!" << endl;
    cout << endl;
    getLine("Press Enter to begin the game ...");
}

//Gets the grid used for the game. Deals with user inputted board as well as calls generate Random
// Grid to create random grid
Grid<char> getGrid(int size){
    if (getYesOrNo("Generate a random board?", "Please type a word that starts with 'Y' or 'N'.")){
        return generateRandomGrid(size);
    }
    else{
        string gridInput = "";
        gridInput = getLine("Type the 16 letters on the board:");
        while(gridInput.length() != 16){
            gridInput = getLine("Invalid board string. Try again.");
        }
        Grid<char> board (size, size);
        int gridValue = 0;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                board[i][j] = toupper(gridInput.at(gridValue));
                gridValue ++;
            }
        }
        return board;
    }
}

// Generates a random grid based on the size inputted
Grid<char> generateRandomGrid(int size){
    Grid<char> board(size, size);
    int gridValue = 0;
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            int choice = randomInteger(0,5);
            char letter;
            if (size == 4){
                letter = LETTER_CUBES[gridValue].at(choice);
            }
            if(size == 5){
                letter = LETTER_CUBES_BIG[gridValue].at(choice);
            }
            if (size == 6){
                letter = LETTER_CUBES_SUPER_BIG[gridValue].at(choice);
            }
            board[row][col] = letter;
            gridValue += 1;
        }
    }
    shuffle(board);
    return board;
}

void printGrid(Grid<char> board){
    for (int i = 0; i < board.numRows(); i++){
        for (int j = 0; j < board.numCols(); j++){
            cout << board[i][j];
        }
        cout << endl;
    }
}
//Deals with the entire players turn
Set<string> humanPlayersTurn(Grid<char>& board, Lexicon& dictionary){
    int score = 0;
    cout << endl << "It's your turn!" << endl;
    string currentWord = " ";
    Set<string> playerWords;

    while(currentWord != ""){
        cout << "Your Words: " << playerWords.toString() << endl;
        cout << "Yout Score: " << score << endl;
        currentWord = getLine("Type a word (or Enter to stop):");
        if (currentWord != "" && checkWord(currentWord, dictionary, playerWords, board)){
            playerWords.add(currentWord);
            if(currentWord.length() == 4){
                score+= 1;
            }
            else if (currentWord.length() == 5){
                score += 2;
            }
            else if(currentWord.length() == 6){
                score += 3;
            }
            else if(currentWord.length() == 7)
                score += 5;
            else {
                score += 11;
            }
            cout << "You found a new word! \"" << currentWord << "\"" <<endl << endl;

            gui::setScore("human", score);
            gui::recordWord("human", currentWord);
        }
    }
    return playerWords;
}

//Checks to see if a word is valid, both in dictionary and with the board
bool checkWord(string word, Lexicon& dictionary, Set<string> wordsList, Grid<char>& board){
    bool checking = true;
    string lowerWord = toLowerCase(word);
    string upperWord = toUpperCase(word);
    if(find(wordsList.begin(), wordsList.end(), lowerWord) != wordsList.end()){
        checking = false;
        cout << "Word has already been entered." << endl;
    }
    else if(lowerWord.length() < 4){
        checking = false;
        cout << "Word is not long enough" << endl;
    }
    else if (!dictionary.contains(lowerWord) ){
        checking = false;
        cout << "That word is not found in the dictionary." << endl;
    }
    else if (!humanWordSearch(board, upperWord)){
        checking = false;
        cout << "That word can't be formed on this board." << endl;
    }
    return checking;
}

//Calls the recusive human word search starting at every point in the grid. Returns whether or not the word is able to be formed
bool humanWordSearch(Grid<char>& board, string word) {
    // TODO: write this function
    bool found = false;
    for (int i = 0; i < board.numRows(); i++){
        for (int j = 0; j < board.numCols(); j++){
            Grid<bool> visted (board.numRows(), board.numCols(), false);
            if (recusiveHumanWordSearch(board, visted, word, "", 0, i, j)){
                found = true;
                return true;
            }
        }
    }
    return false;
}

//Recursive method for human search. Returns false if the word is not possibly going to be formed or if the inputs are out of range. Otherwise
//calls the method with the current word to all points around current point
bool recusiveHumanWordSearch(Grid<char>& board, Grid<bool>& visited, string word, string currentword, int characterCount, int row, int col){
    if (row < 0 || col < 0 || col > board.numCols() - 1 || row > board.numRows() - 1){
        // Out of range or already used
        //cout << "out of range" << endl;
        return false;
    }
    if (visited[row][col]){
        //cout << "used" << endl;
        return false;
    }
    else{ // adds word to current string and marks the spot as used, increases character count
        currentword = currentword + board[row][col];
        visited[row][col] = true;
        characterCount += 1;
        //cout << "Current Word: " << currentword << endl;
    }
    if(currentword == word){
        //cout << "Returns true";
        return true;
    }
    if (currentword != word.substr(0,characterCount)){
        //cout << "Substring Fail" << endl;
        return false;
    }
    else{
        Grid<bool> grid1 = copyGrid(visited);
        Grid<bool> grid2 = copyGrid(visited);
        Grid<bool> grid3 = copyGrid(visited);
        Grid<bool> grid4 = copyGrid(visited);
        Grid<bool> grid5 = copyGrid(visited);
        Grid<bool> grid6 = copyGrid(visited);
        Grid<bool> grid7 = copyGrid(visited);
        Grid<bool> grid8 = copyGrid(visited);
        if (recusiveHumanWordSearch(board, grid1, word, currentword, characterCount, row - 1, col - 1)){
            return true;
        }
        if (recusiveHumanWordSearch(board, grid2, word, currentword, characterCount, row - 1, col)){
            return true;
        }
        if (recusiveHumanWordSearch(board, grid3, word, currentword, characterCount, row - 1, col + 1)){
            return true;
        }
        if (recusiveHumanWordSearch(board, grid4, word, currentword, characterCount, row, col - 1)){
            return true;
        }
        if (recusiveHumanWordSearch(board, grid5, word, currentword, characterCount, row, col + 1)){
            return true;
        }
        if (recusiveHumanWordSearch(board, grid6, word, currentword, characterCount, row + 1, col - 1)){
            return true;
        }
        if (recusiveHumanWordSearch(board, grid7, word, currentword, characterCount, row + 1, col)){
            return true;
        }
        if (recusiveHumanWordSearch(board, grid8, word, currentword, characterCount, row + 1, col + 1)){
            return true;
        }
    }
    return false;

}

Grid<bool> copyGrid(Grid<bool> toCopy){
    Grid<bool> newGrid (toCopy.numRows(), toCopy.numCols());
    for (int i = 0; i < newGrid.numRows(); i++){
        for (int j = 0; j < newGrid.numCols(); j++){
            newGrid[i][j] = toCopy[i][j];
        }
    }
    return newGrid;
}

Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary, Set<string>& humanWords) {
    // TODO: write this function
    // This should call the recusive function for all starting points
    Set<string>::iterator it = humanWords.begin();
    int humanScore = 0;
    while(it != humanWords.end()){
        string currentWord = *it;
        if (currentWord.length() == 4){
            humanScore += 1;
        }
        if (currentWord.length() == 5){
            humanScore += 2;
        }
        if (currentWord.length() == 6){
            humanScore += 3;
        }
        else if(currentWord.length() == 7)
            humanScore += 5;
        else {
            humanScore += 11;
        }
        it++;
    }
    cout << endl << "It's my turn!" << endl;
    Set<string> words;
    int computerScore = 0;
    for (int i = 0; i < board.numRows(); i ++){
        for (int j = 0; j < board.numCols(); j++){
            Grid<bool> visited (board.numRows(), board.numCols(), false);
            recursiveComputerWordSearch(board, visited, "", dictionary, words, humanWords, computerScore, i, j);
        }
    }
    cout << "My Words: " << words.toString() << endl;
    cout << "My Score: " << computerScore <<  endl;
    if (humanScore > computerScore){
        cout  << "WOW, you defeated me! Congratulations!" << endl << endl;
    }
    else if(humanScore < computerScore){
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl << endl;
    }
    else{
        cout << "WOW, we tied. That was unexpected" << endl << endl;
    }



    return words;
}

bool recursiveComputerWordSearch(Grid<char> board, Grid<bool> visited, string currentString, Lexicon& dictionary, Set<string>& words, Set<string> humanWords, int& score, int row, int col){
    if (row < 0 || col < 0 || col > board.numCols() - 1 || row > board.numRows() - 1){
        // Out of range or already used
        //cout << "out of range" << endl;
        return false;
    }
    if (visited[row][col]){
        //cout << "visited" << endl;
        return false;
    }
    else{
        currentString = currentString + board[row][col];
        visited[row][col] = true;
        if (currentString.length() > 3 && dictionary.contains(currentString) && !humanWords.contains(currentString) && !words.contains(currentString)){
            words.add(currentString);
            gui::recordWord("computer", currentString);
            if(currentString.length() == 4){
                score+= 1;
            }
            else if (currentString.length() == 5){
                score += 2;
            }
            else if(currentString.length() == 6){
                score += 3;
            }
            else if(currentString.length() == 7)
                score += 5;
            else {
                score += 11;
            }
            gui::setScore("computer", score);
        }
        //cout << currentString << endl;
    }
    if (dictionary.containsPrefix(currentString)){
        Grid<bool> grid1 = copyGrid(visited);
        Grid<bool> grid2 = copyGrid(visited);
        Grid<bool> grid3 = copyGrid(visited);
        Grid<bool> grid4 = copyGrid(visited);
        Grid<bool> grid5 = copyGrid(visited);
        Grid<bool> grid6 = copyGrid(visited);
        Grid<bool> grid7 = copyGrid(visited);
        Grid<bool> grid8 = copyGrid(visited);
        recursiveComputerWordSearch(board, grid1, currentString, dictionary, words, humanWords, score, row - 1, col - 1);
        recursiveComputerWordSearch(board, grid2, currentString, dictionary, words, humanWords, score, row - 1, col);
        recursiveComputerWordSearch(board, grid3, currentString, dictionary, words, humanWords, score, row - 1, col + 1);
        recursiveComputerWordSearch(board, grid4, currentString, dictionary, words, humanWords, score, row, col - 1);
        recursiveComputerWordSearch(board, grid5, currentString, dictionary, words, humanWords, score, row, col + 1);
        recursiveComputerWordSearch(board, grid6, currentString, dictionary, words, humanWords, score, row + 1, col - 1);
        recursiveComputerWordSearch(board, grid7, currentString, dictionary, words, humanWords, score, row + 1, col);
        recursiveComputerWordSearch(board, grid8, currentString, dictionary, words, humanWords, score, row + 1, col + 1);
    }
    return true;
}

