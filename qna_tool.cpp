

/*                        Theory :
______________________________________________________________

    ==========================================================
                            PART 1 :
    ==========================================================

    We will use dict implimentation (modified) of A6 in A7
    we store complete doc in a Dict class
    modified dict class will store word count paragraph wise

    vector<vector <pair <string,int> > >    was old hash table in Dict

    new will be     vector<vector <pair <string , map<int,int> > > >
        key of map -> para number
        value of map -> count
    we will do separate implimentation of map class whose hash table size
    will be smaller and we will resize on 7% filling

    Time complexity analysis for part 1 :

    only insertion of book into the system will take O(n) time

    -> for searching freq of each word its is approx O(1) time
    -> so finding score of all para will take O(length of sentence * no. of sentence)

    Finding top k para we use min heap methode that takes O(n + k*logn) time
    n = number of paragraphs


    ==========================================================
                            PART 2 :
    ==========================================================

    ###############################################################
    MAY BE OPTIMISED USING THIS METHODE
    NEEDS VERIFICATION
    ###############################################################
    While declaring QNA_tool class object
    we will specialy store some most frequent words from Hash table
    while storing the book, by once complete itrating the hash table
    -----------------
    we will find most optimal value of k by trial analysis
    over various questions and promt output given by the model
    -----------------
    BAKI AGE KA KAISE KRNA WO NHI PATA
    KI KAISE YE PARAGRAPHS GPT KO SEND KRNA FIR
    USKA JO OUTPUT AYEGA USKO PRINT KAISE KRNA

    ALL THE BEST

*/

// #include<bits/stdc++.h>
// #include<algorithm>
#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

scoreMap::scoreMap()
{
    siz_HT = 0;
    cap_HT = mods.front();
    HT = vector<vector<pair<Node, double>>>(cap_HT, vector<pair<Node, double>>(0));
}

scoreMap::~scoreMap()
{
    // nothing to delete specially as everything allocated on stack
}

inline int scoreMap::hashVal(int &b_code, int &pg, int &para)
{
    return (100 * b_code + 10 * pg + para) % cap_HT;
}

void scoreMap::resizeHT()
{
    if (cap_HT >= mods.back())
        return;
    int newCap = 0;
    int m; // this m points the index of vector mods ;
    for (m = 0; m < mods.size(); m++)
        if (mods[m] == cap_HT)
            break;
    newCap = mods[m + 1];

    vector<vector<pair<Node, double>>> newHT = vector<vector<pair<Node, double>>>(newCap, vector<pair<Node, double>>(0));

    // travel old hash table, rehash all elements,
    // put them in new hash table
    for (vector<pair<Node, double>> &v : HT)
    {
        for (pair<Node, double> &p : v)
        {
            int newHashVal = (100 * p.first.book_code + 10 * p.first.page + p.first.paragraph) % newCap;
            newHT[newHashVal].push_back({p.first, p.second});
        }
    }

    cap_HT = newCap;
    HT = newHT;
    // cout << cap_HT << endl ;
    // older Hash table was declared on stack (static declaration)
    // so no need to delete old Hash table
}

void scoreMap::scorePlus(int &b_code, int &pg, int &para, double scoreAdd)
{
    if (cap_HT * 10 < siz_HT * 7)
        resizeHT();

    int h = hashVal(b_code, pg, para);

    int l = HT[h].size();
    int i = 0;
    for (; i < l; i++)
    {
        if (HT[h][i].first.book_code == b_code && HT[h][i].first.page == pg && HT[h][i].first.paragraph == para)
        {
            HT[h][i].second += scoreAdd;
            break;
        }
    }
    if (i == l)
    {
        HT[h].push_back({Node(b_code, pg, para, 0, 0), scoreAdd});
        siz_HT++;
    }
}

bool scoreMap::count(int &b_code, int &pg, int &para)
{
    int h = hashVal(b_code, pg, para);

    int l = HT[h].size();
    int i = 0;
    for (; i < l; i++)
    {
        if (HT[h][i].first.book_code == b_code && HT[h][i].first.page == pg && HT[h][i].first.paragraph == para)
        {
            return true;
        }
    }
    return false;
}

