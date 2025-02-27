//Author: Ahmet Volkan Turan
//Date: 14 February 2025

//I have read the notes.

#include <iostream> //enables cout/cin
#include <string> //enables string methods
#include "TimeCode.h" //includes the method declarations

using namespace std;

//Constructs a TimeCode Object by converting the components into seconds
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
    t = ComponentsToSeconds(hr, min, sec);
}

//Copy constructor
TimeCode::TimeCode(const TimeCode& tc){
    t = tc.GetTimeCodeAsSeconds();
}

//Resets the time to 0
void TimeCode::reset(){
    t=0;
}

//Changes the number of hours in the TimeCode object
void TimeCode::SetHours(unsigned int hours){
    t = ComponentsToSeconds(hours, GetMinutes(), GetSeconds());
}

//Changes the number of minutes in the TimeCode object and makes sure the input is not out of bounds
void TimeCode::SetMinutes(unsigned int minutes){
    if(minutes>=60){
        throw invalid_argument("Invalid input. Minutes has to be less than 60.");
    }
    else{
        t = ComponentsToSeconds(GetHours(), minutes, GetSeconds());
    }
}

//Changes the number of seconds in the TimeCode object and makes sure the input is not out of bounds
void TimeCode::SetSeconds(unsigned int seconds){
    if(seconds>=60){
        throw invalid_argument("Invalid input. Seconds has to be less than 60.");
    }
    else{
        t = ComponentsToSeconds(GetHours(), GetMinutes(), seconds);
    }
}

//Returns the number of hours
unsigned int TimeCode::GetHours() const{
    return t/3600;
}

//Returns the number of minutes
unsigned int TimeCode::GetMinutes() const{
    return (t/60)%60;
}

//Returns the number of seconds
unsigned int TimeCode::GetSeconds() const{
    return t%60;
}

//Assigns the components of the TimeCode object to the inputs
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
    hr = GetHours();
    min = GetMinutes();
    sec = GetSeconds();
}

//Converts the components to seconds
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    return hr*3600+min*60+sec;
}

//Returns a string representation of the TimeCode object
string TimeCode::ToString() const{
    unsigned int h,m,s;
    GetComponents(h,m,s);
    string output = to_string(h) + ":" + to_string(m) + ":" + to_string(s);
    return output;
}

//Changes the + operator to add two TimeCode objects
TimeCode TimeCode::operator+(const TimeCode& other) const{
    TimeCode tc = TimeCode(GetHours()+other.GetHours(),GetMinutes()+other.GetMinutes(),GetSeconds()+other.GetSeconds());
    return tc;
}

//Changes the - operator to subtract two TimeCode objects, makes sure the result is also a valid TimeCode object
TimeCode TimeCode::operator-(const TimeCode& other) const{
    if(*this<other){
        throw invalid_argument("Negative arguments not allowed");
    }
    TimeCode tc = TimeCode(GetHours()-other.GetHours(),GetMinutes()-other.GetMinutes(),GetSeconds()-other.GetSeconds());
    return tc;
}

//Changes the * operator to multiply a TimeCode object by a double, and makes sure the result is a valid TimeCode object
TimeCode TimeCode::operator*(double a) const{
    if(a<0){
        throw invalid_argument("Can't multiply by a negative number.");
    }
    long long unsigned int newt = static_cast<int>(GetTimeCodeAsSeconds()*a);
    TimeCode tc = TimeCode(newt/3600, (newt/60)%60, newt%60);
    return tc;
}

//Changes the / operator to divide a TimeCode object by a double, and makes sure the result is a valid TimeCode object
TimeCode TimeCode::operator/(double a) const{
    if(a<=0){
        throw invalid_argument("Can't divide by a negative number.");
    }
    if(a==0){
        throw invalid_argument("Can't divide by 0");
    }
    long long unsigned int newt = static_cast<int>(GetTimeCodeAsSeconds()/a);
    TimeCode tc = TimeCode(newt/3600, (newt/60)%60, newt%60);
    return tc;
}

//Changes the == operator to compare two TimeCode objects
bool TimeCode::operator == (const TimeCode& other) const{
    if(GetTimeCodeAsSeconds()==other.GetTimeCodeAsSeconds()){
        return true;
    }
    return false;
}

//Changes the != operator to compare two TimeCode objects
bool TimeCode::operator != (const TimeCode& other) const{
    return !(*this==other);
}

//Changes the < operator to compare two TimeCode objects
bool TimeCode::operator < (const TimeCode& other) const{
    if(GetTimeCodeAsSeconds()<other.GetTimeCodeAsSeconds()){
        return true;
    }
    return false;
}

//Changes the <= operator to compare two TimeCode objects
bool TimeCode::operator <= (const TimeCode& other) const{
    return (*this==other) || (*this<other);
}

//Changes the > operator to compare two TimeCode objects
bool TimeCode::operator > (const TimeCode& other) const{
    return !(*this<=other);
}

//Changes the >= operator to compare two TimeCode objects
bool TimeCode::operator >= (const TimeCode& other) const{
    return !(*this<other);
}