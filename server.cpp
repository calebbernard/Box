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
            if (input == "#QUIT" || input == "#quit"){
                return "#####EXIT#####";
            }
        } else {
            return c->parse(input);
        }
    }
};

void mainLoop(int port){
    MetaController c(new Startup());
    IOInterface *io = new TcpWrapper(port);

    cout << io->description() << " live on port " << port << ".\n";
    //cout << "Preface messages with 5-digit message length string.\nExample: 00012Hello World!\n";
    if (!io->connected()){
        io->connect();
        cout << "Connection established.\n";
    }
    while(io->connected()){
        string input = io->input();
        string output = c.parse(input);
        if (output == "#####EXIT#####"){
            break;
        }
        io->output(output);
    }
    cout << "Connection ended.\n"; // this point isn't being reached
    delete io;
}

int main (int argc, char** argv){
    string gameName = "Box";
    int port;
    if (argc != 2){
        cout << "Welcome to " << gameName << "!\n";
        cout << "This game is played over TCP on your local machine.\n";
        cout << "Please preface each message with a 5-character string specifying the length in bytes of the remaining message.\n";
        cout << "For example:\n";
        cout << "00012Hello World!\n";
        cout << "To begin the game, call it with the port you want it to listen on as an argument.\n";
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
            mainLoop(port);
        } else {
            cout << "Port must be an integer from 0-65535.\n";
            return 0;
        }
        return 0;
    }
    mainLoop(port);
    return 0;
}