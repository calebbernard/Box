#include "lobbyModule.h"
#include "mabModule.h"

using namespace std;

    lobby::lobby(){
        changeModule = 0;
        addCommand("?", "Instructions for this room", "", "");
        addCommand("start", "Loads a module", "string", "name of the module you want to load.");
        addCommand("start", "Lists the modules you can select", "", "");
    }

    string lobby::start(string module){
        string output = "";
        if (module == "mab"){
            changeModule = new mabModule();
            output = "Loading multi-armed bandit module.";
        } else {
            output = "Module not found.";
        }
        return output;
    }

    string lobby::start(){
        string output = "mab - Multi-armed bandit";
        return output;
    }
    
    string lobby::instructions(){
        string output = "This is the lobby, where you can select which module you want to load.\n";
        return output;
    }

    string lobby::runCommand(vector<string> words, int arity){
        string output = "Error processing command...";
        if (words[0] == "?" && arity == 0){
            output = instructions();
        } else if (words[0] == "start" && arity == 0){
            output = start();
        } else if (words[0] == "start" && arity == 1){
            output = start(words[1]);
        }
        return output;
    }