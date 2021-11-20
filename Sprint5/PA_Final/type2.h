//William Dunn
#ifndef TYPE2_H
#define TYPE2_H
#include <string>
#include "term.h"
using namespace std;

class type2
{
public:
    int numoccurance;
    string term;
    type2();
    type2(const Term&);
    type2(string,int);
    type2(const type2&);
    type2& operator=(Term&);
    type2& operator=(const type2&) ;
    bool operator<(type2&);
    bool operator>(type2&);
    bool operator<( const type2&) const;
    bool operator>(const type2&) const;
    bool operator==(type2&);
    bool operator==(const type2&) const;
    type2& operator+=(type2&);
    friend std::ostream& operator<<(std::ostream&,  const type2&);
};

#endif // TYPE2_H
