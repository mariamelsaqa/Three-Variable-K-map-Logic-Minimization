//
//  main.cpp
//  Project1
//
//  Created by Mariam Elsaqa on 3/19/21.
//  Copyright © 2021 None. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int COLUMNS = 4, ROWS = 2;
int NoMinterms = 0, DMinterm[7];
string simplifiedBool = " ";

struct MapElement
{
    int binarydigit;
    int DForm;
    int include = 0;
    string BForm;
};
struct output
{
    vector <MapElement> minterm;
    int size;
};

MapElement Kmap[ROWS][COLUMNS];

vector <MapElement> v1, v2, v3, v4, v5, v6, MaxElements;
vector <output> Implicants;

void getInput()
{
    cout << "How many midterms do you have?" << endl;
    cin >> NoMinterms;
    cout << "Enter minterms in  decimal form ex: 0 1 2 3 5" << endl;
    int tempMinterm;
    for(int i =0; i<NoMinterms;i++){
        do
        {
            cin >> tempMinterm;
            if(tempMinterm > 7 || tempMinterm < 0){
                cout<<"Try again, minterm should be between 0 and 7 inclusive"<<endl;
            }
        } while (tempMinterm > 7 || tempMinterm < 0);
        DMinterm[i] = tempMinterm;}
}

void kmap(){
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
            Kmap[i][j].binarydigit = 0;

    Kmap[0][0].DForm = 0;
    Kmap[0][1].DForm = 1;
    Kmap[0][2].DForm = 3;
    Kmap[0][3].DForm = 2;
    Kmap[1][0].DForm = 4;
    Kmap[1][1].DForm = 5;
    Kmap[1][2].DForm = 7;
    Kmap[1][3].DForm = 6;


    for (int i = 0; i < NoMinterms; i++)
    {
        if (DMinterm[i] == 0)
            Kmap[0][0].binarydigit = 1;
        else if (DMinterm[i] == 1)
            Kmap[0][1].binarydigit = 1;
        else if (DMinterm[i] == 2)
            Kmap[0][3].binarydigit = 1;
        else if (DMinterm[i] == 3)
            Kmap[0][2].binarydigit = 1;
        else if (DMinterm[i] == 4)
            Kmap[1][0].binarydigit = 1;
        else if (DMinterm[i] == 5)
            Kmap[1][1].binarydigit = 1;
        else if (DMinterm[i] == 6)
            Kmap[1][3].binarydigit = 1;
        else if (DMinterm[i] == 7)
            Kmap[1][2].binarydigit = 1;
    }
    Kmap[0][0].BForm = "000";
    Kmap[0][1].BForm = "001";
    Kmap[0][2].BForm = "011";
    Kmap[0][3].BForm = "010";
    Kmap[1][0].BForm = "100";
    Kmap[1][1].BForm = "101";
    Kmap[1][2].BForm = "111";
    Kmap[1][3].BForm = "110";
}

vector<MapElement> HighestNumberOfP(vector<MapElement> v1, vector<MapElement> v2, vector<MapElement> v3, vector<MapElement> v4, vector<MapElement> v5){
    vector<MapElement> returnv;
    int S[6];
    S[1] = v1.size();
    S[2] = v2.size();
    S[3] = v3.size();
    S[4] = v4.size();
    S[5] = v5.size();
    
    int max = -1;
    int vectorNo = 0;
    
    for (int i=1; i<=5; i++) {
        if (S[i] > max) {
            max = S[i];
            vectorNo = i;
        }
    }
    
    if (vectorNo == 1) {
        returnv = v1;
    }else if (vectorNo == 2){
        returnv = v2;
    }else if (vectorNo == 3){
        returnv = v3;
    }else if (vectorNo == 4){
        returnv = v4;
    }else if (vectorNo == 5){
        returnv = v5;
    }
    
    return returnv;
}

