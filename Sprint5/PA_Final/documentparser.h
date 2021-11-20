#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include <../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/english_stem.h>
#include <string>
#include <../../lib/dirent.h>
#include <sstream>
#include <vector>
#include "fix.h"
#include "type2.h"
#include <../../lib/rapidjson-master/include/rapidjson/document.h>
#include <../../lib/rapidjson-master/include/rapidjson/writer.h>
#include <../../lib/rapidjson-master/include/rapidjson/istreamwrapper.h>
#include <../../lib/rapidjson-master/include/rapidjson/ostreamwrapper.h>
#include <../../lib/rapidjson-master/include/rapidjson/stringbuffer.h>
#include "term.h"
#include "stemmer.h"
#include "avltree.h"

using namespace rapidjson;
using namespace std;

/*William Dunn
 * This class is responsible for processing and parsing a file of json files and converiting them to Terms
 */
template<typename T>
class documentparser {
private:
    int numNodes;
public:
    AVLTree<string> sw;
    AVLTree<type2> forfinding50;
    string pa;
    //bool r;
    int numbfiles = 5000;

    documentparser() {
        string stopwords[156] = {"", " ", "u.", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
                                 "o", "p", "q", "r", "s", "t", "v", "w", "x", "y", "z", "ed", "i", "me", "my", "myself",
                                 "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves",
                                 "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself",
                                 "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom",
                                 "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been",
                                 "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an",
                                 "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by",
                                 "for", "with", "about", "against", "between", "into", "through", "during", "before",
                                 "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off",
                                 "over", "under", "again", "further", "then", "once", "here", "there", "when", "where",
                                 "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some",
                                 "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s",
                                 "t", "can", "will", "just", "don", "should", "now"};

        for (int i = 0; i < 156; i++) {
            sw.insert(stopwords[i]);
        }
    }

    bool contains(vector<string> Terms, string val) {
        sort(Terms.begin(), Terms.end());
        vector<string>::iterator it;
        it = find(Terms.begin(), Terms.end(), val);
        string a = *it;
        if (a.compare(val) == 0) {
            return true;

        }
        return false;

    }

    Term *contains(vector<Term> Terms, Term val) {
        sort(Terms.begin(), Terms.end());
        vector<Term>::iterator it;
        for (int i = 0; i < Terms.size(); i++) {
            if (Terms.at(i) == val)
                return &Terms.at(i);
        }
        return nullptr;


    }

    string parsefile(string name) {
        fstream cleantxt;
        // cout<<name<<endl;
        //cleantxt.open("cleantxt.txt");
        ifstream ifs;
        ifs.open(name.c_str(), ifstream::in);
        if (!ifs.is_open()) {
            return "";
        }
        if (name.compare(pa + "/.") == 0 || name.compare(pa + "/..") == 0) { return ""; }//to diagram
        //cout<<name<<endl;
        IStreamWrapper isw(ifs);
        Document d;
        d.ParseStream(isw);
        //printf("test = %s/")
        //string dateC=d["date_created"].GetString();
        string test = d["html_with_citations"].GetString();

        int a = 0;
        int b = 0;

        for (a = 0; a < test.size(); a++) {
            if (test[a] == '<') {
                for (b = a; b < test.length(); b++) {
                    if (test[b] == '>') {
                        test.erase(test.begin()+a, test.begin()+b);
                        break;
                    }
                }
            }

        }
        return test;
    }

    vector<string> getwords(const char *path) {
        string inp;
        Stemmer stem;
        stringstream fike(parsefile(path));

        fike >> inp;

        vector<string> words;
        while (!fike.eof()) {

            inp = stem.stem(inp);//stem word
            if (!sw.contains(inp)) {
                words.push_back(inp);
            }
        }

        return words;
    }

    vector<string> listfiles(string path) {

        DIR *dir;
        dirent *pdir;
        vector<string> files;
        dir = opendir(path.c_str());

        while (pdir = readdir(dir)) {
            if (pdir->d_name[0] != '.') {

                files.push_back(path + "/" + pdir->d_name);
            }

        }

        return files;
    }

    void progBar(int num) {
        for (int i = 0; i < num; i++) {
            cout << "|";
        }
    }

    void setNodes(int num) {
        numNodes = num;
    }

    int getNodes() {
        return numNodes;
    }

    float tfidf(string term, const char *path) {
        string inp;
        Stemmer stem;
        stringstream fike(parsefile(path));

        fike >> inp;

        vector<string> words;
        while (!fike.eof()) {

            inp = stem.stem(inp);//stem word
            if (!sw.contains(inp)) {
                words.push_back(inp);
            }
        }

        int Count = count(words.begin(), words.end(), term);
        float tf = (float) Count / (float) words.size();//calculate tf/idf
        return tf;

    }

    string top50(const char *path) {
        string ret = "";
        for (int i = 0; i < 50; i++) {
            if (forfinding50.findMax() == nullptr) {
                break;
            } else {
                ret += to_string(i + 1);
                ret += ": ";
                ret += forfinding50.findMax()->term;
                ret += "\n";
                forfinding50.findMax() ;

            }
        }
    }

