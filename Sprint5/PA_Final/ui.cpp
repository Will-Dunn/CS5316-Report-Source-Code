#include "ui.h"
#include "maintenance.h"
#include "interactive.h"
#include <iostream>

using namespace std;

UI::UI(){
    cout << "----------Welcome to the Search Engine----------" << endl;
    cout << "You can pick either Maintenance Mode or Interactive Mode" << endl;
    cout << "Maintenance Mode- 1\n"
            "Interactive Mode- 2\n" << endl;
    cout << "Your choice: ";
    cin >> userChoice;
    if(userChoice == 1)
        Maintenance<AVLTree<Term>> mM;
    if(userChoice == 2)
        Interactive iM;
}
/*
 * QA
 * at this point we will only have 2 variables the selected mode and the users input
 */