void findPI(){
    if(NoMinterms == 8){
        simplifiedBool = "1";
    }
    else if(NoMinterms == 0){
        simplifiedBool = "0";
    }
    else{
        for (int i=0; i<ROWS; i++) {
            for (int j=0; j<COLUMNS; j++) {
                if (Kmap[i][j].binarydigit == 1) {
                    v1.push_back(Kmap[i][j]);
                    if (Kmap[i][j+1%COLUMNS].binarydigit == 1) {
                        v2.push_back(Kmap[i][j]);
                        v2.push_back(Kmap[i][(j+1)%COLUMNS]);
                    }
                    if (Kmap[(i+1)%ROWS][j].binarydigit == 1) {
                        v3.push_back(Kmap[i][j]);
                        v3.push_back(Kmap[(i+1)%ROWS][j]);
                    }
                    if (Kmap[i][(j + 1) % COLUMNS].binarydigit == 1 && Kmap[(i + 1) % ROWS][j].binarydigit == 1 && Kmap[(i + 1) % ROWS][(j + 1) % COLUMNS].binarydigit == 1) {
                         v4.push_back(Kmap[i][j]);
                         v4.push_back(Kmap[i][(j + 1) % COLUMNS]);
                         v4.push_back(Kmap[(i + 1) % ROWS][j]);
                         v4.push_back(Kmap[(i + 1) % ROWS][(j + 1) % COLUMNS]);
                    }
                    if (Kmap[i][(j + 1) % COLUMNS].binarydigit == 1 && Kmap[i][(j + 2) % COLUMNS].binarydigit == 1 && Kmap[i][(j + 3) % COLUMNS].binarydigit == 1) {
                        v5.push_back(Kmap[i][j]);
                        v5.push_back(Kmap[i][(j + 1) % COLUMNS]);
                        v5.push_back(Kmap[i][(j + 2) % COLUMNS]);
                        v5.push_back(Kmap[i][(j + 3) % COLUMNS]);
                    }
                    MaxElements = HighestNumberOfP(v1, v2, v3, v4, v5);
                    for (int k=0 ; k<MaxElements.size(); k++) {
                        if (MaxElements[k].DForm == 0) {
                            Kmap[0][0].include = Kmap[0][0].include + 1;
                        }else if (MaxElements[k].DForm == 1){
                            Kmap[0][1].include = Kmap[0][1].include + 1;
                        }else if (MaxElements[k].DForm == 2){
                            Kmap[0][3].include = Kmap[0][3].include + 1;
                        }else if (MaxElements[k].DForm == 3){
                            Kmap[0][2].include = Kmap[0][2].include + 1;
                        }else if (MaxElements[k].DForm == 4){
                            Kmap[1][0].include = Kmap[1][0].include + 1;
                        }else if (MaxElements[k].DForm == 5){
                            Kmap[1][1].include = Kmap[1][1].include + 1;
                        }else if (MaxElements[k].DForm == 6){
                            Kmap[1][3].include = Kmap[1][3].include + 1;
                        }else if (MaxElements[k].DForm == 7){
                            Kmap[1][2].include = Kmap[1][2].include + 1;
                        }
                    }
                    int CountP = 0;
                    output x;
                    for (int z=0; z<MaxElements.size(); z++) {
                        x.minterm.push_back(MaxElements[z]);
                    }
                    x.size = MaxElements.size();
                    Implicants.push_back(x);
                    x.minterm.clear();
                    x.size = 0;
                    CountP++;
                }
                v1.clear();
                v2.clear();
                v3.clear();
                v4.clear();
                v5.clear();
            }
        }
    }
}

void includeCount(){
    findPI();
    for (int i = 0; i<Implicants.size(); i++) {
        for (int j = 0; j<Implicants[i].minterm.size(); j++) {
            if (Implicants[i].minterm[j].DForm == 0){
            Implicants[i].minterm[j].include = Kmap[0][0].include;
            }else if (Implicants[i].minterm[j].DForm == 1){
                Implicants[i].minterm[j].include = Kmap[0][1].include;
            }else if (Implicants[i].minterm[j].DForm == 2){
                Implicants[i].minterm[j].include = Kmap[0][3].include;
            }else if (Implicants[i].minterm[j].DForm == 3){
                Implicants[i].minterm[j].include = Kmap[0][2].include;
            }else if (Implicants[i].minterm[j].DForm == 4){
                Implicants[i].minterm[j].include = Kmap[1][0].include;
            }else if (Implicants[i].minterm[j].DForm == 5){
                Implicants[i].minterm[j].include = Kmap[1][1].include;
            }else if (Implicants[i].minterm[j].DForm == 6){
                Implicants[i].minterm[j].include = Kmap[1][3].include;
            }else if (Implicants[i].minterm[j].DForm == 7){
                Implicants[i].minterm[j].include = Kmap[1][2].include;
            }
        }
    }
}

