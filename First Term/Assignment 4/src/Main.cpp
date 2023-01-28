#include <iostream>
#include <fstream>
#include <sstream>
#include "Trie.h"

vector<string> split(const string& info){         //Function to split strings for insert operation
    string tmp;
    stringstream ss(info.substr(7,info.size()-8));
    vector<string> information;                               //Vector to hold information as a string
    while(getline(ss, tmp, ',')){               //Split string
        information.push_back(tmp);
    }
    return information;
}

int main(int argc, char** argv) {
    fstream file1;              //reading input file
    file1.open(argv[1], ios::in);
    ofstream outputFile(argv[2]); //output file
    string line;
    Trie t; //This is our trie
    if(!file1) {
        cout<<"No such file";
    } else {
        while (getline(file1, line)) {       //Reading line by line
            if (line[0] == 'i') {                   //For insert operation
                vector<string> temp= split(line);   //Splitting string to reach insert key and its English equivalent
                t.insert(temp[0],temp[1],outputFile);    //Insert function
            } else if (line[0] == 's') {            //For search operation
                int i=0;
                while(line[i]!=')'){
                    i++;
                }
                outputFile<<t.search(line.substr(7,(i-7)))<<endl;
            } else if (line[0] == 'd') {            //For delete operation
                int i=0;
                while(line[i]!=')'){
                    i++;
                }
                t.del(line.substr(7,(i-7)),outputFile);
            } else if (line[0] == 'l') {             //For list operation
                t.list(outputFile);
            }
        }
    }
    file1.close();
    outputFile.close();
    return 0;
}
