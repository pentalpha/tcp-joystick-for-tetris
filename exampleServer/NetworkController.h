#ifndef _NETWORK_CONTROLLER_
#define _NETWORK_CONTROLLER_

#include <iostream>
#include <thread>
#include <sstream>
#include <fstream>
#include <string>
#include "Queue.h"
#include "Server.h"

using namespace std;

class NetworkController{
public:
  //NetworkController();
  //~NetworkController();

  //returns the current command
  static int getCommand();
  //Values to interpret the return of getCommand():
  const static string no_commandStr;
  const static int no_command = 0;
  //A movement to the right
  const static string rightStr;
  const static int right = 1;
  //A movement to the left
  const static string leftStr;
  const static int left = 2;
  //The light on the LDR decreased
  const static string shadowStr;
  const static int shadow = 3;
  //The button has been pressed
  const static string buttonStr;
  const static int button = 4;

  static void init();
  static void start();
  static void end();
  static void setIP(const char* ip);
  //static NetworkController* _instance;
private:

  //flag to continue the updating of the values
  static bool keepUpdating;
  static Queue cmds;
  static Server *cmdServer;
  static const char* localIP;

  //starts to update the values
  static void startWatchers();
  //callback to update the values
  static void serverWatcher();
  static void stopWatchers();
};

#endif
