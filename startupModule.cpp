#include "startupModule.h"
#include "lobbyModule.h"


using namespace std;

    Startup::Startup(){
        onceBegin = false;
        addCommand("?", "Instructions for this module.", "", "");
        changeModule = 0;
        twoString first;
        first.desc = "First, echo this static string: every time it will be the same.";
        first.answer = "ABC123";
        warmups.push_back(first);
        string dynCheck = "";
        for (int x = 0; x < 3; x++){
            dynCheck += (char)(rand() % 26 + 65);
        }
        for (int x = 0; x < 3; x++){
            dynCheck += (char)(rand() % 10 + 48);
        }
        twoString second;
        second.desc = "Now try this dynamic string: it will change every execution. No more hardcoding!";
        second.answer = dynCheck;
        warmups.push_back(second);
        int iterations = rand() % 200 + 100;
        for (int x = 0; x < iterations; x++){
            twoString bulk;
            bulk.desc = "Now a bulk test: a series of 100-300 randomly generated 6-character strings."
                "\nAfter this stream, the last echo challenge will say \"END\".";
            dynCheck = "";
            for (int y = 0; y < 6; y ++){
                int charType = rand() % 2;
                if (charType == 0){
                    dynCheck += (char)(rand() % 10 + 48);
                } else if (charType == 1){
                    dynCheck += (char)(rand() % 26 + 65);
                }
            }
            bulk.answer = dynCheck;
            warmups.push_back(bulk);
        }
        twoString end;
        end.desc = "Now a bulk test: a series of 100-300 randomly generated 6-character strings."
                "\nAfter this stream, the last echo challenge will say \"END\".";
        end.answer = "END";
        warmups.push_back(end);
    }
    string Startup::instructions(){
        string s = "Welcome to the puzzle box!"
            "\nAt any point, if you don't know what's going on, you can send any unknown command"
            "\n to retrieve a list of currently valid commands. The blank command will never be used,"
            "\n so it is the easiest way to check your options. Go ahead and check what commands are available to move forward.";
            if (!onceBegin){
                onceBegin = true;
                addCommand("begin", "Call this command to get started.", "", "");
            }  
        return s;
    }
    
    string Startup::begin(){
        addCommand("warmup", "Call this to get current warmup task.", "", "");
        addCommand("warmup", "Call this with your answer to the current warmup task.", "string", "Your submitted answer to the task.");
        removeCommand("begin", 0);
        string text = "Good work. I've added two new commands for you."
        "\nThis easy challenge will hopefully give you the opportunity to get the feel of interacting with the puzzle box.";
        return text;
    }

    string Startup::warmup(){
        string output = warmups[0].desc + "\n" + warmups[0].answer;
        return output;
    }

    string Startup::warmup(string attempt){
        string output = "Incorrect. " + warmup();
        if (attempt == warmups[0].answer){
            warmups.erase(warmups.begin());
            if (warmups.size() > 0){
                output = warmup();
            }
            else {
                removeCommand("warmup", 0);
                removeCommand("warmup", 1);
                addCommand("continue", "transports you to the testing zone", "", "");
                output = "You passed the warmups with flying colors! A new command has been added."
                    "\nOnce you select it, we will take you to a puzzle module where we can begin in earnest.";
            }
        }
        return output;
    }

    string Startup::finish(){
        string output = "MOVING TO MODULE 1\n";
        changeModule = new lobby();
        return output;
    }

    string Startup::runCommand(vector<string> words, int arity){
        string output = "Error processing command...";
        if (words[0] == "begin" && arity == 0){
            output = begin();
        } else if (words[0] == "warmup" && arity == 0){
            output = warmup();
        } else if (words[0] == "warmup" && arity == 1){
            output = warmup(words[1]);
        } else if (words[0] == "continue" && arity == 0){
            output = finish();
        } else if (words[0] == "?" && arity == 0){
            output = instructions();
        }
        return output;
    }