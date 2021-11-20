#ifndef INDEX_H
#define INDEX_H
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "fix.h"
#include "term.h"
#include "type2.h"
#include "documentparser.h"
#include "avltree.h"
#include "hashtable.h"
/*William Dunn
 * index the main place for storing data is responsible for reading and writing to persistant index
 * and handling searches
 */
using namespace std;
template<typename T>
class Index{
private:
    documentparser<T> dp;

public:
    vector<type2> forfinding50;


    string file;
    string statfile;
    T workingIndex;
    int numberopinions;

    Index(){
        file="persistantIndex.txt";
        statfile="stats.txt";
        //workingIndex
    }
    Index(string name, T &dataSet){
        file=name;
        workingIndex=dataSet;

    }
    void getstats(){
        fstream stat;
        stat.open("stats.txt");


    }
    T& makeDataSetScratch(T &data, const char* path){
        clear();
        data=dp.parsedataset(path);
        writeToPersistantavl(data);
        workingIndex=data;
        return workingIndex;

    }
    T& makeDataSet(T &data, const char* path1){

        readPeristantIndex(data);
        dp.parsedataset(path1,data);
        ofstream pers;
        pers.open("persistantIndex.txt",ofstream::out|ofstream::trunc);
        pers.close();

        writeToPersistantavl(data);
        workingIndex=data;
        return workingIndex;

    }
    void clear(){
        cout<<"clear"<<endl;
        ofstream pers;
        pers.open("persistantIndex.txt",ofstream::out|ofstream::trunc);//code from stackoverflow on how to clear a file
        pers.close();

        pers.open("stats.txt",ofstream::out|ofstream::trunc);//code from stackoverflow on how to clear a file
        pers<<"0 0 0";
        pers.close();


        //pers.clear();
        //pers.close();
    }
    void writeToPersistant(hashTable<string,Term>& dataset){
        //ofstream os();
        fstream pers;
           pers.open("persistantIndex.txt",fstream::app);

           pers<<dataset;


    }
    void writeToPersistantavl(AVLTree<Term>& dataset){
        ofstream os;

           os.open("persistantIndex.txt", ofstream::out| ofstream::app);

           dataset.print(os);


    }
    string ANDSearch(vector<string> vals,vector<string> no){
        Term* t1=workingIndex.find(vals.at(0));

        set<document> docs1;
        set<document> comp;
        if(t1==nullptr){return "No files";}
            docs1=t1->docs;

        comp=t1->docs;
        set<document>::iterator it;
        set<document>::iterator it2;

        cout<<vals.size()<<endl;
        for(int i=1;i<vals.size();i++){

            Term* Tn=workingIndex.find(vals.at(i));

            set<document> docsn=Tn->docs;
            if(Tn==nullptr){
                return "No files";
            }
            for(it=comp.begin();it!=comp.end();it++){
                bool found=false;
                for(it2=docsn.begin();it2!=docsn.end();it2++){
                    //cout<<it->doc<<" "<<it2->doc<<endl;
                    if(it->doc.compare(it2->doc)==0){
                        //cout<<"found"<<endl;
                        found=true;
                        break;
                    }

                }
                if(found==false){
                    comp.erase(it);

                }
            }



        }
        if(no.size()>0){
        return NotSearch(comp,no);}
        vector<document> strobe;
        for(it=comp.begin();it!=comp.end();it++){
            strobe.push_back(*it);
        }
        string ret;
        if(strobe.size()==0){
            return "No such files";
        }
        for(int i=0;i<strobe.size();i++){
            if(i<15){

            ret+=to_string(i);
            ret+=":     ";
            ret+=strobe.at(i).doc;
            ret+="\n----------------------------------------------------------------------\n";
            ret+=dp.first3hun(strobe.at(i).doc.c_str());
            ret+="\n\n";
}


        }
        ret+="\nenter the file number you would like to acsess:\n";
        cout<<ret<<endl;
        string tem;
        cin>>tem;
        int choic=stoi(tem);
        ret=strobe.at(choic).doc;
        ret+="\n----------------------------------------------------------------------\n";
        ret+=dp.parsefile(strobe.at(choic).doc.c_str());
        return ret;







    }
    string NotSearch(set<document> doccumentss,vector<string> vals){
        Term* t1=workingIndex.find(vals.at(0));

        set<document> docs1;
        set<document> comp;


        comp=doccumentss;
        set<document>::iterator it;
        set<document>::iterator it2;
        for(int i=0;i<vals.size();i++){
            Term* Tn=workingIndex.find(vals.at(i));
            set<document> docsn;
            if(Tn==nullptr){
                break;
            }
            for(it=comp.begin();it!=comp.end();it++){
                bool found=false;
                for(it2=docsn.begin();it2!=docsn.end();it2++){
                    if(it->doc.compare(it2->doc)==0){
                        found=true;
                        break;
                    }

                }
                if(found==true){
                    comp.erase(it);

                }
            }
        }
        vector<document> strobe;
        for(it=comp.begin();it!=comp.end();it++){
            strobe.push_back(*it);
        }
        if(strobe.size()==0){
            return "No such files";
        }
        string ret;
        for(int i=0;i<strobe.size();i++){
            if(i<15){

            ret+=to_string(i);
            ret+=":     ";
            ret+=strobe.at(i).doc;
            ret+="\n----------------------------------------------------------------------\n";
            ret+=dp.first3hun(strobe.at(i).doc.c_str());


            ret+="\n\n";}
        }
        ret+="\nenter the file number you would like to acsess:\n";
        cout<<ret<<endl;
        string tem;
        cin>>tem;
        int choic=stoi(tem);
        ret=strobe.at(choic).doc;
        ret+="\n----------------------------------------------------------------------\n";
        ret+=dp.parsefile(strobe.at(choic).doc.c_str());
        return ret;







    }
    string OrSearch(vector<string> vals, vector<string> no){
        Term* t1=workingIndex.find(vals.at(0));

        set<document> docs1;
        set<document> comp;
        if(t1==nullptr){return "No files";}
            docs1=t1->docs;

        comp=docs1;
        set<document>::iterator it;
         set<document>::iterator it2;
        for(int i=1;i<vals.size();i++){
            Term* Tn=workingIndex.find(vals.at(i));

            set<document> docsn;
            if(Tn==nullptr){
                return "No files";
            }

                for(it2=docsn.begin();it2!=docsn.end();it2++){
                    comp.insert(*it2);
                }



        }
        if(no.size()>0){
        return NotSearch(comp,no);}
        vector<document> strobe;
        for(it=comp.begin();it!=comp.end();it++){
            strobe.push_back(*it);
        }
        if(strobe.size()==0){
            return "No such files";
        }
        string ret;
        for(int i=0;i<strobe.size();i++){
            if(i<15){

            ret+=to_string(i);
            ret+=":    ";
            ret+=strobe.at(i).doc;
            ret+="\n----------------------------------------------------------------------\n";
            ret+=dp.first3hun(strobe.at(i).doc.c_str());



            ret+="\n\n";}
        }
        ret+="\nenter the file number you would like to acsess:\n";
        cout<<ret<<endl;
        string tem;
        cin>>tem;
        int choic=stoi(tem);
        ret=strobe.at(choic).doc;
        ret+="\n----------------------------------------------------------------------\n";
        ret+=dp.parsefile(strobe.at(choic).doc.c_str());

        return ret;







    }

