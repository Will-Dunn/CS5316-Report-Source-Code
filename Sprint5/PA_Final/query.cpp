//Elliot Boesch

#include "query.h"
#include "stemmer.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//STILL NEED TO DO
/* This class will return up to two vectors containing the queries
 * Needs to add specific vectors to the index
 * This could be done in the checkBoolQueries() function
 */



/* The Query class is desgined to ask the user for their query
 * that they would like to search within the documents.
 * This class will deal with the prefixes or trailing statements,
 * then add strings to their apporpriate vectors.
 * These vectors will then be passed to the index.
 */
Query::Query(){
    hashTable<string,Term> index;
    ind.readPeristantIndex(index);
    askForUser();
}
Query::Query(string s){
    checkBoolQueries(s);
}

/* A simple function desgined to ask the user for a query and then send the query
 * to the checkBoolQueries functions to be sorted in the proper vectors.
 */
void Query::askForUser(){
    cout << "Can prefix with AND/OR\nCan also use trailing NOT" << endl;
    cout << "Please enter you search querry: ";
    getline(cin, search);
    checkBoolQueries(search);
}


//Function to print all the elements in a vector
void Query::printVec(vector<string> v){
    for(unsigned i = 0;i < v.size(); i++){
        cout << v.at(i) << " ";
    }
    cout << endl;
}


//Function to print all four private vectors
void Query::printAllVecs(){
    cout << "-----Printing from the vector------" << endl;
    cout << "Regular Vector\n------------" << endl;
    printVec(vec);
    cout << endl;
    cout << "And Vector\n------------" << endl;
    printVec(andVec);
    cout << endl;
    cout << "Or Vector\n------------" << endl;
    printVec(orVec);
    cout << endl;
    cout << "Not Vector\n------------" << endl;
    printVec(notVec);
    cout << endl;
}



/* This function is desgined to iterate through the entire query that the user entered.
 * Then, depending if there are any prefixes or trailing words, each word will
 * be stemmed and then added to the appropriate vector.
 * The vector will then be returned.
 */
vector<string> Query::iterateQuery(string s, vector<string> v, bool firstWord){
    istringstream iterationString(s);
    Stemmer stem;
    string temp;
    string tempTemp;
    bool notFound=false;
    if(firstWord)
        iterationString >> temp;
    do{
        iterationString >> temp;
        if(temp == "NOT"){
           /* do{
                iterationString >> temp;
                temp = stem.stem(temp);
                if(!(temp == tempTemp)){
                    cout << temp << endl;
                    notVec.push_back(temp);
                }
                else
                    break;
                tempTemp = temp;
            }while(iterationString);
            break;*/
           iterationString >> temp;
           notFound=true;

        }
        temp = stem.stem(temp);
        if(!(temp == tempTemp)){
            cout << temp << endl;
            if(notFound)
                notVec.push_back(temp);
            else
                v.push_back(temp);
        }
        else
            break;
        tempTemp = temp;
    }while(iterationString);
    return v;
}



/* This function is desgined to deal with the prefixes.
 * Depending on wether or not a prefix was used in the query,
 * the iterateQuery function will be called with their respective vectors
 * being passed into it.
 */
void Query::checkBoolQueries(string s){

    istringstream itrString(s);
    string keyWord;

    itrString >> keyWord;
    if(keyWord == "AND"){
        andVec = iterateQuery(s, andVec, true);//Need to implement adding this vector to the index
        cout<<ind.ANDSearch(andVec,notVec)<<endl;
    }
    else if(keyWord == "OR"){
        orVec = iterateQuery(s, orVec, true);//Need to implement adding this vector to the index
        cout<< ind.OrSearch(orVec,notVec);
    }
    else if(keyWord != "AND" || keyWord != "OR"){
        vec = iterateQuery(s, vec, false);//Need to implement adding this vector to the index
        cout<<ind.basicSearch(vec.at(0),notVec)<<endl;
    }
    printAllVecs();
}