    string first3hun(const char *path) {
        string inp;
        string ret = "";

        stringstream fileText(parsefile(path));
        for (int i = 0; i < 300; i++) {
            fileText >> inp;
            ret += inp;
            ret += " ";
        }
        return ret;
    }

    int numberOfFilesBeingParsed(const char *path) {
        return 0;
    }

    //void stats()
    T parsedataset(const char *path) {
        //int xas=numberOfFilesBeingParsed(path);
        fstream st;
        st.open("stats.txt");
        T terms;
        //Term a("judiciari");

        //terms.insert(a);
        vector<Term> ter;
        int t = 0;
        //terms.file.open("log.txt");
        vector<string> files = listfiles(path);//gets all the file  names
        Stemmer stem;

        int q = 0;
        int q1 = 0;
        int q2 = 0;
        //int samplesize=5000;
        if (numbfiles > files.size())
            numbfiles = files.size();
        string ree;
        string reee;
        string reeee;
        st >> ree;
        st >> reee;
        st >> reeee;
        q = stoi(ree) + numbfiles;
        q1 = stoi(reee);
        q1 = stoi(reeee);
        ree = to_string(q);
        st.close();
        //st.open()
        st.open("stats.txt");
        st << ree;
        cout << ree << endl;
        //st<<"buts";

        float tf = .0001;
        //vector<string> wordssingletime;
        //vector<string> wordsall;
        cout<<numbfiles<<endl;
        for (int i = 0; i < numbfiles; i++) {//loop through all files
            AVLTree<string> rw;
            //cout<<i<<endl;
            //cout<<parsefile(files.at(i))<<endl;

            //vector<string> words = getwords(files.at(i));
            string inp;

            stringstream fike(parsefile(files.at(i)));
            //stringstream fikesub(parsefile(files.at(i)));
            fike >> inp;
            //cout<<inp;
            vector<string> wordsinf;
            vector<string> words;
            while (!fike.eof()) {

                inp = stem.stem(inp);//stem word
                //cout<<inp;
                if (!sw.contains(inp)) {
                    wordsinf.push_back(inp);
                    if (!rw.contains(inp)) {
                        //cout<<"insert"<<endl;
                        words.push_back(inp);
                        rw.insert(inp);
                    }

                }
                fike >> inp;

            }
            //cout<<words.size()<<endl;
            for (int zoo = 0; zoo < words.size(); zoo++) {
                int c = count(wordsinf.begin(), wordsinf.end(), words.at(zoo));
                type2 temporary(wordsinf.at(zoo), c);
                forfinding50.insert(temporary);
                float wf = (float) c / float(wordsinf.size());
                document d(files.at(i), wf);
                Term temp(wordsinf.at(zoo));
                temp.docs.insert(d);
                //cout<<temp.docs.size()<<endl;
                terms.insert(temp);
            }





        }
        //setNodes(q);

        //terms.printTree();
        st << " " << terms.size();
        st << " " << terms.size() / numbfiles;
        st.close();
        return terms;
    }

    void parsedataset(const char *path, T &datas) {

        T terms = datas;
        //Term a("judiciari");

        //terms.insert(a);
        vector<Term> ter;
        int t = 0;
        //terms.file.open("log.txt");
        vector<string> files = listfiles(path);//gets all the file  names
        Stemmer stem;

        int q = 0;
        //int samplesize=5000;
        if (numbfiles > files.size())
            numbfiles = files.size();

        float tf = .0001;
        //vector<string> wordssingletime;
        //vector<string> wordsall;
        //cout<<numbfiles<<endl;
        for (int i = 0; i < numbfiles; i++) {//loop through all files
            AVLTree<string> rw;
            //cout<<i<<endl;
            //cout<<parsefile(files.at(i))<<endl;

            //vector<string> words = getwords(files.at(i));
            string inp;

            stringstream fike(parsefile(files.at(i)));
            //stringstream fikesub(parsefile(files.at(i)));
            fike >> inp;
            vector<string> wordsinf;
            vector<string> words;
            while (!fike.eof()) {

                inp = stem.stem(inp);//stem word
                if (!sw.contains(inp)) {
                    wordsinf.push_back(inp);
                    if (!rw.contains(inp)) {
                        words.push_back(inp);
                        rw.insert(inp);
                    }

                }
                fike >> inp;

            }
            for (int zoo = 0; zoo < words.size(); zoo++) {
                int c = count(wordsinf.begin(), wordsinf.end(), words.at(zoo));
                type2 temporary(wordsinf.at(zoo), c);
                forfinding50.insert(temporary);
                float wf = (float) c / float(wordsinf.size());
                document d(files.at(i), wf);
                Term temp(wordsinf.at(zoo));
                temp.docs.insert(d);
                //<<temp.docs.size()<<endl;
                terms.insert(temp);
            }





        }
        //setNodes(q);

        //terms.printTree();
        //return terms;
        datas = terms;
    }

};

#endif // DOCUMENTPARSER_H
