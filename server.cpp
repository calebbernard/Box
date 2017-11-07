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

string parse(string request, intro *i){
    //cout << request << endl;
    if (request == "get(a)"){
        return i->get("a");
    }
    else if (request == "get(b)"){
        return i->get("b");
    }
    else if (request == "get(c)"){
        return i->get("c");
    }
    else if (request == ""){
        return i->tutor();
    }
    else {
        return i->get_success();
    }
}

int main (){
    int port = 5555;
    intro i;
    cout << "Server live on port " << port << ".\n";
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:" + itos(port));
    while(true){
        zmq::message_t request;
        socket.recv(&request);
        //cout << string(static_cast<char*>(request.data()), request.size()) << endl;
        string output = parse(string(static_cast<char*>(request.data()), request.size()), &i);

        zmq::message_t reply(output.length());
        memcpy (reply.data(), output.c_str(), output.length());
        socket.send(reply);
    }
    return 0;
}