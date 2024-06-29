#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"
// #include "Node.cpp"
// #include "dict.cpp"
// #include "search.cpp"

using namespace std;



class scoreMap{
public:

    vector<int> mods = {4 , 32 , 64 , 128 , 526 , 1024 , 8192} ;

    vector<vector<pair<Node , double>>> HT ;
    int siz_HT ;
    int cap_HT ;

    scoreMap() ;
    ~scoreMap() ;

    inline int hashVal(int &b_code, int &pg, int &para) ;

    void resizeHT() ;

    // inline bool compareNode(Node* &n1 , Node* &n2) ;

    void scorePlus(int &b_code, int &pg, int &para , double score) ;

    bool count(int &b_code, int &pg, int &para) ;

    double getScore(int &b_code, int &pg, int &para) ;

    inline bool empty() ;
} ;




class Linkedlist
{

public:
    Node *head;
    Node *tail;
    Linkedlist()
    {
        head = NULL;
        tail = NULL;
    }
    void insertnnode(Node *d);
};


class Nodeheap
{
public:
    double score;
    int para;
    int page;
    int book;
    // string sentence;
    // Node* next;

    // Default constructor
    Nodeheap()
    {
        score = 0.0;
        para = 0;
        page = 0;
        book = 0;
        // sentence="";
        // next = NULL;
    }
    Nodeheap(double s, int par, int pag, int bookcode)
    {
        score = s;
        para = par;
        page = pag;
        book = bookcode;
    }
};


//-----------------------
// good to go
//-----------------------
// this is unordered map to store all
// word's general frequency in csv file
// maps a string to long long
class general_count{
    public :
    vector<vector<pair<string , long long>>> HT ;
    int siz_HT ;
    int cap_HT ;

    general_count() ;
    ~general_count() ;
    long long power(long long a , long long b) ;
    long long hashVal(string &word) ;
    void push(string str , long long val) ;
    bool count(string &str) ;
    long long value(string &str) ;
} ;






class QNA_tool {

public:



    Dict dictionary ;
    general_count gen_cnt ;

    inline bool compareNode(Node& n1 , Node& n2) ;



    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string API_KEY, string question);
    // filename is the python file which will call ChatGPT API
    // root is the head of the linked list of paragraphs
    // k is the number of paragraphs (or the number of nodes in linked list)
    // API_KEY is the API key for ChatGPT
    // question is the question asked by the user

    // You can add attributes/helper functions here

public:

    void toLowerCase(string &s) ;
    /*
        . , - : ! " ' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @
    */
    bool seperator[127] ={false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, false, false, false, false, true, true, true, false, false, true, true, true, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};


    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
};