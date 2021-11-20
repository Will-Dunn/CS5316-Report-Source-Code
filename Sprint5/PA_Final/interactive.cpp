//Owner: Elliot Boesch
//Created 12-7-19
//Updated 12-8-19
//  -Improved the design of output
//  -Added functions to create AVL index
//  -Added functions to create Hash index

#include "interactive.h"
#include "query.h"
#include <iostream>
#include <string>
#include <sstream>
#include "maintenance.h"

using namespace std;

/* The interactice class is deisgned for the interactive mode of the user interface.
 * This class will allows the user to determine wether or not they want
 * the index loaded into an AVL tree or a hash table
 */
Interactive::Interactive(){
    cout << "-----Welcome to the Interactive Mode-----" << endl;

while(true){    cout << "Continue- 1\n"<<
           "Print Stats- 2\n"<<

                     "Quit- 3"<< endl;
    cout << "Your choice: ";
    cin >> userChoice;

    if(userChoice == 2)
        printBasicStats();
    if(userChoice == 3)
        exit(1);
    cin.ignore(1000, '\n');
    Query userQuery;}//at this point jumps to query.cpp
}

/* This function will load the index into an AVL tree
 */
void Interactive::avlIndex(){
    //Need some function call to create the index in an AVL
    choice=true;
    AVLTree<Term> index;
    avIND.readPeristantIndex(index);

}


/* This function will load the index into a Hash Table
 */
void Interactive::hashIndex(){
    choice=false;
    hashTable<string,Term> index;
    hashind.readPeristantIndex(index);
    //Need some function call to create the index in a hash table
}


/* This function will print the basic stats of the search egnine
 * This includes:
 * Total number of opinions indexed
 * The average number of words indexed per opinion
 * The top 50 most frequent words
 */
void Interactive::printBasicStats(){
    cout << "Here are some basic stats of the search engine:" << endl;
    fstream sta;
    sta.open("stats.txt");
    string inp;
    sta>>inp;
    cout << "Number of opinions being searched: "<<inp<<endl;
    sta>>inp;
    cout<< "Number of Terms: "<<inp<<endl;
    sta>>inp;
    cout<< "Average Number of Terms per file: "<<inp<<endl;
    AVLTree<Term> top50;
    avIND.readPeristantIndex(top50);
    cout <<"index top 50 most common words\n"<<avIND.top50()<<endl;
    //Should print the basic stats of the search engine
}
/*
 * QA Notes:
 * thia
 */