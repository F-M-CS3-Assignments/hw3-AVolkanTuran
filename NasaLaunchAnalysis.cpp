//Author: Ahmet Volkan Turan
//Date: 27 February 2025

//I have read the notes.

#include <iostream>
#include "TimeCode.h" //Includes the TimeCode class
#include <fstream> //Includes the fstream to input a file
#include <vector> //Includes vectors
#include <string> //Includes string methods

using namespace std;

//Splits a string into a vector<string> by the delimiter
vector<string> split(string str, string delim){
    vector<string> result;
    while(str.length()>0 && str.find(delim)!=string::npos){
        result.push_back(str.substr(0, str.find(delim)));
        str = str.substr(str.find(delim)+delim.length());
    }
    result.push_back(str);
    return result;
}

//Takes in a string, finds the time stamp, and converts it into a TimeCode object
//Invalid situations, or situations where a time stamp is not found returns -1
//Returning -1 results in returning a TimeCode with the highest possible t value due to minimum being 0
//This situation is never achieved by a 24 hour time stamp, so it is safe to use it as the error return value in this case
TimeCode parse_line(string str){
    TimeCode tc;
    vector<string> lineElements = split(str, "\"");
    if(lineElements.size()<2){
        return -1;
    }
    size_t colonIndex = lineElements.at(1).find(':');
    if(colonIndex != string::npos){
        string hrStr = lineElements.at(1).substr(colonIndex-2,2);
        string minStr = lineElements.at(1).substr(colonIndex+1,2);
        try{
            int hr = stoi(hrStr);
            int min = stoi(minStr);
            tc = TimeCode(hr, min, 0);
        } 
        catch(const exception& e){
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return tc;
}

//Main function open the file to read the data from and calculates the average of the time stamps
//It also uses the helper function parse_line to read through the file and collect the TimeCode
int main(){
    ifstream inFS;
    vector<TimeCode> times;
    int dataPoints = 0;

    inFS.open("Space_Corrected.csv");
    if(!inFS.is_open()){
        cout << "Could not open file." << endl;
        return 1;
    }

    string line;
    while(!inFS.eof() && inFS.good()){
        getline(inFS, line);
        if(!inFS.fail()){
            TimeCode tc = parse_line(line);
            if(tc!=-1){
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
    for(unsigned int i = 0; i<times.size(); i++){
        sum = sum + times.at(i);
    }
    TimeCode average = sum/dataPoints;
    cout << dataPoints << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}
