#pragma once

#include <zmq.hpp>
#include <zmq_addon.hpp>

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <string>
#include "stringUtil.h"
using namespace std;

class IOInterface{
public:
    virtual string input()=0;
    virtual void output(string msg)=0;
    virtual string description(){
        return "Server";
    }
    virtual bool connected()=0;
    virtual void connect()=0;
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
    string description(){
        return "ZeroMQ server";
    }
    void connect(){
        
    }
    bool connected(){
        return true;
    }
};

class TcpWrapper: public IOInterface{
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
public:
    TcpWrapper(int port) {
        newsockfd = 0;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero((char*)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);
        bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    }
    string input(){
        read(newsockfd, buffer, 1023);
        return buffer;
    }
    void output (string msg){
        write(newsockfd, msg.c_str(), msg.length());
    }
    string description(){
        return "TCP server";
    }
    void connect(){
        listen(sockfd, 5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
        bzero(buffer, 1023);
    }
    bool connected(){
        return newsockfd != 0;
    }
};