#include <string>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "io.h"
#include "stringUtil.h"
#include "startupModule.h"
#include "dataStructures.h"
using namespace std;



// MetaController should handle universal commands and pass everything else to the current controller.
class MetaModule{
    Module * m;
    bool startup;
public:
    MetaModule(Module * m_){
        m = m_;
        startup = true;
    }
    ~MetaModule(){
        delete m;
    }
    string unrecognizedInput(){
        return "I'm not sure how to handle that input (probably too many arguments).";
    }
    string parse(string input){
        string output = "ERROR";
        if (startup){
            startup = false;
            if (input != "?"){
                output = "Please send a question mark to get started.";
            }
        }
        if (input.size() > 0 && input.at(0) == '#'){
            output = "metacommand";
        } else {
            output = m->parse(input);
        }
        if (m->changeModule != 0){
            m = m->changeModule;
        }
        return output;
    }
};

void mainLoop(int port){
    srand(time(0));
    MetaModule m(new Startup());
    IOInterface *io = new TcpWrapper(port);
    string greeting = io->description() + " live on port " + itos(port);
    string dashes = "";
    for (int x = 0; x < greeting.length(); x++){
        dashes += "-";
    }
    cout << greeting << endl << dashes << endl;
    if (!io->connected()){
        io->connect();
    }
    while(io->connected()){
        io->output(m.parse(io->input()));        
    }
    delete io;
}

int main (int argc, char** argv){
    string gameName = "Box";
    int port;
    if (argc != 2){
        cout << "Welcome to " << gameName << "!\n";
        cout << "This game is played over TCP on your local machine.\n";
        cout << "Please preface each ASCII message with a 5-character string specifying the length in bytes of the remaining message.\n";
        cout << "For example:\n";
        cout << "00012Hello World!\n";
        cout << "To begin, call me with the port you want it to listen on as an argument.\n";
        return 0;
    } else {
        string arg = "";
        int port = 0;
        int x = 0;
        while (argv[1][x] != '\0'){
            arg += argv[1][x];
            x++;
        }
        for (int x = 0; x < arg.length(); x++){
            if (arg.at(x) >= '0' && arg.at(x) <= '9'){
                port *= 10;
                port += arg.at(x) - '0';
            } else {
                cout << "Port must be an integer from 0-65535.\n";
                return 0;
            }
        }
        if (port >= 0 && port <= 65535){
            try{
                mainLoop(port);
            }
            catch (int e){
                return 0;
            }
        } else {
            cout << "Port must be an integer from 0-65535.\n";
            return 0;
        }
        return 0;
    }
    mainLoop(port);
    return 0;
}