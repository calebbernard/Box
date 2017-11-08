#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

string itos(int i){
    stringstream ss;
    ss << i;
    return ss.str();
}

void splitString(string s, vector<string> &arr, string delimiter){
    int pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != -1) {
        token = s.substr(0, pos);
        //cout << token << " ";
        arr.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    //cout << token << endl;
    arr.push_back(s);
}