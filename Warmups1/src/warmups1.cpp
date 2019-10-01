// TODO: Write a comment header here with your name and assignment number.

// TODO: Write your functions in this file.


#include <cctype>      // for char-related functions
#include <cmath>       // for abs
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "strlib.h"    // Stanford string functions
using namespace std;


// TODO: implement this function
void rangeOfNumbers(int start, int end) {
    // TODO
    if (start == end){
        cout << start;
    }
    if (start < end){
        for (int i = start; i <= end; i++){
            if (i != end){
                cout << i << ", ";
            }
            else{
                cout << i;
            }

        }
    }
    if (start > end){
        for (int i = start; i >= end; i--)
            if (i != end){
                cout << i << ", ";
            }
            else{
                cout << i;
            }
    }

}

// TODO: implement this function
string replaceAll(string s, char c1, char c2) {
    std::string newString = "";
    std::string replaceString(1,c2);
    for (int i = 0; i < s.length(); ++i){
        if (s[i] != c1){
            newString.append(s.substr(i,i+1));
        }
        else{
            newString.append(replaceString);
        }
    }
    return newString;   // TODO: remove this line
}
