// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
#include "Node.h"
// #include "Node.cpp"
using namespace std;






// -----------------------------------------------------------------------
// MAP CLASS IMPLIMENTATION
// this class maps a node/paragraph to an integer

class myMap {
public:
    // mods is the array of possible sizes of HT
    // we choose powers of 2 because (i % pow_of_2)
    // is a faster operation than any other modulo operation
    // because of bit operation auto modification by the compiler
    // (if the compiler supports)
    vector<int> mods = {16 , 32 , 64 , 128 , 526 , 1024 , 8192 , 32768 , 131072 , 524288} ; // TO BE UPDATED

    vector<vector<pair<Node,long long>>> HT ;
    // 1st index of vector is the hash val of key
    // vector inside that location stores all
    // key val pairs corresponding to that hash val

    int siz_HT ;
    int cap_HT ;

    myMap() ;
    ~myMap() ;

    inline int hashVal(Node i) ;

    // when HT is 70% filled we will use
    // this function to resize HT
    // if increase = 1 then HT size increase
    // else decrease
    void resizeHT(bool increase) ;

    // compare equalithy of 2 Nodes
    inline bool compareNode(Node& n1 , Node& n2) ;

    // push this key val pair in HT
    // if key already exists then update
    // the val
    void push(Node key , long long val) ;

    // delete that key from HT
    void erase(Node key) ;

    // is present key?
    bool count(Node &key) ;

    // if key exists in HT then returns it's val
    long long value(Node &key) ;

    inline bool empty() ;
};




class Dict {
public:
    // You can add attributes/helper functions here

    // source http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
    // possible sizes of hash table
    vector<long long> mods = {1009 , 10007 , 100003 , 1000003 , 9999889 , 10009079 , 100000007, 1000000070 , 10000000700} ;
    
    vector<vector<pair<string,myMap>>> HT ;
    long long sizeHT ;
    long long capHT ;

    /*
        . , - : ! " ' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @
    */
    bool seperator[127] ={false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, false, false, false, false, true, true, true, false, false, true, true, true, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

    // function to calculate power
    long long power(long long a , long long b) ;

    // hash val calculator
    long long hashVal(string &word) ;

    // any case to lower case convertor
    void toLowerCase(string &s) ;

    // insert word in hash table
    void insertInHT(string word , Node n) ;

    void resizeHT() ;


    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    myMap get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