    string basicSearch(string term, vector<string> no){

        Term* t1=workingIndex.find(term);
        if(t1==nullptr){
            return "No Files Found";
        }
        set<document> docs1=t1->docs;
        //return NotSearch(docs1,no);
        if(no.size()>0){
        return NotSearch(docs1,no);}
        vector<document> alldocs;
         vector<float> alldocss;
        documentparser<AVLTree<Term>> dp;
        set<document>::iterator it3;
        for(it3=docs1.begin();it3!=docs1.end();it3++){


                alldocs.push_back(*it3);

            }
        if(alldocs.size()==0){
            return "NONE";
        }
        for(int i=0;i<alldocs.size()-1;i++){
            document b=alldocs.at(i);
            for(int j=1;i<alldocs.size();i++){
                if(alldocs.at(j)<b){
                document t=alldocs.at(j);
                alldocs.at(j)=alldocs.at(i);
                alldocs.at(i)=t;
                }


            }

        }

        string ret="Term : "+term+" is found "+to_string(t1->numoccurance)+" times in files:\n";


        for(int i=0;i<15;i++){
            if(i>alldocs.size()-1){
                break;
            }
            ret+=to_string(i);
            ret+=":    ";
            ret+=alldocs.at(i).doc;
            ret+="\n----------------------------------------------------------------------\n";
            ret+=dp.first3hun(alldocs.at(i).doc.c_str());
            ret+="\n\n";
        }
         ret+="\nenter the file number you would like to acsess:\n";
         cout<<ret<<endl;
         string tem;
         cin>>tem;
         int choice=stoi(tem);
         ret=alldocs.at(choice).doc;
         ret+="\n----------------------------------------------------------------------\n";
         ret+=dp.parsefile(alldocs.at(choice).doc.c_str());
        return ret;

    }


