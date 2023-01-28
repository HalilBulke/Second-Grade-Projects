#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void linker(int* table,int row,int column,int n){   //This method finds links between balloons
    int link=0; //Counter
    int coordinate[8][2]; //This array stores coordinates of balloons that creates links
    for(auto & i : coordinate){ 
        for(int & j : i){
            j=-1;
        }
    }
    for(int i=1;(row-i)>=0 && i<3;i++){      //Check whether there can be links or not
        if(*(table + row * n + column) == *(table + (row-i) * n + column)) { //First it checks upper cell than if it is equal the id
            coordinate[i - 1][0] = row - i;                                  //stores its coordinate and increases link
            coordinate[i - 1][1] = column;
            link += 1;
            if ((column + 1) < n && *(table + row * n + column) == *(table + (row - 1) * n + (column + 1))) {
                coordinate[1][0] = row-1;                                   //Then it checks right cell
                coordinate[1][1] = column + 1;
                link += 1;
            } else if ((column - 1) >= 0 && *(table + row * n + column) == *(table + (row - 1) * n + (column - 1))) {
                coordinate[1][0] = row-1;                                   //Then it checks left cell
                coordinate[1][1] = column - 1;
                link += 1;
            }
        }else break;
    }
    for(int i=1;(row+i) < n && i<3;i++){
        if(*(table + row * n + column) == *(table + (row+i) * n + column)) {
            coordinate[i+1][0]=row+i;
            coordinate[i+1][1]=column;
            link+=1;
            if((column+1) < n && *(table + row * n + column) == *(table + (row+1) * n + (column+1))) {
                coordinate[3][0]=row+1;
                coordinate[3][1]=column+1;
                link+=1;
            }else if((column-1) >= 0 && *(table + row * n + column) == *(table + (row+1) * n + (column-1))){
                coordinate[3][0]=row+1;
                coordinate[3][1]=column-1;
                link+=1;
            }
        }else break;
    }
    for(int i=1;(column+1) < n && i<3;i++){
        if(*(table + row * n + column) == *(table + row * n + (column+i))) {
            coordinate[i+3][0]=row;
            coordinate[i+3][1]=column+i;
            link+=1;
            if((column+1) < n && *(table + row * n + column) == *(table + (row+1) * n + (column+1))) {
                coordinate[5][0]=row+1;
                coordinate[5][1]=column+1;
                link+=1;
            }else if((column-1) >= 0 && *(table + row * n + column) == *(table + (row-1) * n + (column+1))){
                coordinate[5][0]=row-1;
                coordinate[5][1]=column+1;
                link+=1;
            }
        }else break;
    }
    for(int i=1;(column-1) >= 0 && i<3;i++){
        if(*(table + row * n + column) == *(table + row * n + (column-i))) {
            coordinate[i+5][0]=row;
            coordinate[i+5][1]=column-i;
            link+=1;
            if((column+1) < n && *(table + row * n + column) == *(table + (row+1) * n + (column-i))) {
                coordinate[7][0]=row+1;
                coordinate[7][1]=column-1;
                link+=1;
            }else if((column-1) >= 0 && *(table + row * n + column) == *(table + (row-1) * n + (column-i))){
                coordinate[7][0]=row-1;
                coordinate[7][1]=column-1;
                link+=1;
            }
        }else break;
    }
    if(link>=2){  //If number of link reaches 3 this loop reaches coordinate of balloons that create links
        for(auto & i : coordinate){
            if(i[0]!= -1){
                *(table + i[0] * n + i[1])=0;
                }
            }
        *(table + row * n + column)+=1;
        linker(table, row, column,n); //After increasing the value, call linker function again to check possible links
    }
}
int main(int argc, char** argv){
    int lineNumber=-1;//Counts the number of lines inside input2 file
    int n,r,c,v;//Holds value, row, column information of balloons
    int point=0;//Holds the points for part 2
    int* table;//Table for 1 part
    int* bombTable;//Table for 2 part

    ofstream myFile(argv[3]);

    fstream file1;//reading input1 file
    file1.open(argv[1], ios::in);
    string line;
    if(!file1) {
        cout<<"No such file";
    } else {
        while (getline (file1, line)) {
            istringstream iss(line);
            vector<string> info1; //Vector to hold information about balloons coordinates
            for(string s1;iss>>s1;){
                info1.push_back(s1);}
            if(info1.size() == 1){
                n=stoi(info1[0]);
                table = new int[n * n];//Table array
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        *(table + i * n + j) = 0;
                    }
                }
            }
            else {
                r = stoi(info1[1]);
                c = stoi(info1[2]);
                v = stoi(info1[0]);
                *(table + r * n + c) = v;//According to information place balloons
                linker(table,r, c, n);//Call linker function to check possible link
            }
        }
        myFile<<"PART 1:"<<endl;//Writing table to the output file
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                myFile << *(table + i * n + j)
                     << " ";
            }
            myFile << endl;
        }
        myFile << endl;
        delete table;
        file1.close();
    }
    fstream file2;
    file2.open(argv[2], ios::in);
    string line2;
    if(!file2) {
        cout<<"No such file";
    } else {
        while (getline(file2, line2)) {
            istringstream iss(line2);
            vector<string> info;//Vector to hold information about bomb table
            for(string s;iss>>s;){
                info.push_back(s);}

            if (info.size() == 1) {
                n = stoi(info[0]);
                bombTable = new int[n * n];
            }
            else if(info.size() > 2){//Create bomb table array
                lineNumber++;
                for (int j = 0; j < n; j++) {
                    *(bombTable + lineNumber * n + j) = stoi(info[j]);
                }
            }
            else if(info.size() == 2){
                int row = stoi(info[0]);//Bomb coordinates
                int column = stoi(info[1]);

                for(int i=1;(row+i)<n;i++){//Check upper cells of the bomb
                    if(*(bombTable + row * n + column) == *(bombTable + (row+i) * n + column)) {
                        *(bombTable + (row + i) * n + column) = 0;
                        point+=*(bombTable + row * n + column);//If there is a match, the point increases
                    }
                }
                for(int i=1;(row-i) > -1;i++){//Check lower cells of the bomb
                    if(*(bombTable + row * n + column) == *(bombTable + (row-i) * n + column)) {
                        *(bombTable + (row - i) * n + column) = 0;
                        point+=*(bombTable + row * n + column);
                    }
                }
                for(int i=1;(column+i)<n;i++){//Check right-hand side cells of the bomb
                    if(*(bombTable + row * n + column) == *(bombTable + row * n + (column+i))) {
                        *(bombTable + row  * n + (column+i)) = 0;
                        point+=*(bombTable + row * n + column);
                    }
                }
                for(int i=1;(column-i)> -1;i++){//Check left-hand side cells of the bomb
                    if(*(bombTable + row * n + column) == *(bombTable + row * n + (column-i))) {
                        *(bombTable + row * n + (column-i)) = 0;
                        point+=*(bombTable + row * n + column);
                    }
                }
                for(int i=1;(row+i)< n &&(column+i)<n;i++){//Check bottom right cross cells of the bomb
                    if(*(bombTable + row * n + column) == *(bombTable + (row+i) * n + (column+i))) {
                        *(bombTable + (row + i) * n + (column+i)) = 0;
                        point+=*(bombTable + row * n + column);
                    }
                }
                for(int i=1;(row-i) > -1 && (column-i)> -1;i++){//Check left upper cross cells of the bomb
                    if(*(bombTable + row * n + column) == *(bombTable + (row-i) * n + (column-i))) {
                        *(bombTable + (row - i) * n + (column-i)) = 0;
                        point+=*(bombTable + row * n + column);
                    }
                }
                for(int i=1;(row-i) > -1 && (column+i) < n;i++){//Check upper right cross cells of the bomb
                    if(*(bombTable + row * n +column) == *(bombTable + (row-i) * n + (column+i))) {
                        *(bombTable + (row-i)  * n + (column+i)) = 0;
                        point+=*(bombTable + row * n + column);
                    }
                }
                for(int i=1;(row+i) < n && (column-i)> -1;i++){//Check left bottom cross cells of the bomb
                    if(*(bombTable + row * n + column) == *(bombTable + (row+i) * n + (column-i))) {
                        *(bombTable + (row+i) * n + (column-i)) = 0;
                        point+=*(bombTable + row * n +column);
                    }
                }
                point+=*(bombTable + row * n + column);
                *(bombTable + row * n + column) = 0;

            }
        }
        myFile<<"PART 2:"<<endl;
        for (int i = 0; i < n; i++) {//Writing bomb table to the output file
            for (int j = 0; j < n; j++) {
                myFile << *(bombTable + i * n + j)
                     << " ";
            }
            myFile << endl;
        }
        myFile <<"Final Point: "<<point<<"p"<< endl;
        delete bombTable;
        file2.close();
    }
    myFile.close();
    return 0;
}


