#include <../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/english_stem.h>
#include "stemmer.h"
#include <iostream>
#include <string>
//#include <bits/stdc++.h>

/* The Stemmer class allows for words to be provided and the stemmed lowercase version is returned.
 * Imported from the Oleander Stemming Library- https://github.com/OleanderSoftware/OleanderStemmingLibrary.git
 * String parameter gets converted to lowercase.
 * String parameter gets converted to wchar_t buffer.
 * Buffer gets passed through the stemmer library.
 * Buffer gets converted back to string.
 * String ids returned.
 */

Stemmer::Stemmer(){

}

string Stemmer::stem(string givenWord){
    //bool prd=;
    //bool prd1=;
    bool prd2=((int(*)(int))isspace);
    string copy = givenWord;
    transform(givenWord.begin(), givenWord.end(), givenWord.begin(), ::tolower);
    std::string ANSIWord(givenWord);
    wchar_t* UnicodeTextBuffer = new wchar_t[ANSIWord.length()+1];
    std::wmemset(UnicodeTextBuffer, 0, ANSIWord.length()+1);
    std::mbstowcs(UnicodeTextBuffer, ANSIWord.c_str(), ANSIWord.length());
    wstring stemmedWord = UnicodeTextBuffer;
    stemming::english_stem<> StemEnglish;
    StemEnglish(stemmedWord);

  //  cout << "Original text: " << copy << endl;
   // std::wcout << L"Stemmed text: " << stemmedWord.c_str() << std::endl;
    wstring temp(stemmedWord);
    string str(temp.begin(), temp.end());
    //will's code here

    str.erase(remove_if(str.begin(),str.end(),(int(*)(int))isdigit),str.end());//remove numbers
    str.erase(remove_if(str.begin(),str.end(),(int(*)(int))ispunct),str.end());//remove symbols

    return str;
}
