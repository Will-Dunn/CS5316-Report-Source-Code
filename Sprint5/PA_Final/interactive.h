//Owner: Elliot Boesch
//Created 12-7-19
//Updated 12-8-19
//  -Improved the design of output
//  -Added functions to create AVL index
//  -Added functions to create Hash index

/* The interactice class is deisgned for the interactive mode of the user interface.
 * Theis class will allows the user to determine wether or not they want
 * the index loaded into an AVL tree or a hash table
 */

//SEE MORE IN INTERACTIVE.CPP

#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <iostream>
#include<string>
#include "index.h"

using namespace std;

class Interactive{
    private:
        int userChoice;
        string search;
        bool choice;
        Index<hashTable<string,Term>> hashind;
        Index<AVLTree<Term>> avIND;

    public:
        Interactive();
        void avlIndex();
        void hashIndex();
        void printBasicStats();
};

#endif // INTERACTIVE_H
