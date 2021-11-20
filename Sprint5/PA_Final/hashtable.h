#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <bitset>
#include <fstream>
#include <list>
#include <list>
#include <iterator>
#include "document.h"
using namespace std;
/*William Dunn
 * Hash Table uses key value pairing to build a hashed array with linking conflict resolution
 * Based on code from Geeks for Geeks https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
 */
//const bool db=false;
//const bool db1=true;
template<typename K, typename V>
class hashNode{

private:
    K key;
    V val;
    //hashNode* next;

public:
    hashNode( K Key, V &Val){
       //cout<<"key: "<<Key<<endl;
        key=Key;
        val=Val;
    }
    K getKey(){
        return key;
    }
    void setKey(K k){
        key=k;
    }
    V& getVal(){
        return val;
    }
    void setVal(V k){
        val=k;
    }
    hashNode* getNext(){
        return next;
    }
    void setNext(hashNode N){
        next=N;
    }
};

template< typename K, typename V>
class hashTable{
private:
    list<hashNode<K,V>> **arr;

    int cap;
    hashNode<K,V> *dum;

public:
    int size;
    hashTable(){

        this->size=0;
        this->cap=10000;
        //cout<<"dog hash: "<<abs(hashcode("dog"))%cap<<endl;
        //cout<<abs(hashcode("dog"))%cap<<endl;
        arr= new list<hashNode<K,V>>*[cap];
        for(int i=0;i<cap;i++){
            arr[i]=nullptr;
        }
        //dum= new list<hashNode<K,V>>(-1,-1);
    }
    void insert(V val){
        string nam="class Term";
        //if the template is working with a Term this is how it should handle
        //duplicate values only
        //cout<<typeid(t->element).name()<<endl;
        if(nam.compare(typeid(val).name())==0){
        insert(val.term,val);}
    }
    int hashcode(K key){
        hash<K> a;
        return a(key);
    }
    void insert(K key,V val){
        char **test;
        test = new char*[60];

        //cout<< key<<endl;
        //cout<<typeid(V).name()<<endl;
       // cout<<"insert: "<<key<<endl;
        bool found=false;
        //hashNode<K,V> *temp= new hashNode<K,V>(key,val);
        hashNode<K,V> temp(key,val);
        int hashInd= abs(hashcode(key)) % cap;
        //cout<<hind<<endl;
        typename list<hashNode<K,V>>::iterator it;
        if(arr[hashInd] != nullptr){
        for(it=arr[hashInd]->begin(); it != arr[hashInd]->end(); it++){
            if(it->getKey()==key){
                string nam="class Term";
                //if the template is working with a Term this is how it should handle
                //duplicate values only

                if(nam.compare(typeid(val).name())==0){

               getval(key)+=temp.getVal();}

                found=true;
                break;


            }
        }
        if (found==false){

        arr[hashInd]->push_back(temp);
        }}
        else{
        list<hashNode<K,V>>* t= new  list<hashNode<K,V>>();

        t->push_back(temp);

        arr[hashInd]=t;
        size++;}

    }
    V* getvall(K key){
        int hind=abs(hashcode(key))%cap;

        typename list<hashNode<K,V>>::iterator it;
        if(arr[hind]!=nullptr){
        for(it=arr[hind]->begin();it !=arr[hind]->end();it++){
            if(it->getKey()==key){

                return &(it->getVal());
            }
        }}
        cout<<"foo"<<endl;
        V v;
        return nullptr;



    }
    V* find(K key){
       return getvall(key);
    }
    V& getval(K key){
        int hind=abs(hashcode(key))%cap;

        typename list<hashNode<K,V>>::iterator it;
        if(arr[hind]!=nullptr){
        for(it=arr[hind]->begin();it !=arr[hind]->end();it++){
            if(it->getKey()==key){

                return it->getVal();
            }
        }}
        cout<<"foo"<<endl;
        V v;
        return v;



    }
    void remove(K key){
        int hind=hashcode(key);
        typename list<hashNode<K,V>>::iterator it;
        for(it=arr[hind].begining;it !=arr[hind].end();it++){
            if(it->getKey()==key){
                break;
            }
        }
        if(it!=arr[hind].end()){
            arr[hind].erase(it);
        }
    }
    void print(){

        for(int i=0;i<size+1;i++){

            typename list<hashNode<K,V>>::iterator it;
            if(arr[i]!=nullptr){
            for(it=arr[i]->begin();it !=arr[i]->end();it++){
                //cout<<it->getVal()<<endl;
            }
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& out, const hashTable<K,V>& tab){
        out<<"size: "<<tab.size<<endl;
        for(int i=0;i<tab.size;i++){
            //cout<<i;
            typename list<hashNode<K,V>>::iterator it;
            if(tab.arr[i]!=nullptr){
                //if(arr[i]->begin()!=nullptr)
            for(it=tab.arr[i]->begin();it !=tab.arr[i]->end();it++){
                out<<it->getVal()<<endl;
            }
            }
        }
    }
    void print(ostream &os){

        for(int i=0;i<size;i++){
            //cout<<i;
            typename list<hashNode<K,V>>::iterator it;
            if(arr[i]!=nullptr){
                //if(arr[i]->begin()!=nullptr)
            for(it=arr[i]->begin();it !=arr[i]->end();it++){
                os<<it->getVal()<<endl;
            }
            }
        }
    }


};
#endif // HASHTABLE_H