double scoreMap::getScore(int &b_code, int &pg, int &para)
{
    int h = hashVal(b_code, pg, para);

    int l = HT[h].size();
    int i = 0;
    for (; i < l; i++)
    {
        if (HT[h][i].first.book_code == b_code && HT[h][i].first.page == pg && HT[h][i].first.paragraph == para)
        {
            return HT[h][i].second;
        }
    }
    return 0.0;
}

inline bool scoreMap::empty()
{
    return siz_HT == 0;
}

void Linkedlist::insertnnode(Node *d)
{
    if (head == NULL)
    {
        head = d;
        tail = d;
        return;
    }
    tail->right = d;
    d->left=tail;
    tail = tail->right;
    tail->right=NULL;
}

void swapnode(Nodeheap *&p, Nodeheap *&q)
{
    Nodeheap *d = q;
    q = p;
    p = d;
}

// To heapify a subtree rooted with node i which is
// an index of arr[] and n is the size of heap
void heapifydown(vector<Nodeheap *> &arr, int n, int i)
{

    int largest = i;   // Initialize largest as root
    int l = 2 * i ; // left = 2*i + 1
    int r = 2 * i +1; // right = 2*i + 2
    // cout<<largest<<endl;
    // If left child is larger than root
    if (l < n && arr[l]->score > arr[largest]->score)
    {
        largest = l;}
        // cout<<largest<<endl;}
        // cout<<largest<<endl;

        // If right child is larger than largest so far
        if (r < n && arr[r]->score > arr[largest]->score)
        {
            largest = r;
        }

        // If largest is not root
        if (largest != i)
        {
            // cout<<arr[i]->score<<" "<<arr[largest]->score<<endl;
            swapnode(arr[i], arr[largest]);
            // cout<<arr[i]->score<<" "<<arr[largest]->score<<endl;

            // Recursively heapify the affected sub-tree
            // cout<<largest<<endl;
            heapifydown(arr, n, largest);
        }
    }


void buildheap(vector<Nodeheap *> &arr, int n)
{
    for (int j = (n - 1) / 2; j > 0; j--)
    {
        // cout<<j<<endl;
        heapifydown(arr, n, j);
    }
}

// void heapifyup(vector<Nodeheap *> &arr, int n, int i)
// {
//     // Find parent
//     if (i > 0)
//     {
//         int parent = (i - 1) / 2;
//         // For Max-Heap
//         // If current node is greater than its parent
//         // Swap both of them and call heapify again
//         // for the parent
//         // cout<<arr[i]->score<<"   "<<arr[parent]->score<<endl;
//         if (arr[i]->score > arr[parent]->score)
//         {
//             // cout<<"hih";
//             swapnode(arr[i], arr[parent]);
//             // Recursively heapify the parent node
//             heapifyup(arr, n, parent);
//         }
//     }
// }

// Function to insert a new node to the Heap
// void insertNode(vector<Nodeheap *> &arr, int &n, Nodeheap *Key)
// {

//     // Increase the size of Heap by 1
//     n = n + 1;

//     // Insert the element at end of Heap
//     arr.push_back(Key);

//     // cout<<arr[n-1]->score<<endl;

//     // Heapify the new node following a
//     // Bottom-up approach
//     heapifyup(arr, n, n - 1);
// }

// Function to delete the root from Heap
Nodeheap *deleteRoot(vector<Nodeheap *> &arr, int &n)
{
    if (n > 0)
    {
        Nodeheap *ans = arr[1];
        arr[1] = arr[n - 1];
        arr.pop_back();
        n = n - 1;
        heapifydown(arr, n, 1);
        return ans;
    }
    return NULL;
}

/* A utility function to print array of size n */
// void printArray(vector<Nodeheap*>&arr, int n)
// {
//     for (int i = 0; i < n; ++i)
//         cout << arr[i]->score << " ";
//     cout << "\n";
// }

