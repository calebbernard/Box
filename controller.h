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
    
    
    string begin(){
        Command calibrateCheck;
        calibrateCheck.set("calibrate", "Call this to get current calibration task.", "", "");
        availableCommands.push_back(calibrateCheck);
        Command calibrateSubmit;
        calibrateSubmit.set("calibrate", "Call this with your answer to the current calibration task.", "string", "Your submitted answer to the task.");
        availableCommands.push_back(calibrateSubmit);
        Command test;
        test.set("test", "test command", "int", "test int");
        availableCommands.push_back(test);
        removeCommand(testCommand);
        return "neato";
    }

    string runCommand(vector<string> words, int arity){
        string output = "Error processing command...";
        if (words[0] == "begin" && arity == 0){
            output = begin();
        }
        return output;
    }
};