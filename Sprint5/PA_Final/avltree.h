#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include "fix.h"
#include <fstream>
/*Elliot Boesch
 * with modifications from William Dunn
 * Is an AVL Tree
 * BASED ON CODE FROM CLASS
 */
using namespace std;
const bool db = false;
const bool db1 = true;

template<typename T>
class AVLTree {
private:

    class Node {
    public:

        T value;
        Node *left;
        Node *right;
        int height;

        Node(const T &theElement, Node *lt, Node *rt, int h = 0) : value(theElement), left(lt), right(rt),
                                                                   height(h) {}
    };

    Node *findMin(Node *t) const {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    Node *findMax(Node *t) const {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    bool contains(const T &x, Node *t) const {
        if (t == nullptr)
            return false;
        else if (x < t->value)
            return contains(x, t->left);
        else if (t->value < x)
            return contains(x, t->right);
        else
            return true;
    }

    void makeEmpty(Node *&t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    int height(Node *t) const {
        return t == nullptr ? -1 : t->height;
    }

    //int Node::max(int lhs, int rhs) const {
      //  return lhs > rhs ? lhs : rhs;
    //}

    int countnodes(Node *start) {

        int count = 1;

        if (start->left != nullptr)
            count += countnodes(start->left);
        if (start->right != nullptr)
            count += countnodes(start->right);


        return count;

    }

    int numberofNodes(Node *Root) {
        int count = 0;
        if (Root != nullptr) {
            count += countnodes(Root);

        }
        return count;
        //countnodes()
    }

    void insert(T &x, Node *&t) {
        //file<<"\n\n"<<endl;
        //file<<x<<endl;
        if (t == nullptr) {
            t = new Node(x, nullptr, nullptr);
            numnodes++;
        } else if (x < t->value) {

            if (db1) {//I belive this is just debugging and we might wanna take it out
                if (t->left != nullptr) {
                    if (t->left->left != nullptr) {
                        if (t->left->left->value == t->value) {
                            t->left->left = nullptr;
                        }
                    }
                    if (t->left->right != nullptr) {
                        if (t->left->right->value == t->value) {
                            t->left->right = nullptr;
                        }
                    }
                }
                if (t->right != nullptr) {
                    if (t->right->left != nullptr) {
                        if (t->right->left->value == t->value) {
                            t->right->left = nullptr;
                        }
                    }
                    if (t->right->right != nullptr) {
                        if (t->right->right->value == t->value) {
                            t->right->right = nullptr;
                        }
                    }
                }
            }


            if (t->left != nullptr)

                if (t->value == t->left->value) {
                    //cout<<"loop"<<endl;
                    t->left == nullptr;
                }
            insert(x, t->left);
            //cout<<"past"<<endl;
            if (height(t->left) - height(t->right) == 2) {
                if (x < t->left->value)
                    rotateWithLeftChild(t);
                else {
                    doubleWithLeftChild(t);
                }
            }
        } else if (x > t->value) {
            if (db) {
                if (t->left != nullptr && t->right != nullptr) {
                    cout << x << " is Greater than " << t->value << "\nright element is: " << t->right->value
                         << " left element is: " << t->left->value << endl;
                }
            }//todo:determine if this does anything
            if (db1) {
                if (t->left != nullptr) {
                    if (t->left->left != nullptr) {
                        if (t->left->left->value == t->value) {
                            t->left->left = nullptr;
                        }
                    }
                    if (t->left->right != nullptr) {
                        if (t->left->right->value == t->value) {
                            t->left->right = nullptr;
                        }
                    }
                }
                if (t->right != nullptr) {
                    if (t->right->left != nullptr) {
                        if (t->right->left->value == t->value) {
                            t->right->left = nullptr;
                        }
                    }
                    if (t->right->right != nullptr) {
                        if (t->right->right->value == t->value) {
                            t->right->right = nullptr;
                        }
                    }
                }
            }
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2) {
                if (t->right->value < x)
                    rotateWithRightChild(t);
                else {
                    doubleWithRightChild(t);
                }
            }
        } else {//cout<<typeid(t->value).name()<<endl;
            string nam = "class Term";
            string nam1 = "class type2";
            //if the template is working with a Term this is how it should handle
            //duplicate values only
            //type2 a

            if (nam.compare(typeid(t->value).name()) == 0) {
                t->value += x;
                //cout<<"run"<<endl;
            } else if (nam1.compare(typeid(t->value).name()) == 0) {
                if (x == t->value)
                    t->value += x;
            }
            //cout<<"added duplicate value"<<endl;}
            // cout<<"dupe"<<endl;
        }
        t->height = max(height(t->left), height(t->right)) + 1;
       // printTree();
    }

    void rotateWithLeftChild(Node *&k2) {
        if (db) { cout << "rotate left child" << endl; }
        Node *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(Node *&k1) {
        if (db) { cout << "rotate right child" << endl; }
        Node *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(Node *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(Node *&k1) {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    void printTree(Node *t) const {
        if (t != nullptr) {
            printTree(t->left);
            cout << "a     :" << t->value << endl;
            printTree(t->right);
        }
    }

    void printTree(Node *t, ostream &os) const {
        // fstream idf;
        //idf.open(file);
        if (t != nullptr) {
            printTree(t->left, os);
            os << t->value;
            printTree(t->right, os);
        }
        //idf.close();
    }

    string printTree(Node *t, string b) const {
        // fstream idf;
        //idf.open(file);
        if (t != nullptr) {
            printTree(t->left, b);
            b += t->value.print();
            b += ",";
            printTree(t->right, b);
        }
        return b;

        //idf.close();
    }

    Node *clone(Node *t) const {
        if (t == nullptr)
            return nullptr;
        else {
            return new Node(t->value, clone(t->left), clone(t->right), t->height);
        }
    }

    void printlevord(Node *root) {
        int h = root->height;
        for (int i = 1; i <= h; i++) {
            printlevel(root, i);
            cout << endl;
        }
    }

    void printlevel(Node *node, int level) {
        if (node == nullptr) {
            return;
        }
        if (level == 1) {
            cout << node->value << " ";
        } else if (level > 1) {
            printlevel(node->left, level - 1);
            printlevel(node->right, level - 1);
        }
    }

    T &findval(T &val, Node *start) {
        if (start == nullptr) {
            T va(""); //if not there return NULL
            cout << "No such Term" << endl;
            return va;
        }
        if (val == start->value) {
            cout << start->value << endl;
            return val;
        } else if (val < start->value)
            return findval(val, start->left);
        else if (val > start->value)
            return findval(val, start->right);
    }

public:
    Node* root;
    fstream file;

    AVLTree() : root(nullptr), numnodes(0) {}

    AVLTree(const AVLTree &rhs) : root(nullptr), numnodes(rhs.numnodes) {
        *this = rhs;
    }

    ~AVLTree() {
        //root=nullptr;
        makeEmpty();
    }

    int numberofNodes() {
        return numberofNodes(root);
    }

    int size() {
        return numberofNodes();
    }

    T findval(T &val) {

        return findval(val, root);

    }

    const T &findMin() const {
        if (isEmpty())
            cout << "The tree is empty...findMin()" << endl;
        return findMin(root)->value;
    }

    /*  const T& findMax() const{
          if(isEmpty())
              cout << "The tree is empty...findMax()" << endl;
          return findMax(root)->element;
      }*/
    T *findMax() const {
        if (isEmpty())
            cout << "The tree is empty...findMax()" << endl;
        return &findMax(root)->value;
    }

    bool contains(const T &x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void insert(T &x) {

        insert(x, root);
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    string printit() {
        return printTree(root, "");
    }

    void printTree() const {
        cout<<"tot"<<endl;
        if (isEmpty())
            cout << "Empty Tree" << endl;
        else {
            printTree(root);
        }
    }

    void print(ostream &os) const {
        if (isEmpty())
            cout << "Empty Tree" << endl;
        else {
            printTree(root, os);
        }
    }

    const AVLTree &operator=(const AVLTree &rhs) {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    int numnodes;

    friend std::ostream &operator<<(std::ostream &out, const AVLTree<T> &t) {

        AVLTree<T> t1 = t;
        //cout<<t1.printit()<<endl;
        out << t1.printit() << endl;
        //operator<<(out,t->right);

        return out;
    }



};


#endif // AVLTREE_H
