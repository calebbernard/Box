#include "io.h"
using namespace std;

    string IOInterface::description(){
        return "Server";
    }

    TcpWrapper::TcpWrapper(int port) {
        newsockfd = 0;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero((char*)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);
        bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    }
    string TcpWrapper::input(){
        bzero(buffer, 99999);
        read(newsockfd, buffer, 5);
        for (int x = 0; x < 5; x++){
            if (buffer[x] == '\0'){
                throw(0);
            }
            if (buffer[x] < '0' || buffer[x] > '9'){
                cout << "Error: Bad input format.\nPlease preface each ASCII message with a 5-character string specifying the length in bytes of the remaining message.\n";
                cout << "(Character " << buffer[x] << " found at position " << x << ", which is reserved for length marker)\n";
                throw(0);
            }
        }
        int msgLength = 0;
        for (int x = 0; x < 5; x++){
            msgLength *= 10;
            msgLength += buffer[x] - '0';
        }
        bzero(buffer, 5);
        if (msgLength > 0){
            read (newsockfd, buffer, msgLength);
        }
        return buffer;
    }
    void TcpWrapper::output (string msg){
        string length = itos(msg.length());
        while (length.length() < 5){
            length = "0" + length;
        }
        string finalMsg = length + msg;
        write(newsockfd, finalMsg.c_str(), finalMsg.length());
    }
    string TcpWrapper::description(){
        return "TCP server";
    }
    void TcpWrapper::connect(){
        listen(sockfd, 5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
        bzero(buffer, 99999);
    }
    bool TcpWrapper::connected(){
        return newsockfd != 0;
    }