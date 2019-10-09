/**
 * CS 106B, Homework 2, Part B: Warmups
 *
 * This program contains code to test your warm-up functions.
 * If you do not want to use CodeStepByStep, you can use this
 * project to write your code.
 *
 * DO NOT MODIFY THIS FILE.
 * Instead, put your code in warmups2.cpp.
 * This file is an instructor-provided testing program that will
 * run your functions to check their behavior.
 */

#include <iostream>    // for cout, endl
#include "console.h"   // for graphical console
#include "map.h"
#include "set.h"
#include "simpio.h"    // for getLine
#include "stack.h"
#include "vector.h"
using namespace std;

// function prototype declarations
// (we declare prototypes for your functions, too, as 'extern' or external)
void intro();
extern void collapse(Stack<int>& stack);
extern char mostCommonFirstChar(Set<string>& set);
void menu();
void test_collapse();
void test_mostCommonFirstChar();

int main() {
    intro();
    menu();
    cout << "Exiting." << endl;
    return 0;
}

void intro() {
    cout << "CS 106B Homework 2 Warmups test program" << endl;
    cout << "This program helps you manually test the" << endl;
    cout << "warmup functions you wrote in warmups2.cpp." << endl;
    cout << "=======================================" << endl;
    cout << endl;
}

void menu() {
    int choice = -1;
    while (choice != 0) {
        cout << "1) collapse" << endl;
        cout << "2) mostCommonFirstChar" << endl;
        cout << "0) quit" << endl;
        choice = getIntegerBetween("Your choice? ", 0, 2);
        if (choice == 1) {
            test_collapse();
        } else if (choice == 2) {
            test_mostCommonFirstChar();
        }
        cout << endl;
    }
}

void test_collapse() {
    string stackStr = getLine("Stack? ");
    Stack<int> stack;

    // convert the user input into a stack
    istringstream input(stackStr);
    if (!(input >> stack)) {
        cerr << "Invalid stack format." << endl;
        return;
    }

    collapse(stack);
    cout << "after collapse: " << stack << endl;
}

void test_mostCommonFirstChar() {
    string setStr = getLine("Set? ");
    Set<string> set;

    // convert the user input into a stack
    istringstream input(setStr);
    if (!(input >> set)) {
        cerr << "Invalid set format." << endl;
        return;
    }

    char ch = mostCommonFirstChar(set);
    cout << "mostCommonFirstChar returned: '" << ch << "'" << endl;
}
