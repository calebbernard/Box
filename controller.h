#include <string>
#include <vector>
#include "stringUtil.h"
using namespace std;

class Controller{
public:
    virtual string instructions()=0;
    virtual string invalidInput(){
        return "Invalid input.";
    }
    virtual string parse(string request)=0;
};

class Startup : public Controller {
    vector<string> tutorialText;
    bool blankTest;
    bool arity0Test;
    int instructionState;
public:
    Startup(){
        instructionState = 0;
        tutorialText.push_back("Oh good, you compiled.");
        tutorialText.push_back("A quick calibration if you don't mind. Send a blank signal.");
        tutorialText.push_back("Good. Now send:\nABC123");
    }
    string instructions(){
        string reply = tutorialText[instructionState % tutorialText.size()];
        instructionState++;
        return reply;
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
                    output = invalidInput();
                }
                break;
            case 2: // Arity 1
                output = invalidInput();
                break;
            default:
                output = invalidInput();
                break;
        }
        return output;
    }
};

class TutorialSuccess : public Controller {
public:
    string instructions() {
        string msg = pull();
        return msg;
    }
    string parse(string request){
        string output;
        vector<string> words;
        splitString(request, words, " ");
        cout << words.size() << '\n';
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