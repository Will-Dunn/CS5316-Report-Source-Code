//Owner: Elliot Boesch
//Created: 12-7-19
//Updated: 12-8-19
//  -Improved the design of the output
//  -Added clear index capabilities within clearIndex() function
//  -Added opinions adding capabilities within addOpinions() function
//  -Added parsing corpus and populating index capabilities within parseAndPop() function

/*include "maintenance.h"
#include <iostream>

using namespace std;

/* The maintenance class was desgined for the maintenance mode from the user interface.
 * This class will allow the user to either:
 * Add a path to a folder to be included within the index
 * Clear the current index completely
 * Parse the corpus and then populate the index
 */
/*Maintenance::Maintenance(){
    cout << "-----Welcome to the Maintenance Mode-----" << endl;
    cout << "In this mode, you can add opinions to the index, clear the index, "
            "or parse the corpus and populate the data." << endl;
    while(true){
        cout << endl;
        cout << "Add opinions to the index- 1" << endl;
        cout << "Clear the index- 2" << endl;
        cout << "Parse the corpus and populate the data- 3" << endl;
        cout << "Quit- 4" << endl;
        cin >> userChoice;
        if(userChoice == 1)
            addOpinions();
        if(userChoice == 2)
            clearIndex();
        if(userChoice == 3)
            parseAndPopulate();
        if(userChoice == 4)
            return;
    }
}

/* This function will accept a path for a folder, then add it to the parsing data
 */
/*void Maintenance::addOpinions(){
    cout << "Please enter the path to the folder containing new opinions: ";
    cin >> dirPath;
    //Need some way to include this new folder into the path for parsing
    cout << "Added the path" << endl;
}


/* This function will clear out the current index
 */
/*void Maintenance::clearIndex(){
    //Need some function to be called that will clear the index
    cout << "You have cleared the index." << endl;

}

/* This function will parse the corpus and then populate the index with the data
 */
/*void Maintenance::parseAndPopulate(){
    cout << "Parsing the corpus and populating the index" << endl;
    //Need some function to be called that will parse and populate

}*/
