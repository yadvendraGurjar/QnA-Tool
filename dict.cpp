// Do NOT add any other includes
#include "dict.h"





/*                  map implimentation :
______________________________________________________________
*/

myMap::myMap() {
    siz_HT = 0 ;
    cap_HT = mods.front();
    HT = vector<vector<pair<Node,long long>>>(cap_HT , vector<pair<Node,long long>>(0)) ;
}



myMap::~myMap() {
    // nothing to delete specially as everything allocated on stack
}


inline int myMap::hashVal(Node i) {
    return  (i.paragraph + 100*i.book_code + 10*i.page) % cap_HT;
}

void myMap::resizeHT(bool increase) {
    if(cap_HT >= mods.back())
        return ;
    int newCap = 0 ;
    int m ; // this m points the index of vector mods ;
    for(m = 0 ; m < mods.size() ; m++)
        if(mods[m] == cap_HT) break ;

    if(increase)
        newCap = mods[m+1] ;
    else if(cap_HT <= mods.front())
        return ;
    else
        newCap = mods[m-1] ;

    vector<vector<pair<Node,long long>>> newHT 
        = vector<vector<pair<Node,long long>>>(newCap , vector<pair<Node,long long>>(0)) ;

    // travel old hash table, rehash all elements,
    // put them in new hash table

    for(vector<pair<Node,long long>> &v : HT) {
        for(pair<Node,long long> &p : v) {
            int newHashVal = (100*p.first.book_code + 10*p.first.page + p.first.paragraph) % newCap ;
            newHT[newHashVal].push_back({p.first,p.second}) ;
        }
    }

    cap_HT = newCap ; HT = newHT ;
    // cout << cap_HT << endl ;
    // older Hash table was declared on stack (static declaration)
    // so no need to delete old Hash table
}





inline bool myMap::compareNode(Node& n1 , Node& n2) {
    if(n1.book_code == n2.book_code && n1.page == n2.page && n1.paragraph == n2.paragraph)
        return true ;
    else
        return false ;
}




void myMap::push(Node key, long long val) {
    // if 70% filled then resizeHT
    if(cap_HT*10 < siz_HT*7) resizeHT(true) ;

    int h = hashVal(key) ;

    int l = HT[h].size() ;
    int i = 0 ;
    for( ; i < l ; i++) {
        if(compareNode(HT[h][i].first , key)) {
            HT[h][i].second = val ;
            break ;
        }
    }
    
    if(i == l) {
        HT[h].push_back({key , val}) ;
        siz_HT++ ;
    }
}

void myMap::erase(Node key) {
    int h = hashVal(key) ;

    int l = HT[h].size() ;
    for(int i = 0 ; i < l ; i++) {
        if(compareNode(HT[h][i].first , key)) {
            HT[h].erase(HT[h].begin() + i) ; siz_HT-- ;
            break ;
        }
    }
    // ========================
    // MAY NEED  RESIZE
    // TO BE IMPLIMENTED LATER
    // ========================
}

bool myMap::count(Node &key) {
    int h = hashVal(key) ;

    int l = HT[h].size() ;
    for(int i = 0 ; i < l ; i++) {
        if(compareNode(HT[h][i].first , key)) {
            return true ;
        }
    }
    return false ;
}

long long myMap::value(Node &key) {
    int h = hashVal(key) ;

    int l = HT[h].size() ;
    for(int i = 0 ; i < l ; i++) {
        if(compareNode(HT[h][i].first , key)) {
            return HT[h][i].second ;
        }
    }
    return 0 ;
}

inline bool myMap::empty() {
    return siz_HT == 0 ;
}





















































/*                    Utility functions :
______________________________________________________________
*/


long long Dict::power(long long a , long long b) {
    // 31^12 excede limit of long long
    b %= 11 ;
    long long ans = 1 ;
    while(b > 0) {
        if(b & 1 == 1)  // b is odd
            ans *= a ;
        a *= a ;
        b >>= 1 ;
    }
    return ans ;
}


long long Dict::hashVal(string &word) {

    /*
        hash val of "abc"
        = 1*31^0 + 2*31^1 + 3*31^2
        = 1 + 62 + 2883 = 2946 % 1009 = 928
    */

    long long h = 0 ;
    long long l = word.length() ;

    for(long long i = 0 ; i < l ; i++) {
        if( word[i] <= 'z' && word[i] >= 'a')
            h = (h + ((word[i] - 96)*power(31 , i))) % capHT ;
        else
            h = (h + ((word[i])*power(31 , i))) % capHT ;
    }

    return h ;
}


