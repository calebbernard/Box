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
    void set(string keyword_ = "", string description_ = "No description has been entered for this command.", string argTypes_= "", string argDescriptions_ = ""){
        keyword = keyword_;
        description = description_;
        vector<string> argTypes;
        vector<string> argDescriptions;
        if (argTypes_ != ""){
            splitString(argTypes_, argTypes, " ");
        }
        if (argDescriptions_ != ""){
            splitString(argDescriptions_, argDescriptions, "~");
        }
        if (argTypes.size() != argDescriptions.size()){
            cout << "Internal error - Bad command initialization.\n";
            throw(0);
        }
        for (int x = 0; x < argTypes.size(); x++){
            Argument temp;
            temp.type = argTypes[x];
            temp.description = argDescriptions[x];
            argument.push_back(temp);
        }
    }
    string describe(){
        int counter = 0;
        string pluralize = "";
        string output = keyword + " - " + description;
        output += "\n" + keyword + " takes " + itos(argument.size()) + " arguments.";
        for (int x = 0; x < argument.size(); x++){
            output += "\n\t" + itos(x+1) + ". " + argument[x].type + " - " + argument[x].description;
        }
        return output;
    }
};

class Module{
public:
    Module * changeModule;
    vector<Command> availableCommands;
    virtual string instructions()=0;
    virtual string invalidInput(){
        string output = "Invalid command. Current options:";
        string pluralize = "";
        for (int x = 0; x < availableCommands.size(); x++){
            if (availableCommands[x].argument.size() != 1){
                pluralize = "s";
            } else {
                pluralize = "";
            }
            output += "\n\t" + itos(x) + ". " + availableCommands[x].keyword + " (" + itos(availableCommands[x].argument.size()) + " argument" + pluralize + ")";
        }
        output += "\nFor more instructions about a particular command on this list, type \"[command name] [# of args]?\"";
        return output;
    }
    virtual string parse(string request){
        string output = invalidInput();
        vector<string> words;
        splitString(request, words, " ");
        bool foundMatch = 0;
        if (words[0] == ""){
            return invalidInput();
        }
        if (words.size() == 2 && words[1].substr(words[1].length()-1, words[1].length()) == "?" && isNum(words[1].substr(0, words[1].length()-1))){
            for (int x = 0; x < availableCommands.size(); x++){
                if ((words[0] == availableCommands[x].keyword) && (strtoi(words[1].substr(0,words[1].length()-1)) == availableCommands[x].argument.size())){
                    output = availableCommands[x].describe();
                }
            }
        }
        else {
            for (int x = 0; x < availableCommands.size(); x++){
                if (words[0] == availableCommands[x].keyword){
                    if (words.size() - 1 == availableCommands[x].argument.size()){
                        output = runCommand(words, words.size() - 1);
                    }
                }
            }
        }
        return output;
    }
    virtual string runCommand(vector<string> words, int arity)=0;
    virtual void removeCommand(string keyword_, int arity_){
        for (int x = 0; x < availableCommands.size(); x++){
            if (keyword_ == availableCommands[x].keyword && arity_ == availableCommands[x].argument.size()){
                availableCommands.erase(availableCommands.begin() + x);
            }
        }
    }
};