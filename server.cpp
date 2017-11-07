#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
using namespace std;

string itos(int i){
    //cout << i << endl;
    stringstream ss;
    ss << i;
    //cout << ss.str() << endl;
    return ss.str();
}

class IOInterface{
public:
    virtual string input()=0;
    virtual void output(string msg)=0;
};

class zmqWrapper : public IOInterface{
private:
    zmq::context_t context;
    zmq::socket_t socket;
public:
    zmqWrapper(int port) : context(1), socket(context, ZMQ_REP){
        socket.bind("tcp://*:" + itos(port));
    }
    string input(){
        zmq::message_t request;
        socket.recv(&request);
        string msg = string(static_cast<char*>(request.data()), request.size());
        return msg;
    }
    void output(string msg){
        zmq::message_t reply(msg.length());
        memcpy (reply.data(), msg.c_str(), msg.length());
        socket.send(reply);
    }
};

void splitString(string s, vector<string> &arr, string delimiter){
    int pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != -1) {
        token = s.substr(0, pos);
        arr.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arr.push_back(s);
}

class tutorial{
    int counter;
    vector<string> tutorialText;
public:
    tutorial(){
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

};

class intro{
    int a, b, c;
    tutorial t;
public:
    intro(){
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
    string tutor(){
        return t.pull();
    }
};

class controller{
public:
    string blank(){
        return "no arguments";
    }
    string single(){
        return "One argument";
    }
    string notBlank(){
        return "some arguments";
    }
};

string parse(string request, intro *i, controller *c){
    string output;
    vector<string> words;
    splitString(request, words, " ");
    cout << words.size() << '\n';
    switch (words.size()){
        case 1:
            if (words[0] == ""){
                output = c->blank();
            } else {
                output = c->single();
            }
            break;
        default:
            output = c->notBlank();
            break;
    }
    return output;
}





void zmqLoop(){
    controller c;
    int port = 5555;
    intro i;
    IOInterface * io = new zmqWrapper(port);
    cout << "Server live on port " << port << ".\n";
    while(true){
        string input = io->input();
        string output = parse(input, &i, &c);
        io->output(output);
    }
    delete io;
}

int main (){
    zmqLoop();
    return 0;
}