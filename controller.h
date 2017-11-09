#pragma once

#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "stringUtil.h"
using namespace std;

class Controller{
public:
    Controller * changeController;
    virtual string instructions()=0;
    virtual string invalidInput(){
        return "Invalid input.";
    }
    virtual string parse(string request)=0;
};

class TutorialSuccess : public Controller {
public:
    TutorialSuccess(){
        changeController = 0;
    }
    string instructions() {
        string msg = pull();
        return msg;
    }
    string parse(string request){
        string output;
        vector<string> words;
        splitString(request, words, " ");
        //cout << words.size() << '\n';
        switch (words.size()){
            case 1:
                if (words[0] == ""){ // Blank
                    output = instructions();
                }
                else { // Arity 0
                    if (words[0] == "a"){
                        output = a();
                    } else if (words[0] == "b"){
                        output = b();
                    } else {
                        output = invalidInput();
                    }
                }
                break;
            case 2: // Arity 1
                if (words[0] == "a"){
                    output = a1(words[1]);
                } else if (words[0] == "b"){
                    output = b1(words[1]);
                }
                break;
            default:
                output = invalidInput();
                break;
        }
        return output;
    }
    string a(){
        return "a";
    }
    string b(){
        return "b";
    }
    string a1(string arg){
        return "a - " + arg;
    }
    string b1(string arg){
        return "b - " + arg;
    }
    string pull(){
        string msg = "Ultimate Success!";
        return msg;
    }
};


//class

class Startup : public Controller {
    vector<string> tutorialText;
    bool firstMessage;
    bool blankTest;
    bool arity0Test;
    int instructionState;
    bool loopInstructions;
    string dynCheck;
public:
    Startup(){
        firstMessage = true;
        loopInstructions = false;
        changeController = 0;
        instructionState = 0;
        dynCheck = "";
        tutorialText.push_back("Blank message calibration: Send \"\"");
        tutorialText.push_back("Static message calibration: send \"ABC123\"");
    }
    string instructions(){
        if (instructionState == tutorialText.size() && loopInstructions == false){
            return "Please finish the startup challenges.";
        }
        string reply = tutorialText[instructionState % tutorialText.size()];
        instructionState++;
        return reply;
    }
    string parse(string request){
        // this sort of "once" thing should be generalized, all of this should be generalized really
        if (firstMessage == true){
            firstMessage = false;
            return instructions();
        }
        string output;
        vector<string> words;
        splitString(request, words, " ");
        switch (words.size()){
            case 1:
                if (words[0] == "" || words[0].at(0) == '\0'){ // Blank
                    output = instructions();
                }
                else { // Arity 0
                    if (words[0] == dynCheck){
                        output = "Calibration complete!\nFrom here on out, sending blank messages will get instructions for a challenge.";
                        changeController = new TutorialSuccess();
                    }
                    else if(words[0] == "ABC123"){
                        if (instructionState == 2){
                            if (!arity0Test){
                                arity0Test = true;
                                for (int x = 0; x < 3; x++){
                                    dynCheck += (char)(rand() % 26 + 65);
                                }
                                for (int x = 0; x < 3; x++){
                                    dynCheck += (char)(rand() % 10 + 48);
                                }
                                // all of this code is incredibly terrible but I'm just figuring out what sort of things I'll want in generalized code for now.
                                string nextMessage = "Random message calibration: send \"" + dynCheck + "\"";
                                tutorialText.push_back(nextMessage);
                                output = instructions();
                                //changeController = new TutorialSuccess();
                                //return output;
                            } else {
                                output = "You already completed the static challenge.";
                            }
                        }
                        else {
                            output = invalidInput();
                        }
                        
                        
                    }
                    else {
                        output = invalidInput();
                    }
                }
                break;
            case 2: // Arity 1
                output = invalidInput();
                break;
            default:
                output = invalidInput(); // instead of manually setting invalidInput we should set it once at the end if output is an empty string.
                break;
        }
        return output;
    }
};



class Tutorial {
    int counter;
    vector<string> tutorialText;
public:
    Tutorial(){
        counter = 0;
        tutorialText.push_back("Hello! Please send a blank message to begin.");
        tutorialText.push_back("Nice work! Send another blank message.");
        tutorialText.push_back("Now echo this code: \'ABCDE\'");
    }
    string pull(){
        string reply = tutorialText[counter % tutorialText.size()];
        counter ++;
        return reply;
    }
    string blank(){
        string msg = pull();
        return msg;
    }
    string arity0(string command){
        return "";
    }
    string arity1(string command, string arg1){
        return "";
    }
};

class Intro {
    int a, b, c;
public:
    Intro(){
        a = 1; b = 1; c = 1;
    }
    string get_a(){
        //cout << "a: " << a << endl;
        b = (b + 3) % 5;
        return itos(a);
    }
    string get_b(){
        //cout << "b: " << b << endl;
        c = (c + 5) % 7;
        return itos(b);
    }
    string get_c(){
        //cout << "c: " << c << endl;
        a = (a + 7) % 11;
        return itos(c);
    }
    string get(string var){
        //cout << var << endl;
        if (var == "a"){
            return get_a();
        }
        else if (var == "b"){
            return get_b();
        }
        else if (var == "c"){
            return get_c();
        }
        else {
            return "";
        }
    }
    string get_success(){
        if (a == 1 && b == 2 && c == 3){
            return "true";
        } 
        else {
            return "false";
        }
    }
    string blank(){
        string msg = "Blank! What can ya do.";
        return msg;
    }
    string arity0(string command){
        return "";
    }
    string arity1(string command, string arg1){
        return "";            
    }
};