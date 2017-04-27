#include "NetworkController.h"
#include <iostream>
using namespace std;

bool NetworkController::keepUpdating;
Queue NetworkController::cmds;
Server NetworkController::cmdServer;
const string NetworkController::no_commandStr = "";
//A movement to the right
const string NetworkController::rightStr = "right";
//A movement to the left
const string NetworkController::leftStr = "left";
//The light on the LDR decreased
const string NetworkController::shadowStr = "shadow";
//The button has been pressed
const string NetworkController::buttonStr = "button";

/*NetworkController::NetworkController(){
  startWatchers();
}

NetworkController::~NetworkController(){
  stopWatchers();
}*/

void NetworkController::init(){
  cmdServer.start();
  //startWatchers();
}

void NetworkController::end(){
  stopWatchers();
  cmdServer.stop();
}

void NetworkController::start(){
  cmdServer.startWaiting();
  startWatchers();
}

void NetworkController::startWatchers(){
  keepUpdating = true;
  thread t1 = thread(NetworkController::serverWatcher);
  t1.detach();
}

void NetworkController::stopWatchers(){
  keepUpdating = false;
}

void NetworkController::serverWatcher(){
  while(keepUpdating){
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    string s = cmdServer.getMessage();
    int *cmdPointer = new int(NetworkController::no_command);
    if(s == NetworkController::rightStr){
      *cmdPointer = NetworkController::right;
    }else if(s == NetworkController::leftStr){
      *cmdPointer = NetworkController::left;
    }else if(s == NetworkController::shadowStr){
      *cmdPointer = NetworkController::shadow;
    }else if(s == NetworkController::buttonStr){
      *cmdPointer = NetworkController::button;
    }
    if(*cmdPointer != NetworkController::no_command){
      cmds.push(cmdPointer);
    }
  }
}

int NetworkController::getCommand(){
  int* cmd = cmds.pop();
  if(cmd != NULL){
    return *cmd;
  }else{
    return NetworkController::no_command;
  }
}
