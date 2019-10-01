/**
 * CS 106B, Homework 1, Part B: Warmups
 *
 * This program contains code to test your warm-up functions.
 * If you do not want to use CodeStepByStep, you can use this
 * project to write your code.
 *
 * DO NOT MODIFY THIS FILE.
 * Instead, put your code in warmups1.cpp.
 * This file is an instructor-provided testing program that will
 * run your functions to check their behavior.
 */

#include <iostream>    // for cout, endl
#include "console.h"   // for graphical console
#include "simpio.h"    // for getLine
using namespace std;

// function prototype declarations
// (we declare prototypes for your functions, too, as 'extern' or external)
void intro();
extern void rangeOfNumbers(int start, int end);
extern string replaceAll(string s, char c1, char c2);
void menu();
void test_rangeOfNumbers();
void test_replaceAll();

int main() {
    intro();
    menu();
    cout << "Exiting." << endl;
    return 0;
}

void intro() {
    cout << "CS 106B Homework 1 Warmups test program" << endl;
    cout << "This program helps you manually test the" << endl;
    cout << "warmup functions you wrote in warmups1.cpp." << endl;
    cout << "=======================================" << endl;
    cout << endl;
}

void menu() {
    int choice = -1;
    while (choice != 0) {
        cout << "1) rangeOfNumbers" << endl;
        cout << "2) replaceAll" << endl;
        cout << "0) quit" << endl;
        choice = getIntegerBetween("Your choice? ", 0, 2);
        if (choice == 1) {
            test_rangeOfNumbers();
        } else if (choice == 2) {
            test_replaceAll();
        }
        cout << endl;
    }
}

void test_rangeOfNumbers() {
    int start = getInteger("Start?");
    int end   = getInteger("End?  ");
    rangeOfNumbers(start, end);
}

void test_replaceAll() {
    string s = getLine("s? ");
    char c1  = getChar("c1? ");
    char c2  = getChar("c2? ");
    string result = replaceAll(s, c1, c2);
    cout << "replaceAll(\"" << s << "\", '" << c1 << "', '" << c2
         << "') returns \"" << result << "\"" << endl;
}

