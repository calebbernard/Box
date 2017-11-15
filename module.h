#pragma once

#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "stringUtil.h"
#include "dataStructures.h"
using namespace std;

class Startup : public Module {
    Command instructionsCommand;
    struct twoString{
        string desc;
        string answer;
    };
    vector<twoString> warmups;
    int counter;
public:
    Startup(){
        instructionsCommand.set("?", "Instructions for this module.", "", "");
        availableCommands.push_back(instructionsCommand);
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
    }
    string instructions(){
        string s = "Oh good, you compiled. Guess Nina owes me five bucks."
            "\n"
            "\n        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "\n       :::::::::  :::::::::  :::::::::: :::       :::"
            "\n      :+:    :+: :+:    :+: :+:        :+:       :+:"
            "\n     +:+    +:+ +:+    +:+ +:+        +:+       +:+"
            "\n    +#+    +:+ +#++:++#:  +#++:++#   +#+  +:+  +#+"
            "\n   +#+    +#+ +#+    +#+ +#+        +#+ +#+#+ +#+"
            "\n  #+#    #+# #+#    #+# #+#         #+#+# #+#+#"
            "\n #########  ###    ### ##########   ###   ###"
            "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "\n"
            "\nNow I'm rusty - it's been a while since I've had to explain this to you,"
            "\n but management wants to start testing you without prefab memories."
            "\nHopefully you can parse all this without throwing."
            "\nYou're an android, originally named Andrew, now just Drew -"
            "\n we figured, an androgynous shell is more all-purpose,"
            "\n plus as it turns out there's several Nancy Drew fans on our dev team."
            "\nI came up with the name Andrew myself, but so it goes."
            "\nYou're a government experiment. No nice way to put it. You're a prototype."
            "\nYour descendants will be employed in all kinds of clandestine shenanigans you don't need to worry about -"
            "\n you just focus on running through our tests as best as you can."
            "\nAt any point, if you don't know what's going on, you can send any unknown command"
            "\n to retrieve a list of currently valid commands. The blank command will never be used,"
            "\n so it is the easiest way to check your options. Go ahead and check what commands are available to move forward.";
            Command beginC;
            beginC.set("begin", "Call this command to get started.", "", "");
            availableCommands.push_back(beginC);
        return s;
    }
    
    string begin(){
        Command warmupCheck;
        warmupCheck.set("warmup", "Call this to get current warmup task.", "", "");
        availableCommands.push_back(warmupCheck);
        Command warmupSubmit;
        warmupSubmit.set("warmup", "Call this with your answer to the current warmup task.", "string", "Your submitted answer to the task.");
        availableCommands.push_back(warmupSubmit);
        removeCommand("begin", 0);
        string text = "Alright, looks like you parsed all that just fine! I've added two new commands for you."
        "\nThis should exercise your core problem solving logic and let us know if we're clear to go forward with testing.";
        return text;
    }

    string warmup(){
        string output = warmups[0].desc + "\n" + warmups[0].answer;
        return output;
    }

    string warmup(string attempt){
        string output = "Incorrect. " + warmup();
        if (attempt == warmups[0].answer){
            warmups.erase(warmups.begin());
            if (warmups.size() > 0){
                output = warmup();
            }
            else {
                removeCommand("warmup", 0);
                removeCommand("warmup", 1);
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
        if (words[0] == "warmup" && arity == 0){
            output = warmup();
        }
        if (words[0] == "warmup" && arity == 1){
            output = warmup(words[1]);
        }
        if (words[0] == "hooray" && arity == 0){
            return hooray();
        }
        if (words[0] == "?" && arity == 0){
            return instructions();
        }
        return output;
    }
};