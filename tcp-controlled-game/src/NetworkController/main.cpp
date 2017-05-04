#include <iostream>
#include <thread>
#include <chrono>
#include "Server.h"

int main(int argc, char const *argv[]) {
  Server server;
  bool started = server.start();
  if(!started){
    std::cout << "Could not start server\n";
    return 1;
  }else{
    server.startWaiting();
    int i = 8;
    while(i > 0){
      std::this_thread::sleep_for(std::chrono::milliseconds(800));
      string s = server.getMessage();
      if(s != ""){
        cout << s << "\n";
        i--;
      }
    }
    server.stop();
  }
}
