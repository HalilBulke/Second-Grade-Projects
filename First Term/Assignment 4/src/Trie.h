#ifndef ASSIGNMENT4_TRIE_H
#define ASSIGNMENT4_TRIE_H


#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Trie {

    class Node{
    public:
        bool ends;//Bool ends to determine while traversing trie whether words ends or not
        char value;//Stored value inside node
        Node *next[26];//Array for next nodes of trie
        string mean;//The English equivalent for the given Dothraki word

        Node(const char c){//Node constructor
            for(auto & i : this->next){//Initialize next array
                i = nullptr;
            }
            this->value=c;
            this->ends= false;
        }
    };

    Node* root;//Root of the trie
public:
    Trie(){
        root = new Node(' ');//Creates root of the trie
    };
    ~Trie()= default;

    void insert(const string& k, const string& v,ofstream &outputFile) {//Insert function takes 2 parameter: inserted key,its English equivalent
        string result= search(k);//First searching for given key whether it was inserted before or not
        if(result[1] == 'T'){//If it is inserted before
            Node* temp = root;  //Search whether its mean same or not
            for (int i = 0; i < k.length(); i++) {
                int index = k[i] - 'a';
                temp = temp->next[index];
            }
            if(temp->mean==v){ //If mean was inserted same
                outputFile<<'"'<< k << '"'<< " already exist"<<endl;
            }else{
                temp->mean=v;//Else update keys mean
                outputFile<<'"'<< k << '"'<< " was updated"<<endl;
            }
        }
        else {//If it is not inserted before
            Node *temp = root;//Create temporary root to traverse trie
            for (int i = 0; i < k.length(); i++) {//Loop to insert key
                int index = k[i] - 'a';//Find its index in array
                if (!temp->next[index]) {//If there is no node that was inserted before
                    temp->next[index] = getNode(k[i]);//Create new node
                }
                temp = temp->next[index];
            }
            temp->mean = v;//Once traverse done put mean to the last node
            temp->ends = true;//Change ends true
            outputFile<<'"'<< k << '"'<<" was added"<<endl;
        }
    }

    string search(const string& k) {
        string output;
        Node* temp = root;
        int first = k[0] - 'a';
        if(!temp->next[first]){//If no character of given key was inserted
            output= "\"no record\"";
        }
        else {
            for (int i = 0; i < k.length(); i++) {
                int index = k[i] - 'a';
                if (!temp->next[index]) {//If some character of given key was inserted but not enough
                    output= "\"incorrect Dothraki word\"";
                    return output;
                }
                temp = temp->next[index];
            }
            if (!temp->ends) {//If all character of given key was inserted but there is no word same as key in trie
                output= "\"not enough Dothraki word\"";
            } else if (temp->ends) {//If all character of given key was inserted before return its mean
                output= "\"The English equivalent is " + temp->mean+'"';
            }
        }
        return output;
    }

    static bool isFilled(Node* root){//Function to determine whether given node has childes or not
        for (auto & i : root->next) {//Loop for given roots next array
            if (i) {//If one of them is filled before return false
                return false;
            }
        }
        return true;//else return true
    }

    void del(const string& k,ofstream &outputFile) {    //Function for delete operation
        string result = search(k); //First search whether given key was inserted before or not
        if(result[1] == 'T'){      //If its inserted call deleteHelper function to delete operation
            deleteHelper(root,k);
            outputFile<<'"'<<k<<'"'<<" deletion is successful"<<endl;
        }else
            outputFile<<result<<endl;
    }
    Node* deleteHelper(Node* temporaryRoot, const string& k, int counter=0) {
        //This function used recursively to handle deletion operation
        //because to delete a key, first we reach end of the key and then move backward
        //to avoid deleting branches of the given key has

        if (!temporaryRoot) {   //It is the base case
            return nullptr;     //If reach the empty root
        }
        if (counter == k.size()) {//If we reach the end of the key
            if (temporaryRoot->ends) {//Check whether it ends or not
                temporaryRoot->ends = false;//If it is,change ends true so this key doesn't represent in trie anymore
            }
            if (isFilled(temporaryRoot)) {//Check whether given root has childes or not
                delete (temporaryRoot);//If not,delete given root
                temporaryRoot = nullptr;
            }
            return temporaryRoot;
        }
        int index = k[counter] - 'a';//Find its index in array
        //Recursively go to end of the given key
        temporaryRoot->next[index] = deleteHelper(temporaryRoot->next[index], k, counter + 1);

        if (isFilled(temporaryRoot) && !temporaryRoot->ends) {//Check whether given root has childes or not and Check whether it ends or not
            delete (temporaryRoot);//If yes delete given root
            temporaryRoot = nullptr;
        }
        return temporaryRoot;
    }

    void list(ofstream &outputFile) {//Function to list trie
        listHelper(root,outputFile);
    }
    static bool hasBranch(Node* root){//This function used to determine whether given root has branched or not
        int branch =0;//Branch counter
        for (auto & i : root->next)
            if (i)//if it has branched
                branch+=1;//increase the number of branch counter
        return branch > 1;
    }

    void listHelper(Node* temporaryRoot,ofstream &outputFile, const string& k = ""){
        //It takes root node,output file
        // and string k to store characters was traversed in trie
        //This function also traverses trie recursively
        if (temporaryRoot->ends) {//Base case
            if(k[0] == '\t'){//If it's a branch
                outputFile << k + "(" + temporaryRoot->mean + ")" << endl;//Write without "-"
            }else{
                outputFile << "-" + k + "(" + temporaryRoot->mean + ")" << endl;
            }
            if(hasBranch(temporaryRoot)){//If it has also branches
                if(k[0] == '\t'){
                    auto *temp= const_cast<string *>(&k);//Using pointers add tab to indicate it is branched
                    *temp= "\t" + k;
                }else{
                    auto *temp= const_cast<string *>(&k);//Add "-" too
                    *temp= "-" + k;
                    *temp= "\t" + k;
                }
            }
        }
        else if(temporaryRoot->value != ' ' && hasBranch(temporaryRoot)){//If it is not root of the trie and has branched
            if(k[0] == '\t'){
                outputFile << k << endl;
            }else{
                outputFile << "-" + k << endl;
            }
            if(k[0] == '\t'){
                auto *temp= const_cast<string *>(&k);
                *temp= "\t" + k;
            }else{
                auto *temp= const_cast<string *>(&k);
                *temp= "-" + k;
                *temp= "\t" + k;
            }
        }
        for (int i = 0; i < 26; i++) {
            if (temporaryRoot->next[i] != nullptr) {
                listHelper(temporaryRoot->next[i],outputFile, k + temporaryRoot->next[i]->value);//Everytime update key
            }
        }
    }

    static Node* getNode(char c) {//Creates nodes when needed
        Node* newNode = new Node(c);
        return newNode;
    }

};



#endif //ASSIGNMENT4_TRIE_H
