#include "document.h"
#include <iostream>
document::document()
{
    doc="";
    tf=0;
}
document::document(string d,float f)
{
    doc=d;
    tf=f;
}
document::document(const document& v){
     doc=v.doc;
     tf=v.tf;
     //return *this;
 }
std::ostream& operator<<(std::ostream& out,  const document& val){
    string a=val.doc;
   // std::cout<<a<<std::endl;
    a+=",";
    a+=to_string(val.tf);

    out<<a;
    return out;
}
bool document::operator<( document& v)const{
    if(tf<v.tf){
        return true;
    }
    return false;

}
bool document::operator>( document& v)const{
    if(tf>v.tf){
        return true;
    }
    return false;

}
bool document::operator<( const document& v)const{
    if(tf<v.tf){
        return true;
    }
    return false;

}

bool document::operator>( const document& v)const{
    if(tf>v.tf){
        return true;
    }
    return false;

}
//bool operator<( Term&);
bool document::operator==( const document& v){
    if(tf==v.tf){
        return true;
    }
    return false;

}


string document::tostring(){
    string a=doc;
    //std::cout<<a<<std::endl;
    a+=",";
    a+=to_string(tf);
    return a;
}
 bool document::operator==( document& v){
     if(tf==v.tf){
         return true;
     }
     return false;

 }
 const document& document::operator-(const document& v){
     //docv.doc;
     tf-=v.tf;
     return *this;
 }
 const document& document::operator=(const document& v){
     doc=v.doc;
     tf=v.tf;
     return *this;
 }