    string NOTSearch(string term1,string term2){

        Term* t1=workingIndex.find(term1);
        if(t1==nullptr){
            return "no files found";
        }

        set<document> docs1=t1->docs;
        Term* t2=workingIndex.find(term2);
        Term temp;
        if(t2==nullptr){
            t2=&temp;
        }
        set<document> docs2=t2->docs;
        set<document>::iterator it1;
        set<document>::iterator it2;

        vector<document> alldocs;

        for(it1=docs1.begin();it1!=docs1.end();it1++){
            bool found=false;
            document d11=*it1;
            for(it2=docs2.begin();it2!=docs2.end();it2++){

                if(d11==*it2){

                    alldocs.push_back(*it1);

                break;}
            }

        }

        for(int i=0;i<alldocs.size()-1;i++){

             document b=alldocs.at(i);
            for(int j=1;i<alldocs.size();i++){
                if(alldocs.at(j)<b){
                document t=alldocs.at(j);
                alldocs.at(j)=alldocs.at(i);
                alldocs.at(i)=t;
                }


            }

        }


        vector<pair<string,float>>::iterator it3;

        string ret="Term 1: "+term1+" and Term 2: "+term2+" are found in files:\n";


        for(int i=0;i<15;i++){
            ret+=alldocs.at(i).doc;
            ret+=" occurs: ";
            ret+=alldocs.at(i).tf;

            ret+=" ";
        }

        ret+="\nthat is all\n";
        return ret;
    }
    //get top 50 terms
    string top50(){
        string ret="";
        sort(forfinding50.begin(),forfinding50.end());
       for(int i=0;i<50;i++){

            ret+=to_string(i+1);
            ret+=": ";
            ret+=forfinding50.at(forfinding50.size()-(1+i)).term;
            ret+="\n";
            //forfinding50.findMax()->numoccurance=-1;

        }
       return ret;
       }

    void readPeristantIndex(T& dataset){
        //cout<<typeid(workingIndex).name()<<endl;
        fstream os(file.c_str());
        string input;
        getline(os,input,',');
        while(!os.eof()){
            //cout<<"next term "<<input<<endl;
            Term temp(input);
            getline(os,input);
            temp.numoccurance=stoi(input);
            type2 t50i(temp);
            forfinding50.push_back(t50i);
            getline(os,input);
            //if(input.compare("")==0){break;}

            //cout<<"files"<<endl;
           // cout<<input<<endl;
            stringstream fileList(input);

            getline(fileList, input, ',');
            while(!fileList.eof()){
                string fName=input;
                getline(fileList, input, ',');

                float tf;
                if(isdigit(input[0]))
                       tf =stof(input);
            document doc(fName, tf);
            temp.docs.insert(doc);
            getline(fileList, input, ',');}
           //cout<<"end of docs"<<endl;
            getline(os,input,',');
            workingIndex.insert(temp);


    }
        //cout<<"read"<<endl;
    dataset=workingIndex;

    //dataset.print(cout);
    //return workingIndex;}
}



};
#endif // INDEX_H
