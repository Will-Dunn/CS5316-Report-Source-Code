#ifndef FIX_H
#define FIX_H
#include "document.h"
const document& operator-(const document& i, const document& v);
//bool operator<(const document& i, const document& v);
//bool operator>(const document& i, const document& v);
bool operator==(const document& i, const document& v);
class fix
{
public:
    fix();
};

#endif // FIX_H
