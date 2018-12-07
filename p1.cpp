#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <vector>

using namespace std;

int main() {
    ifstream inFile;
    int num = 0;
    int virtual_address;
    int physical_address;
    int bytes;

    inFile.open("test.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    if (inFile >> num){
		virtual_address = num;
		if (inFile >> num){
			physical_address = num;
			if(inFile >> num){
				bytes = num;
			}
		}
		
	}

	vector<int> row;
    while(inFile >> num){
    	row.push_back(num);
    }

    vector<int> valid;
    vector<int> permission;
    vector<int> pgNum;
    vector<int> useBit;
    for(int i = 0; i < row.size(); i++){
    	//printf("%i ", row[i]);
    	if( i % 4 == 0){
    		valid.push_back(row[i]);
    	} 
    	if(i % 4 == 1){
    		permission.push_back(row[i]);
    	}
    	if(i % 4 == 2){
    		pgNum.push_back(row[i]);
    	}
    	if (i % 4 == 3){
    		useBit.push_back(row[i]);
    	}
    }
   
    inFile.close();
    return 0;
}
