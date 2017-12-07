#pragma once

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

#include <iomanip>
#include <string>
#include "stringUtil.h"
using namespace std;

class IOInterface{
public:
    virtual string input()=0;
    virtual void output(string msg)=0;
    virtual string description();
    virtual bool connected()=0;
    virtual void connect()=0;
};

class TcpWrapper: public IOInterface{
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[100000];
    struct sockaddr_in serv_addr, cli_addr;
public:
    TcpWrapper(int port);
    string input();
    void output (string msg);
    string description();
    void connect();
    bool connected();
};