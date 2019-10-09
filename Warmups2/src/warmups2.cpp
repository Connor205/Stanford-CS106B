// TODO: Write a comment header here with your name and assignment number.

// TODO: Write your functions in this file.


#include <cctype>      // for tolower, etc.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "map.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "strlib.h"    // Stanford string functions
using namespace std;


// TODO: implement this function
void collapse(Stack<int>& stack) {
    cout << "original stack: " << stack;
    Stack<int> backwardsStack;
    Stack<int> finalStack;
    int stackSize = stack.size();

    for (int i = 0; i < stackSize; i++){ // fill new stack
        backwardsStack.push(stack.pop());
    }
    cout << backwardsStack;
    if(stackSize % 2 == 1){
        stackSize += 1;
    }

    for (int i = 0; i < stackSize/2; i++){
        int total = 0;
        total += backwardsStack.pop();
        if (!backwardsStack.isEmpty()){
            total += backwardsStack.pop();
        }
        stack.push(total);
    }


}

// TODO: implement this function
char mostCommonFirstChar(Set<string>& set) {
    Set<string> testing = {"bb", "aa"};
    std :: set <string> :: iterator itr = testing.begin();
    for (itr = testing.begin(); itr != testing.end(); ++itr){

    }
    map<char, int> countLetters;
    for (int i = 0; i < set.size(); i++){
        char = set[i]
    }
}
