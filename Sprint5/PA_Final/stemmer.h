#ifndef STEMMER_H
#define STEMMER_H
#include <iostream>
#include <string>
#include "fix.h"

using namespace std;

//See stemmer.cpp for more info.

class Stemmer{
public:
    Stemmer();
    string stem(string givenWord);

};

#endif // STEMMER_H
