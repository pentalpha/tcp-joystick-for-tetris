#include <iostream>
#include <thread>
#include <chrono>
#include "Server.h"

int main(int argc, char const *argv[]) {
  const char* ip = "127.0.0.1";
  if(argc >= 2){
    ip = argv[1];
  }
  std::cout << "Hosting on " << ip << std::endl;
  Server server(ip);
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
