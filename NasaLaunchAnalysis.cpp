//Author: Ahmet Volkan Turan
//Date: 27 February 2025

//I have read the notes.

#include <iostream>
#include "TimeCode.h" //Includes the TimeCode class
#include <fstream> //Includes the fstream to input a file
#include <vector> //Includes vectors
#include <string> //Includes string methods

using namespace std;

vector<string> split(string str, string delim){
    vector<string> result;
    while(str.find(delim)!=string::npos){
        result.push_back(str.substr(0, str.find(delim)));
        str = str.substr(str.find(delim)+delim.length());
    }
    result.push_back(str);
    return result;
}

TimeCode parse_line(string str){
    TimeCode tc;
    vector<string> lineElements = split(str, ",");
    if(lineElements.size()<4){
        return NULL;
    }
    int colonIndex = lineElements.at(4).find(':');
    if(colonIndex != string::npos){
        string hrStr = lineElements.at(4).substr(colonIndex-2,2);
        string minStr = lineElements.at(4).substr(colonIndex+1,2);
        try{
            int hr = stoi(hrStr);
            int min = stoi(minStr);
            tc = TimeCode(hr, min, 0);
        } 
        catch(exception e){
            return NULL;
        }
    }
    return tc;
}

int main(){
    ifstream inFS;
    vector<TimeCode> times;
    int dataPoints = 0;

    inFS.open("Space_Corrected_Short.csv");
    if(!inFS.is_open()){
        cout << "Could not open file." << endl;
        return 1;
    }

    string line;
    while(!inFS.eof() && inFS.good()){
        getline(inFS, line);
        if(!inFS.fail()){
            TimeCode tc = parse_line(line);
            if(tc!=NULL){
                times.push_back(tc);
                dataPoints++;
            }
        }
    }
    if(!inFS.eof()){
        cout << "Input failure." << endl;
        return 1;
    }
    inFS.close();

    TimeCode sum;
    for(int i = 0; i<times.size(); i++){
        sum = sum + times.at(i);
    }
    TimeCode average = sum/dataPoints;
    cout << dataPoints << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}
