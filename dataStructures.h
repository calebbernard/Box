#pragma once

#include <string>
#include <vector>
#include "stringUtil.h"
using namespace std;

class Argument{
public:
    string type; // this should become an enum
    string description;
};

class Command{
public:
    string keyword;
    string description;
    vector<Argument> argument;
    void set(string keyword_, string description_, string argTypes_, string argDescriptions_);
    string describe();
};

class Module{
public:
    Module * changeModule;
    vector<Command> availableCommands;
    virtual string instructions()=0;
    virtual string runCommand(vector<string> words, int arity)=0;
    virtual string invalidInput(bool blankString);
    virtual string parse(string request);
    virtual void addCommand(string keyword, string description, string argTypes, string argDescriptions);
    virtual void removeCommand(string keyword_, int arity_);
};