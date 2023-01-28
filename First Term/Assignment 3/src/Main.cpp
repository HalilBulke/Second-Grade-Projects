#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<string> findFinal(const string& info){           //Function to split strings and find final states
    int i =0;
    while(i<info.size()){
        if(info[i]=='['){
            break;
        }i++;
    }
    string tmp;
    stringstream ss(info.substr(i,info.size()));
    vector<string> information;                        //Vector to hold information as a string
    while(getline(ss, tmp, ',')){                      //Split string
        information.push_back(tmp.substr(1,tmp.size()-2));
    }
    return information;
}

vector<string> split(const string& info){           //Function to split strings
    int i =0;
    while(i<info.size()){
        if(info[i]==' '){
            break;
        }i++;
    }
    string tmp;
    stringstream ss(info.substr(2,i-2));
    vector<string> information;                      //Vector to hold information as a string
    while(getline(ss, tmp, ',')){                    //Split string
        information.push_back(tmp);
    }
    return information;
}
void writeStack(stack<string> myStack, ofstream &outputFile)//Function to write stack items
{
    string output;
    stack<string> copyStack(std::move(myStack));
    while(!copyStack.empty()){
        output += copyStack.top()+",";
        copyStack.pop();
    }
    for (int i=output.length()-2; i>=0; i--){
        outputFile<<output[i];
    }
}
void writeTransitions( const string& T0 , const string& T1 ,  const string& T2 ,const string& T3,const string& T4,ofstream &outputFile){
    outputFile << T0 + "," << T1 + "," << T2 + " => " << T3 + "," << T4 << " [STACK]:";
}
int main(int argc, char** argv) {
    stack<string> myStack;//Used for stack operations

    vector<string> states;  //These vectors used for storing file information
    vector<string> finalStates;
    vector<string> symbols;
    vector<string> stackSymbols;
    vector<string> T;   //For Transitions
    vector<vector<string>> Ts;


    ofstream outputFile(argv[3]); 

    fstream file1;              //reading input1 file
    file1.open(argv[1], ios::in);
    string line;
    if(!file1) {
        cout<<"No such file";
    } else {
        while (getline(file1, line)) {            //Splitting and holding in vector dpda information
            if(line[0] == 'Q'){                         //state infos
                states=split(line);
                finalStates=findFinal(line);
            }
            else if(line[0] == 'A'){                    //input symbols infos
                symbols=split(line);
                symbols.emplace_back("e");
            }
            else if(line[0] == 'Z'){                    //stack symbol infos
                stackSymbols=split(line);
                stackSymbols.emplace_back("e");
            }
            else if(line[0] == 'T'){                    //transition rules
                T=split(line);

                        //DPDA description checks
                if(find(states.begin(), states.end(), T[0]) != states.end() && find(states.begin(), states.end(), T[3]) != states.end()&&
                find(symbols.begin(), symbols.end(), T[1]) != symbols.end() &&
                find(stackSymbols.begin(), stackSymbols.end(), T[2]) != stackSymbols.end()&&
                find(stackSymbols.begin(), stackSymbols.end(), T[4]) != stackSymbols.end()) {
                    Ts.push_back(T);
                } else {
                    outputFile<<"Error [1]:DPDA description is invalid!"<<endl;
                    exit(0);
                }
            }

        }
    }
    file1.close();

    string state;       //current state

    fstream file2;      //reading input1 file
    file2.open(argv[2], ios::in);
    string line2;
    if(!file2) {
        cout<<"No such file";
    } else {
        vector<string> information2;            //Vector to hold input information as a string
        while (getline(file2, line2)) {
            string tmp;
            stringstream ss(line2);
            while (getline(ss, tmp, ',')) {   //Split string
                information2.push_back(tmp);
            }
            if (find(stackSymbols.begin(), stackSymbols.end(), "$") != stackSymbols.end()) {//IF $ symbol used

                int j = 0;
                if(information2.empty()){
                    outputFile<<"ACCEPT"<<endl<<endl;
                }else {
                    for(auto & T1 : Ts)                          //starting from starter state
                        if (T1[0] == states[0]) {
                            myStack.push(T1[4]);            //pushing to stack
                            writeTransitions(T1[0], T1[1] ,T1[2] , T1[3], T1[4], outputFile);
                            writeStack(myStack, outputFile);              //writing stack
                            outputFile << endl;
                            state = T1[3];                              //changing current state
                        }
                    while (j < information2.size()) {                   //loops for finding right transition rule
                        for (int i = 0; i < Ts.size(); i++) {
                            if(Ts[i][0]==state && Ts[i][1] == "e"){
                                if(Ts[i][2] != "e"){
                                    myStack.pop();
                                }
                                if(Ts[i][4] != "e") {
                                    myStack.push(Ts[i][4]);
                                }
                                writeTransitions(Ts[i][0], Ts[i][1] , Ts[i][2] , Ts[i][3] ,Ts[i][4], outputFile);
                                writeStack(myStack, outputFile);
                                outputFile << endl;
                                state = Ts[i][3];
                                if (myStack.size() ==1 && find(finalStates.begin(), finalStates.end(), state) != finalStates.end()) {
                                    outputFile << "ACCEPT"<< endl<< endl;
                                    j++;
                                    break;
                                }
                                if (j + 1 == information2.size() && myStack.size() !=1) {
                                    outputFile << "REJECT"<< endl<< endl;
                                    j++;
                                    break;
                                }
                                break;
                            }
                            if(Ts[i][0]==state && Ts[i][1] == information2[j] && (Ts[i][2] == "e" || Ts[i][2] ==myStack.top())){
                                if(Ts[i][2] != "e"){
                                    myStack.pop();
                                }
                                if(Ts[i][4] != "e") {
                                    myStack.push(Ts[i][4]);
                                }
                                writeTransitions(Ts[i][0], Ts[i][1] , Ts[i][2] , Ts[i][3] ,Ts[i][4], outputFile);
                                writeStack(myStack, outputFile);
                                outputFile << endl;
                                state = Ts[i][3];
                                if (myStack.size()==1 && find(finalStates.begin(), finalStates.end(), state) != finalStates.end()) {
                                    outputFile << "ACCEPT"<< endl<< endl;
                                }
                                else if (myStack.size() == 1) {
                                    for (int k = 0; k < Ts.size(); k++) {
                                        if (Ts[k][0] == state && Ts[k][1] == Ts[i][4] && find(finalStates.begin(), finalStates.end(), Ts[k][3]) != finalStates.end()) {
                                            writeTransitions(Ts[k][0] ,Ts[k][1] , Ts[k][2],Ts[k][3] ,Ts[k][4], outputFile);
                                            writeStack(myStack, outputFile);
                                            outputFile << endl;
                                        }
                                    }
                                    outputFile << "ACCEPT"<< endl<< endl;
                                }
                                if (j + 1 == information2.size() && myStack.size() != 1) {
                                    if(Ts[i][4] != "e") {
                                        myStack.push(Ts[i][4]);
                                    }
                                    for (int k = 0; k < Ts.size(); k++) {
                                        if (Ts[k][0] == state && (Ts[k][1] == Ts[i][4] || Ts[k][1] == "e")) {
                                            writeTransitions(Ts[k][0] ,Ts[k][1] , Ts[k][2],Ts[k][3] ,Ts[k][4], outputFile);
                                            writeStack(myStack, outputFile);
                                            outputFile << endl;
                                        }
                                    }
                                    outputFile << "REJECT"<< endl<< endl;

                                }
                                j++;
                                break;
                            }
                        }
                    }
                }
            }else {
                int j = 0;
                if(information2.empty()){
                    outputFile<<"ACCEPT"<<endl<<endl;
                }else {
                    state=states[0];
                    while (j < information2.size()) {
                        for (int i = 0; i < Ts.size(); i++) {
                            if(Ts[i][0]==state && Ts[i][1] == "e"){
                                if(Ts[i][2] != "e"){
                                    myStack.pop();
                                }
                                if(Ts[i][4] != "e") {
                                    myStack.push(Ts[i][4]);
                                }
                                writeTransitions(Ts[i][0], Ts[i][1] , Ts[i][2] , Ts[i][3] ,Ts[i][4], outputFile);
                                writeStack(myStack, outputFile);
                                outputFile << endl;
                                state = Ts[i][3];
                                if (myStack.empty() && find(finalStates.begin(), finalStates.end(), state) != finalStates.end()) {
                                    outputFile << "ACCEPT"<< endl<< endl;
                                    j++;
                                    break;
                                }
                                if (j + 1 == information2.size() && !myStack.empty()) {
                                    outputFile << "REJECT"<< endl<< endl;
                                    j++;
                                    break;
                                }
                                break;
                            }
                            if(Ts[i][0]==state && Ts[i][1] == information2[j] && (Ts[i][2] == "e" || Ts[i][2] ==myStack.top())){
                                if(Ts[i][2] != "e"){
                                    myStack.pop();
                                }
                                if(Ts[i][4] != "e") {
                                    myStack.push(Ts[i][4]);
                                }
                                writeTransitions(Ts[i][0], Ts[i][1] , Ts[i][2] , Ts[i][3] ,Ts[i][4], outputFile);
                                writeStack(myStack, outputFile);
                                outputFile << endl;
                                state = Ts[i][3];
                                if (myStack.empty() && find(finalStates.begin(), finalStates.end(), state) != finalStates.end()) {
                                    outputFile << "ACCEPT"<< endl<< endl;

                                }
                                else if (myStack.empty()) {
                                    for (int k = 0; k < Ts.size(); k++) {
                                        if (Ts[k][0] == state && Ts[k][1] == Ts[i][4] && find(finalStates.begin(), finalStates.end(), Ts[k][3]) != finalStates.end()) {
                                            writeTransitions(Ts[k][0] ,Ts[k][1] , Ts[k][2],Ts[k][3] ,Ts[k][4], outputFile);
                                            writeStack(myStack, outputFile);
                                            outputFile << endl;
                                        }
                                    }
                                    outputFile << "ACCEPT"<< endl<< endl;
                                }
                                if (j + 1 == information2.size() && !myStack.empty()) {
                                    if(Ts[i][4] != "e") {
                                        myStack.push(Ts[i][4]);
                                    }
                                    for (int k = 0; k < Ts.size(); k++) {
                                        if (Ts[k][0] == state && (Ts[k][1] == Ts[i][4] || Ts[k][1] == "e")) {
                                            writeTransitions(Ts[k][0] ,Ts[k][1] , Ts[k][2],Ts[k][3] ,Ts[k][4], outputFile);
                                            writeStack(myStack, outputFile);
                                            outputFile << endl;
                                        }
                                    }
                                    outputFile << "REJECT"<< endl<< endl;
                                }
                                j++;
                                break;
                            }
                        }
                    }
                }
            }
            while (!myStack.empty()) {//Clearing stack for the new lines
                myStack.pop();
            }
            information2.clear();//Clearing information vector for the new lines
        }
        file2.close();
    }
    outputFile.close();

    return 0;
}
