#include "fix.h"
#include "document.h"
//fix for some messed up opperators
fix::fix()
{

}
const document& operator-(const document& i, const document& v){
    return i;
}
bool operator==(const document& i, const document& v) {
    if(i.doc.compare(v.doc)==0){
        return true;
    }

    if(i.tf==v.tf){
        return true;
    }
    return false;

}
bool operator<(const document& i, const document& v) {
    if(i.doc.compare(v.doc)<0){
        return true;
    }
    if(i.doc.compare(v.doc)>0){
        return false;
    }
    if(i.tf<v.tf){
        return true;
    }
    return false;

}
bool operator>(const document& i, const document& v){
    if(i.doc.compare(v.doc)>0){
        return true;
    }
    if(i.doc.compare(v.doc)<0){
        return false;
    }
    if(i.tf>v.tf){
        return true;
    }
    return false;

}