Node *topk(vector<Nodeheap *> &arr, int n, int k)
{
    // cout<<n<<endl;
    Linkedlist *List = new Linkedlist();
    while (k > 0)
    {
        Nodeheap *ans = deleteRoot(arr, n);
        k--;
        Node *nd = new Node(ans->book, ans->page, ans->para, 0, 0);
        // cout<<ans->score<<" "<< ans->book<<" "<<ans->page<<" "<<ans->para<<endl;
        List->insertnnode(nd);
    }
    return List->head;
}

general_count::general_count()
{
    cap_HT = (int)1e6;
    HT = vector<vector<pair<string, long long>>>(cap_HT, vector<pair<string, long long>>(0));
}

general_count::~general_count()
{
}

long long general_count::power(long long a, long long b)
{
    // 31^12 excede limit of long long
    b %= 11;
    long long ans = 1;
    while (b > 0)
    {
        if (b & 1 == 1) // b is odd
            ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

long long general_count::hashVal(string &word)
{
    long long h = 0;
    long long l = word.length();

    for (long long i = 0; i < l; i++)
    {
        if (word[i] <= 'z' && word[i] >= 'a')
            h = (h + ((word[i] - 96) * power(31, i))) % cap_HT;
        else
            h = (h + ((word[i]) * power(31, i))) % cap_HT;
    }

    return h;
}

void general_count::push(string str, long long val)
{
    long long hash_val = hashVal(str);
    HT[hash_val].push_back({str, val});
}

bool general_count::count(string &str)
{
    long long hash_val = hashVal(str);
    for (pair<string, long long> &p : HT[hash_val])
    {
        if (p.first == str)
            return true;
    }
    return false;
}

long long general_count::value(string &str)
{
    long long hash_val = hashVal(str);
    for (pair<string, long long> &p : HT[hash_val])
    {
        if (p.first == str)
            return p.second;
    }
    return 0;
}

void QNA_tool::toLowerCase(string &s)
{
    /*
        input "SubHojIt iS A BoY."
        output "subhojit is a boy."
    */
    for (char &c : s)
        if ('A' <= c && c <= 'Z')
            c = c - 'A' + 'a';
}

inline bool QNA_tool::compareNode(Node &n1, Node &n2)
{
    if (n1.book_code == n2.book_code && n1.page == n2.page && n1.paragraph == n2.paragraph)
        return true;
    else
        return false;
}

QNA_tool::QNA_tool()
{
    // Implement your function here
    dictionary = Dict();
    gen_cnt = general_count();

    ifstream file("unigram_freq.csv");
    if (!file.is_open())
    {
        cerr << "file not found unigram_freq.csv" << endl;
    }

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        // Use a stringstream to split the line into word and frequency
        stringstream freq(line);
        string word;
        long long frequency;

        // Read the word and frequency from the stringstream
        getline(freq, word, ',');
        freq >> frequency;

        gen_cnt.push(word, frequency);
    }

    file.close();
}

QNA_tool::~QNA_tool()
{
    // Implement your function here
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    dictionary.insert_sentence(book_code, page, paragraph, sentence_no, sentence);
}

Node *QNA_tool::get_top_k_para(string question, int k)
{
    // Implement your function here
    toLowerCase(question);

    vector<pair<string, double>> word_list;
    // string stores the word in question
    // double stores the score of the word
    // score = freq_in_given_corpus / freq_in_csv_file

    int l = question.length();
    int x1 = 0, x2 = 0;
    Node total_cnt_node = Node(0, 0, 0, 0, 0);

    // creating word list vector of words in question
    // and also mapping their word scores
    while (x2 < l)
    {
        if (seperator[question[x2]])
        {
            string word;
            for (int i = x1; i < x2; i++)
            {
                word += question[i];
            }
            if (x1 < x2)
            {
                // get freq_in_given_corpus
                long long corpus_freq = dictionary.get_word_count(word).value(total_cnt_node);
                long long gen_freq = gen_cnt.value(word);
                double score = (double)(10000 * (corpus_freq + 1)) / (double)(gen_freq + 1);
                word_list.push_back({word, score});
                // cout << word << " = " << score << endl <<
                // "gen_freq = " << gen_freq << " corpus_freq = " << corpus_freq << endl ;
            }
            x1 = x2 + 1;
        }
        else if (x2 == l - 1)
        {
            string word;
            for (int i = x1; i <= x2; i++)
            {
                word += question[i];
            }
            if (x1 <= x2)
            {
                long long corpus_freq = dictionary.get_word_count(word).value(total_cnt_node);
                long long gen_freq = gen_cnt.value(word);
                double score = (double)(10000 * (corpus_freq + 1)) / (double)(gen_freq + 1);
                word_list.push_back({word, score});
                // cout << word << " = " << score << endl <<
                // "gen_freq = " << gen_freq << " corpus_freq = " << corpus_freq << endl ;
            }
        }
        x2++;
    }

    vector<pair<double, Node *>> score_vector;
    Nodeheap *panode = new Nodeheap(0.0,0,0,0);
    vector<Nodeheap *> heap={panode};
// as i have made 1 based indexing (by VTJ)
    int heap_siz = 1;

    scoreMap scrMp = scoreMap();

    // travell all those paragraphs in which words of the
    // question is present
    for (pair<string, double> &p1 : word_list)
    {
        myMap m = dictionary.get_word_count(p1.first);
        for (vector<pair<Node, long long>> &v : m.HT)
        {
            for (pair<Node, long long> &p2 : v)
            {
                if (compareNode(p2.first, total_cnt_node))
                {
                    continue;
                }

                // calculate add on score due to current word in word list
                // to the paragraph
                double addon = p2.second * p1.second; // freq in para * score of word

                // add this score to the node
                scrMp.scorePlus(p2.first.book_code, p2.first.page, p2.first.paragraph, addon);

                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                // get score for this paragraph
                // Nodeheap* para_node = new Nodeheap(0.0 , p2.first.paragraph , p2.first.page , p2.first.book_code) ;
                // heap.push_back(para_node) ; heap_siz++ ;
                // for(pair<string,double> &p3 : word_list) {
                //     para_node->score += (p3.second * p2.second) ;
                // }
                // score_vector.push_back({para_node->score , new Node(p2.first.book_code , p2.first.page , p2.first.paragraph , 0 , 0)}) ;
            }
        }
    }

    for (vector<pair<Node, double>> &v : scrMp.HT)
    {
        for (pair<Node, double> &p : v)
        {
            Nodeheap *para_node = new Nodeheap(p.second, p.first.paragraph, p.first.page, p.first.book_code);
            // if (p.first.book_code==355 or p.first.page==355 or p.first.paragraph==355 ){
            // cout<<p.second<<" "<< p.first.book_code<<" "<< p.first.page<<" "<< p.first.paragraph<<endl;}
            heap.push_back(para_node);
            heap_siz++;
            // score_vector.push_back
            //     ({p.second , new Node(p.first.book_code , p.first.page , p.first.paragraph , 0 , 0)}) ;
        }
    }
    // cout<<"end"<<endl;
    buildheap(heap, heap.size());
    // sort(score_vector.rbegin() , score_vector.rend()) ;

    // for(int i = 0 ; i <  k ; i++) {
    //     if(i<k-1)
    //         score_vector[i].second->right = score_vector[i+1].second ;
    //     else
    //         score_vector[i].second->right = NULL ;
    //     if(i > 0)
    //         score_vector[i].second->left = score_vector[i+1].second->left ;
    //     else
    //         score_vector[i].second->left = NULL ;
    // }

    return topk(heap, heap.size(), k);
    // return score_vector.front().second ;
}

void QNA_tool::query(string question, string filename)
{
    // Implement your function here
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: "
              << "Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph)
{

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;

    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
    {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ','))
        {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos)
            {
                token = token.substr(start, end - start + 1);
            }

            // Check if the element is a number or a string
            if (token[0] == '\'')
            {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            }
            else
            {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if (
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph))
        {
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node *root, int k, string API_KEY, string question)
{

    // first write the k paragraphs into different files

    Node *traverse = root;
    int num_paragraph = 0;

    while (num_paragraph < k)
    {
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();

    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}
