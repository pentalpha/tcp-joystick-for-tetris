#ifndef _SERVER_
#define _SERVER_

#include <iostream>     //cout
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close

#define MAXMSG 1024
#define PORTNUM 4325

class Server{
public:
  Server();

  bool start();
  void waitForClientAndReceive();
private:
  bool getSocket();
  bool doBind();
  bool startListening();
  //variáveis do servidor
  struct sockaddr_in address;
  int socketId;
  //variáveis relacionadas com as conexões clientes
  struct sockaddr_in addressClient;
  socklen_t sizeAddressClient;
  int connectionClientId;
  //Permitir inserir o caractere de fim de msg \0
  char *msg;
  int bytesread;
};

#endif
