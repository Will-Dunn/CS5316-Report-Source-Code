#include "term.h"
#include <string.h>
#include <vector>
#include <set>
#include <algorithm>
#include <../../Sprint5/PA_Final/documentparser.h>

Term::Term()
{
term="";
numoccurance=1;
numdoc=0;
}
Term::Term(string val)
{
term=val;
numoccurance=1;
numdoc=0;

}

Term::Term(const Term &val)
{   //Term temp=val;
    Term* r=nullptr;
    if(&val==r){
        term="";
        docs.clear();
         numoccurance=0;
         numdoc=0;
    }
    else{


term=val.term;
        docs=val.docs;
numoccurance=val.numoccurance;
numdoc=val.numdoc;
    }
}
Term& Term::operator+(const Term &val){
    set<document> res;
    //for()
    set<document>::iterator it;
    set<string>::iterator its;
    vector<float> tfs;
    //for(i)
     merge(val.docs.begin(), val.docs.end(), docs.begin(), docs.end(), inserter(res, res.begin()));
    //cout<<"merge term:" << val.term<<endl;


   // pair<set<string>,vector<float>> temp(res,tfs);
    //temp.first=res;


    docs=res;

    numdoc=docs.size();

    numoccurance+=val.numoccurance;
    numoccurance++;


    return *this;
}
Term& Term::operator=(const Term &val){
    term=val.term;
    docs=val.docs;
    numoccurance=val.numoccurance;
    numdoc=val.numdoc;
    return *this;
}
Term& Term::operator+=(const Term &val){


    set<document>::iterator it;


   set<document> res;
    merge(val.docs.begin(), val.docs.end(), docs.begin(), docs.end(), inserter(res, res.begin()));
    //cout<<"merge term:" << val.term<<endl;
    vector<float> tfs;
    //pair<set<string>,vector<float>> temp(res,tfs);
    docs=res;

    numdoc=docs.size();

    numoccurance+=val.numoccurance;
    //numoccurance++;


    return *this;

}
bool Term::operator<(  Term &val){

   //cout<<"t: "<<term<<" val: "<<val.term<<endl;
   if(term.compare(val.term)<0)
    {
        return true;
    }
   else
    return false;
}
bool Term::operator>(  Term &val){
   if(term.compare(val.term)>0)
    {
        return true;
    }
    return false;
}
string Term::print(){
    string b="";
    b+=term;
    set<document>::iterator it;
    for(it=docs.begin(); it != docs.end(); it++){
        document d=*it;
        b+=d.tostring();
        b+=",";
    }
    return b;
}
bool Term::operator==(Term &val){
    Term* p=nullptr;
    if(&val==p){
        return false;
    }
    if(term.compare(val.term)==0){
        return true;
    }
    return false;
}

bool Term::operator==(const Term &val){
    if(term.compare(val.term)==0){
        return true;
    }
    return false;
}
 std::ostream& operator<<(std::ostream& out,  const Term& val){

     out<<val.term<<","<<val.numoccurance<<endl;
     set<document>::iterator it;
     for(it=val.docs.begin(); it != val.docs.end(); it++){
         out<<*it<<",";
     }

    out<<endl;
    return out;
}
