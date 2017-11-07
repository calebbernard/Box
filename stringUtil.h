#pragma once

#include <string>
#include <sstream>
#include <vector>
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
        arr.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arr.push_back(s);
}