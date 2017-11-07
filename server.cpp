#include <string>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
#include "io.h"
#include "stringUtil.h"
#include "controller.h"
using namespace std;



// MetaController should handle meta commands (like the #commands) as well as interface-enforced commands, and pass everything else to the subcontroller.
class MetaController{
    Controller * c;
public:
    MetaController(Controller * c_){
        c = c_;
    }
    string blank(){
        return "no arguments";
    }
    string single(){
        return "One argument";
    }
    string notBlank(){
        return "some arguments";
    }
    string parse(string request){
        string output;
        vector<string> words;
        splitString(request, words, " ");
        cout << words.size() << '\n';
        switch (words.size()){
            case 1:
                if (words[0] == ""){
                    output = blank();
                } else {
                    output = single();
                }
                break;
            default:
                output = notBlank();
                break;
        }
        return output;
    }
};

void mainLoop(){
    MetaController c;
    int port = 5555;
    IOInterface * io = new ZmqWrapper(port);
    cout << "Server live on port " << port << ".\n";
    while(true){
        string input = io->input();
        string output = c.parse(input);
        io->output(output);
    }
    delete io;
}

int main (){
    mainLoop();
    return 0;
}