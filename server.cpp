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
    ~MetaController(){
        delete c;
    }
    string unrecognizedInput(){
        return "I'm not sure how to handle that input (probably too many arguments).";
    }
    string parse(string input){
        if (input.size() > 0 && input.at(0) == '#'){
            return "Metacommand";
        } else {
            return c->parse(input);
        }
    }
};

void mainLoop(){
    MetaController c(new Startup());
    int port = 5555;
    IOInterface * io = new TcpWrapper(port);
    cout << io->description() << " live on port " << port << ".\n";
    if (!io->connected()){
        io->connect();
    }
    cout << "Connection established.\n";

    while(io->connected()){
        string input = io->input();
        cout << input << '\n';
        string output = c.parse(input);
        io->output(output);
    }
    cout << "Connection ended.\n";
    delete io;
}

int main (){
    mainLoop();
    return 0;
}