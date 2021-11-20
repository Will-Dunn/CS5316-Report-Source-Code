#ifndef QUERY_H
#define QUERY_H
#include <string>
#include <iostream>
#include <vector>
#include <../../Sprint5/PA_Final/index.h>
#include "hashtable.h"
using namespace std;

class Query{
    private:
        string search;
        vector<string> vec;
        vector<string> andVec;
        vector<string> orVec;
        vector<string> notVec;
    public:
       Index<hashTable<string, Term>> ind;
        Query();
        Query(string s);
        void askForUser();
        vector<string> iterateQuery(string s, vector<string> v, bool firstWord);
        void printVec(vector<string> v);
        void printAllVecs();
        void checkBoolQueries(string s);
};

#endif // QUERRY_H
