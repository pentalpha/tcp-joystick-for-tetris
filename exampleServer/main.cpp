#include <iostream>
#include "Server.h"

int main(int argc, char const *argv[]) {
  Server server;
  bool started = server.start();
  if(!started){
    std::cout << "Could not start server\n";
    return 1;
  }else{
    server.waitForClientAndReceive();
    return 0;
  }
}
