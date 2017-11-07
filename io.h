#pragma once

#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <string>
#include "stringUtil.h"
using namespace std;

class IOInterface{
public:
    virtual string input()=0;
    virtual void output(string msg)=0;
};

class ZmqWrapper : public IOInterface{
private:
    zmq::context_t context;
    zmq::socket_t socket;
public:
    ZmqWrapper(int port) : context(1), socket(context, ZMQ_REP){
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