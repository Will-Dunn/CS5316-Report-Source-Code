#ifndef TERM_H
#define TERM_H
#include <string>
#include <vector>

using namespace std;
class Term
{
private:


public:
    string term="";
    vector<string> doc;
    Term();
    Term(string);
    Term(const Term&);
    bool operator==(const Term&);
    Term& operator=(const Term&);
};

#endif // TERM_H
