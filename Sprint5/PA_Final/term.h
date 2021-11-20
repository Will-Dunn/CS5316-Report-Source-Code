//William Dunn
#ifndef TERM_H
#define TERM_H
#include <string>
#include <vector>
#include <iostream>
#include "document.h"
#include <set>
#include "fix.h"
//#include <pair>
using namespace std;
class Term
{
private:


public:
    void tfs();
    int numoccurance;
    int numdoc;
    string term="";
    Term& operator+(const Term &val);
    string print();
    set<document> docs;
    Term();
    Term(string);
    Term(const Term&);
    bool operator<( Term&);
    bool operator>( Term&);
    //bool operator<( Term&);
    bool operator==(const Term&);
     bool operator==( Term&);
    Term& operator=(const Term&);
    Term& operator+=(const Term&);
    friend std::ostream& operator<<(std::ostream&,  const Term&);
};

#endif // TERM_H
