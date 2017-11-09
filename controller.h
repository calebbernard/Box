#pragma once

#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "stringUtil.h"
#include "dataStructures.h"
using namespace std;




//class

class Startup : public Controller {
    Command testCommand;
public:
    Startup(){
        testCommand.set("begin", "Call this command to get started.", "", "");
        availableCommands.push_back(testCommand);
        changeController = 0;
        instructions();
    }
    string instructions(){
        return "Hello! This is the startup module. We'll run through some calibration challenges so you can get the hang of it.";
    }
    
    
    string blankTest(){
        return "hey!";
    }

    string runCommand(vector<string> words, Command c){
        return blankTest();
    }
};