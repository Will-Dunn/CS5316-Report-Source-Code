#include "type2.h"
#include "term.h"
type2::type2()
{

}
type2::type2(const Term& val){
    numoccurance=val.numoccurance;
    term=val.term;

}
type2::type2(string T,int o){
    numoccurance=o;
    term=T;

}
type2::type2(const type2& val){
    numoccurance=val.numoccurance;
    term=val.term;
}
type2& type2::operator=(Term& val){
    numoccurance=val.numoccurance;
    term=val.term;
    return *this;
}
type2& type2::operator=(const type2& val) {
    numoccurance=val.numoccurance;
    term=val.term;
    return *this;}
bool type2::operator<(type2& val){
    if(numoccurance<val.numoccurance)
        return true;
    return false;
}
bool type2::operator>(type2& val){
    if(numoccurance>val.numoccurance)
        return true;
    return false;
}
bool type2::operator<( const type2& val) const{
    if(numoccurance<val.numoccurance)
        return true;
    return false;
}
bool type2::operator>(const type2& val) const{
    if(numoccurance>val.numoccurance)
        return true;
    return false;
}
bool type2::operator==(type2& val){
    if(term.compare(val.term)==0)
        return true;
    return false;
}
bool type2::operator==(const type2& val)const {
    if(term.compare(val.term)==0)
        return true;
    return false;
}
type2& type2::operator+=(type2& val){
    numoccurance+=val.numoccurance;
    return *this;
}
std::ostream& operator<<(std::ostream& out,  const type2& val){

    out<<val.term<<" occurs "<<val.numoccurance<<" times";


   out<<endl;
   return out;
}
