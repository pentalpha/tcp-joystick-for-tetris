#ifndef _BEAGLE_CONTROLLER_
#define _BEAGLE_CONTROLLER_

#include <iostream>
#include <thread>
#include <sstream>
#include <fstream>
#include "Queue.h"
#include "gpio.h"

#define MAX_POTENCIOMETER 4095
#define MAX_LDR 4095
#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"
//The ports of the ADC hardware
#define POTENCIOMETER_PORT 1
#define LIGHT_PORT 3
//The GPIO id of the button
#define BUTTON_GPIO 115
//A value smaller than the tolerance will be ignored
#define POTENCIOMETER_TOLERANCE 0.02
#define LIGHT_TOLERANCE 0.1

class BeagleController{
public:
  //BeagleController();
  //~BeagleController();

  //returns the current command
  static int getCommand();
  //Values to interpret the return of getCommand():
  const static int no_command = 0;
  //A movement to the right
  const static int right = 1;
  //A movement to the left
  const static int left = 2;
  //The light on the LDR decreased
  const static int shadow = 3;
  //The button has been pressed
  const static int button = 4;

  //reads an analog port
  static int readAnalog(int number);
  static void init();
  static void end();
  static float getNormalizedPort(int port);
  //static BeagleController* _instance;

private:

  //flag to continue the updating of the values
  static bool keepUpdating;

  static Queue cmds;

  //starts to update the values
  static void startWatchers();
  //callback to update the values
  static void moveWatcher();
  static void lightWatcher();
  static void buttonWatcher();
  static void stopWatchers();
};

#endif