void Dict::toLowerCase(string &s) {
    /*
        input "SubHojIt iS A BoY."
        output "subhojit is a boy."
    */
    for(char &c : s)    if('A' <= c && c <= 'Z')
                            c = c - 'A' +'a' ;
}



void Dict::resizeHT() {
    
    long long m ;
    for(m = 0 ; m < mods.size() ; m++)
        if(mods[m] == capHT) break ;

    long long newCap = (long long)mods[m + 1] ;
    vector<vector<pair<string,myMap>>> newHT(newCap , vector<pair<string,myMap>>(0)) ;

    // travel old HT and rehash elements put them in new table
    for(long long i  = 0 ; i < capHT ; i++) {
        for(pair<string,myMap> p : HT[i]) {
            long long h = 0 ;
            long long l = p.first.length() ;

            for(long long k = 0 ; k < l ; k++) {
                if( p.first[k] <= 'z' && p.first[k] >= 'a')
                    h = (h + ((p.first[k] - 96)*power(31 , k))) % newCap ;
                else
                    h = (h + ((p.first[k])*power(31 , k))) % newCap ;
            }
            
            newHT[h].push_back(p) ;
        }
    }
    capHT = newCap ; HT = newHT ;
}


void Dict::insertInHT(string word , Node n) {
    
    
    // check for resize
    if(((capHT * 3) / 5) < sizeHT && capHT < mods.back()) {
        resizeHT() ;
    }

    Node total_cnt = Node(0,0,0,0,0) ;

    // insert the word
    long long h = hashVal(word) ;
    long long l = HT[h].size() ;
    long long i = 0 ;
    for( ; i < l ; i++) {
        if(HT[h][i].first == word) {
            long long node_count = 1 + HT[h][i].second.value(n) ;
            long long total_count = 1 + HT[h][i].second.value(total_cnt) ;
            HT[h][i].second.push(total_cnt,total_count) ;
            HT[h][i].second.push(n,node_count) ;
            break;
        }
    }

    if(i == l) {
        HT[h].push_back({word,myMap()}) ;
        HT[h][i].second.push(total_cnt,1) ;
        HT[h][i].second.push(n,1) ;
        sizeHT++ ;
    }

}

/*                   Main functions:
______________________________________________________________
*/

Dict::Dict() {
    // Implement your function here
    sizeHT = 0 ;
    capHT = mods[0] ;
    HT = vector<vector<pair<string,myMap>>>(capHT , vector<pair<string,myMap>>(0)) ;
}

Dict::~Dict(){
    // Implement your function here

    // nothing to delete specially as everything allocated on stack
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // cout << endl;
    // Implement your function here
    Node n = Node(book_code,page,paragraph,sentence_no,0) ;
    toLowerCase(sentence) ;
    int l = sentence.length() ;
    int x1 = 0 , x2 = 0 ;

    while(x2 < l) {
        if(seperator[sentence[x2]]) {
            string word ;
            for(int i = x1 ; i < x2 ; i++) {
                word += sentence[i] ;
            }
            if(x1 < x2) {
                insertInHT(word,n) ;
            }
            x1 = x2 + 1 ;
        } else if (x2 == l-1) {
            string word ;
            for(int i = x1 ; i <= x2 ; i++) {
                word += sentence[i] ;
            }
            if(x1 <= x2) {
                // toLowerCase(word) ;
                insertInHT(word,n) ;
            }
        }
        x2++ ;
    }
}

myMap Dict::get_word_count(string word){
    // Implement your function here
    toLowerCase(word) ;
    long long h = hashVal(word) ;

    for(pair<string,myMap> &p : HT[h])
        if(p.first == word) return p.second ;

    return myMap();
}

// void Dict::dump_dictionary(string filename){
//     // Implement your function here  
//     ofstream out(filename , ios::app) ;

//     for(vector<pair<string,int>> &v : HT) {
//         for(pair<string,int> &p : v)
//             out << p.first << ", " << p.second << endl ;
//     }

//     out.close();
// }

/*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
                        END OF CODE
                    Yadvendra | Subhojit
                  2022EE31764 | 2022mt61976
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/