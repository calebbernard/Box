#pragma once

#include <string>
#include <vector>
#include "stringUtil.h"
using namespace std;

class Argument{
public:
    string type;
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
        string output = keyword + " - " + description;
        output += "\n" + keyword + " takes " + itos(argument.size()) + " arguments.";
        for (int x = 0; x < argument.size(); x++){
            output += "\n\t" + itos(x+1) + ". " + argument[x].type + " - " + argument[x].description;
        }
        return output;
    }
};

class Controller{
public:
    Controller * changeController;
    vector<Command> availableCommands;
    virtual string instructions()=0;
    virtual string invalidInput(){
        string output = "Invalid command. Current options:";
        for (int x = 0; x < availableCommands.size(); x++){
            output += "\n\t" + itos(x) + ". " + availableCommands[x].keyword;
        }
        output += "\n For more instructions about a particular command on this list, type its name followed by a question mark.";
        return output;
    }
    virtual string parse(string request){
        string output = invalidInput();
        vector<string> words;
        splitString(request, words, " ");
        bool foundMatch = 0;
        for (int x = 0; x < availableCommands.size(); x++){
            if (words[0].substr(words[0].length() - 1, words[0].length()) == "?"){
                if (words[0].substr(0, words[0].length() - 1) == availableCommands[x].keyword){
                    output = availableCommands[x].describe();
                    break;
                }
            }
            if (words[0] == availableCommands[x].keyword){
                //cout << words.size() << " - " << availableCommands[x].argument.size() << '\n';
                if (words.size() - 1 == availableCommands[x].argument.size()){
                    output = runCommand(words, availableCommands[x]);
                }
            }
        }
        return output;
    }
    virtual string runCommand(vector<string> words, Command c)=0;
};