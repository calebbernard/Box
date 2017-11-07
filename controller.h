#include <string>
#include <vector>
#include "stringUtil.h"
using namespace std;

class Controller{
public:
    virtual string blank()=0;
};

class TutorialSuccess : public Controller {
public:
    string blank() {
        string msg = pull();
        return msg;
    }
    string pull(){
        string msg = "Ultimate Success!";
        return msg;
    }
};

class Tutorial : public Controller {
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
};

class Intro : public Controller {
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
};