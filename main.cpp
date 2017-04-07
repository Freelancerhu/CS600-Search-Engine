#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
using namespace std;

struct Node {
    char chara;
    vector<Node*> N;        // pointer to child
    bool isWord = false;    // is or is not a word
    vector<int> netAdd;  // address of netsite
    Node(){}
    Node(char c) : chara(c) {}
};

class Tries {
private :
    Node* Root;
public:
    Tries() {
        Root = new Node();
    }
    void insertWord(string str, int netAddress) {
        Node* root = Root;
        for (size_t i = 0; i < str.size(); ++i) {
            if (root->N.empty()) {
                Node* tempNode = new Node(str[i]);
                root->N.push_back(tempNode);
                root = tempNode;
                if (i + 1 == str.size()) {
                    root->isWord = true;
                    if (root->netAdd.empty()) {
                        root->netAdd.push_back(netAddress);
                    } else {
                        for (auto x : root->netAdd) {
                            if(x == netAddress) {
                                return;
                            }
                        }
                        root->netAdd.push_back(netAddress);
                    }
                }
            } else {
                for (size_t j = 0; j < root->N.size(); ++j) {
                    if (root->N[j]->chara == str[i]) {
                        root = root->N[j];
                        if (i + 1 == str.size()) {
                            root->isWord = true;
                            if (root->netAdd.empty()) {
                                root->netAdd.push_back(netAddress);
                            } else {
                                for (auto x : root->netAdd) {
                                    if(x == netAddress) {
                                        return;
                                    }
                                }
                                root->netAdd.push_back(netAddress);
                            }
                        }
                        break;
                    }
                    if (j + 1 == root->N.size()) {
                        Node* tempNode = new Node(str[i]);
                        root->N.push_back(tempNode);
                        root = tempNode;
                        if (i + 1 == str.size()) {
                            root->isWord = true;
                            if (root->netAdd.empty()) {
                                root->netAdd.push_back(netAddress);
                            } else {
                                for (auto x : root->netAdd) {
                                    if(x == netAddress) {
                                        return;
                                    }
                                }
                                root->netAdd.push_back(netAddress);
                            }
                        }
                    }
                }
            }
        }
    }

//    void printFirstWord() {
//        string res = "";
//        Node* root = Root;
//        while (1) {
//            res += root->N[0]->chara;
//            root = root->N[0];
//            if (root->isWord == true) {
//                break;
//            }
//        }
//        cout << res << endl;
//    }

    vector<int> queryWords (string str) {
        vector<int> res;
        Node* root = Root;
       // cout << root->N.size() <<endl; // abcdefg   bbb
        for (size_t i = 0; i < str.size(); ++i) {
            for (size_t j = 0; j < root->N.size(); ++j) {
                if (str[i] == root->N[j]->chara) {  //found
                    root = root->N[j];              //next pointer
                    if (i + 1 == str.size() && root->isWord == true) {      //if str[i] is the last element/character and is a word then return
                        return root->netAdd;
                    }
                    if (i + 1 == str.size() && root->isWord != true) {
                        return res;
                    }
                    break;
                }
                if (j + 1 == root->N.size()) {      // not found
                    return res;                     // return NULL vector
                }
            }
        }
    }
};

int main() {
    Tries B;
    vector<string> web{"www.1.com", "www.2.com", "www.3.com"};

    ifstream fin1("test1.txt");
    string s1;
    while (fin1 >> s1) {
        string tempS = "";
        for (size_t i = 0; i < s1.size(); ++i) {
            if (s1[i] == ' '||s1[i] == '(' || s1[i] == ')' || s1[i] == ':' || s1[i] == '"'
                    ||s1[i] == '\'' || s1[i] == '.'|| s1[i] == ',' || s1[i] == '?') {
                continue;
            } else {
                tempS += s1[i];
            }
        }

        if (tempS.size() == 0) {
            continue;
        } else {
            cout << tempS << endl;
            B.insertWord(tempS, 0);
        }
    }
    fin1.close();
    cout << "========================" << endl;
    ifstream fin2("test2.txt");
    string s2;
    while (fin2 >> s2) {
        string tempS = "";
        for (size_t i = 0; i < s2.size(); ++i) {
            if (s2[i] == ' '||s2[i] == '(' || s2[i] == ')' || s2[i] == ':' || s2[i] == '"'
                    ||s2[i] == '\'' || s2[i] == '.'|| s2[i] == ',' || s2[i] == '?') {
                continue;
            } else {
                tempS += s2[i];
            }
        }
        if (tempS.size() == 0) {
            continue;
        } else {
            cout << tempS << endl; //" ():""''.,<>/?[]{}=-"
            B.insertWord(tempS, 1);
        }
    }
    fin2.close();
    cout << "========================" << endl;
    fin2.open("test3.txt",std::ifstream::in);
    while (fin2 >> s2) {
        string tempS = "";
        for (size_t i = 0; i < s2.size(); ++i) {
            if (s2[i] == ' '||s2[i] == '(' || s2[i] == ')' || s2[i] == ':' || s2[i] == '"'
                    ||s2[i] == '\'' || s2[i] == '.'|| s2[i] == ',' || s2[i] == '?') {
                continue;
            } else {
                tempS += s2[i];
            }
        }
        if (tempS.size() == 0) {
            continue;
        } else {
            cout << tempS << endl; //" ():""''.,<>/?[]{}=-"
            B.insertWord(tempS, 2);
        }
    }
    fin2.close();
    cout << "========================" << endl;



    string strQuery;
    string isStop;
    vector<string> vecQuery;
    map<int, int> multiQuery;
    vector<string> result;
    do {
        cout << "Enter one word or Press 'q' or 'Q' to quit." << endl;
        while(1) {
            cin >> strQuery;
            if (strQuery == "Q" || strQuery == "q") {
                break;
            }
            vecQuery.push_back(strQuery);
            cout << "Enter one word or Press 'q' or 'Q' to quit." << endl;
        }

        for (auto x : vecQuery) { // the words which user wanna to query
            vector<int> res = B.queryWords(x);      //index of website, 1 2 3
            if (res.empty()) {
                cout << "res is empty;" << endl;
            }

            for (auto y : res) {
                if (multiQuery.find(y) == multiQuery.end()) {
                    multiQuery.insert(pair<int, int>(y, 1));
                } else {
                    multiQuery[y]++;
                }
            }
        }

        for (auto x : multiQuery) {
            if (x.second == vecQuery.size()) {
                result.push_back(web[x.first]);
            }
        }
        if (result.empty()) {
            cout << "There is no website contenting ALL the given keywords." << endl;
        } else {
            for (auto x : result) {
                cout << x << endl;
            }
        }
        strQuery.clear();
        vecQuery.clear();
        result.clear();
        multiQuery.clear();
        cout << "continue?<Y/N>";
        cin >> isStop;
    } while( isStop == "y" || isStop == "Y");
    return 0;
}
