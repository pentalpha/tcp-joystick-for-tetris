#include "beagleController.h"
#include <iostream>
using namespace std;

bool BeagleController::keepUpdating;
Queue BeagleController::cmds;

/*BeagleController::BeagleController(){
  startWatchers();
}

BeagleController::~BeagleController(){
  stopWatchers();
}*/

void BeagleController::init(){
  startWatchers();
}

void BeagleController::end(){
  stopWatchers();
}

int BeagleController::readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

float BeagleController::getNormalizedPort(int port){
  return ((float)readAnalog(port) / (float)MAX_POTENCIOMETER);
}

void BeagleController::startWatchers(){
  keepUpdating = true;
  thread t1 = thread(BeagleController::moveWatcher);
  t1.detach();
  thread t2 = thread(BeagleController::lightWatcher);
  t2.detach();
  thread t3 = thread(BeagleController::buttonWatcher);
  t3.detach();
}
void BeagleController::stopWatchers(){
  keepUpdating = false;
}

void BeagleController::moveWatcher(){
  float old_potenciometer;
  float potenciometer;
  old_potenciometer = potenciometer = getNormalizedPort(POTENCIOMETER_PORT);
  while(keepUpdating)
  {
    float p = getNormalizedPort(POTENCIOMETER_PORT);
    potenciometer = p;
    if((potenciometer - old_potenciometer) > POTENCIOMETER_TOLERANCE){
      old_potenciometer = potenciometer;
      int* v = new int;
      *v = BeagleController::left;
      cmds.push(v);
    }else if((old_potenciometer - potenciometer) > POTENCIOMETER_TOLERANCE){
      old_potenciometer = potenciometer;
      int* v = new int;
      *v = BeagleController::right;
      cmds.push(v);
    }else{
    }
  }
}

void BeagleController::lightWatcher(){
  float old_lightFactor;
  float lightFactor;
  bool shadowed = false;
  old_lightFactor = lightFactor = getNormalizedPort(LIGHT_PORT);
  while(keepUpdating)
  {
    lightFactor = getNormalizedPort(LIGHT_PORT);
    if(shadowed == false){
      if(lightFactor - old_lightFactor >= LIGHT_TOLERANCE){
        old_lightFactor = lightFactor;
        int* v = new int;
        *v = BeagleController::shadow;
        cmds.push(v);
        shadowed = true;
      }
    }else{
      if(old_lightFactor - lightFactor >= LIGHT_TOLERANCE){
        old_lightFactor = lightFactor;
        shadowed = false;
      }
    }
  }
}

void BeagleController::buttonWatcher(){
  bool old_buttonValue;
  bool buttonValue;
  //buttonValue = old_buttonValue = false;
  buttonValue = old_buttonValue = getGpioValue(BUTTON_GPIO);
  while(keepUpdating){
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    bool p = getGpioValue(BUTTON_GPIO);
    if(old_buttonValue == false && p == true){
      int* v = new int;
      *v = BeagleController::button;
      cmds.push(v);
    }
    old_buttonValue = buttonValue;
    buttonValue = p;
  }
}

int BeagleController::getCommand(){

  int* cmd = cmds.pop();
  if(cmd != NULL){
    return *cmd;
  }else{
    return BeagleController::no_command;
  }
}
