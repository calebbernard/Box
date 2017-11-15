#pragma once

#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "stringUtil.h"
#include "dataStructures.h"
using namespace std;




//class

class Startup : public Module {
    Command instructions;
    Command testCommand;
    vector<string> calibrations;
    int counter;
public:
    Startup(){
        instructions.set("?", "Instructions for this module.", "", "")
        testCommand.set("begin", "Call this command to get started.", "", "");
        availableCommands.push_back(testCommand);
        changeController = 0;

        calibrations.push_back("ABC123");
        string dynCheck = "";
        for (int x = 0; x < 3; x++){
            dynCheck += (char)(rand() % 26 + 65);
        }
        for (int x = 0; x < 3; x++){
            dynCheck += (char)(rand() % 10 + 48);
        }
        calibrations.push_back(dynCheck);
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
        removeCommand("begin", 0);
        return "neato";
    }

    string calibrate(){
        string output = "Please send:\n" + calibrations[0];
        return output;
    }

    string calibrate(string attempt){
        string output = "Incorrect. " + calibrate();
        if (attempt == calibrations[0]){
            calibrations.erase(calibrations.begin());
            if (calibrations.size() > 0){
                output = "Good work! " + calibrate();
            }
            else {
                removeCommand("calibrate", 0);
                removeCommand("calibrate", 1);
                Command patOnTheBack;
                patOnTheBack.set("hooray", "a command to congratulate you on your success!", "", "");
                availableCommands.push_back(patOnTheBack);
                output = "";
            }
        }
        return output;
    }

    string hooray(){
        return "You are a champ!";
    }

    string runCommand(vector<string> words, int arity){
        string output = "Error processing command...";
        if (words[0] == "begin" && arity == 0){
            output = begin();
        }
        if (words[0] == "calibrate" && arity == 0){
            output = calibrate();
        }
        if (words[0] == "calibrate" && arity == 1){
            output = calibrate(words[1]);
        }
        if (words[0] == "hooray" && arity == 0){
            return hooray();
        }
        return output;
    }
};