void includeCountAfterRemovingDuplicates(int i)
{
    int* DecimalMinterm = new int[Implicants[i].minterm.size()];
    for (int j = 0; j < Implicants[i].minterm.size(); j++)
    {
        DecimalMinterm[j] = Implicants[i].minterm[j].DForm;
    }
    for (int k = 0; k < Implicants.size(); k++)
    {
        for (int y = 0; y < Implicants[k].minterm.size(); y++)
        {
            for (int x = 0; x < Implicants[i].minterm.size(); x++)
            {
                if (Implicants[k].minterm[y].BForm == Implicants[i].minterm[x].BForm)
                {
                    Implicants[k].minterm[y].include = Implicants[k].minterm[y].include - 1;
                }
            }
        }
    }
}

void removeDuplicates(){
    includeCount();
    int Duplicate = 0;
    
    for (int i = 0; i<Implicants.size(); i++) {
        for (int j = 1; j<Implicants.size()-1; j++) {
            for (int k = 0; k<Implicants[i].minterm.size(); k++) {
                for (int y = 0; y<Implicants[j].minterm.size(); y++) {
                    if (Implicants[i].minterm[k].BForm == Implicants[j].minterm[y].BForm) {
                        Duplicate++;
                    }
                }
                if (Duplicate == Implicants[i].minterm.size() && Implicants[i].size == Implicants[j].size) {
                    includeCountAfterRemovingDuplicates(i);
                    Implicants.erase(Implicants.begin()+i);
                }
                Duplicate = 0;
            }
        }
    }
}

void findEPI(){
    removeDuplicates();
    int repeatedMinterms;
    
    for (int i = 0; i<Implicants.size(); i++) {
        repeatedMinterms = 0;
        for (int j = 0; j<Implicants[i].minterm.size(); j++) {
            if (Implicants[i].minterm[j].include > 1) {
                repeatedMinterms++;
            }
        }
        if (repeatedMinterms == Implicants[i].size) {
            includeCountAfterRemovingDuplicates(i);
            Implicants.erase(Implicants.begin()+i);
            --i;
        }
    }
    for (int i =0 ; i<Implicants.size(); i++) {
        for (int j =0 ; j<Implicants[i].minterm.size(); j++) {
            string Bmin= Implicants[i].minterm[j].BForm;
        }
    }
}

void simplifiedBoolExp(){
    findEPI();
    
    string* letters;
    string implicant = "\"";
    for (int i = 0; i<Implicants.size(); i++) {
        NoMinterms = Implicants[i].minterm.size();
        letters = new string [Implicants[i].minterm.size()];
        for (int j = 0; j<Implicants[i].minterm.size(); j++) {
            letters[j] = Implicants[i].minterm[j].BForm;
        }
        int SameExpressionCount = 0;
        for (int k = 0; k<3; k++) {
            int x = 0;
            for (int y = 1; y<NoMinterms; y++) {
                if (letters[x][k] == letters[y][k]) {
                    SameExpressionCount++;
                }
            }
            if (SameExpressionCount == NoMinterms-1) {
                if (letters[0][k] == '0') {
                    implicant += char(k+65);
                    implicant += "'";
                }else if (letters[0][k] == '1'){
                    implicant += char(k+65);
                }
            }
            SameExpressionCount = 0;
        }
        implicant += " + ";
    }
    if(NoMinterms>0 && NoMinterms < 7){
    implicant = implicant.erase(implicant.size()-2);
    implicant += "\"";
        simplifiedBool = implicant;}
}

void PrintResults(){
    kmap();
    simplifiedBoolExp();
    cout<<"Kmap ="<<endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << Kmap[i][j].binarydigit<< "  ";
        cout << endl;
    }
    
    cout<<"F ="<<endl;
    cout << simplifiedBool << endl;
}

int main() {
    getInput();
    PrintResults();
    return 0;
}
