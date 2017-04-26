/*
Pitágoras Alves & André Winston, UFRN, March 2017.

Basic API to use GPIOs on Linux systems.
Uses the "echo" and "cat" commands.
*/
#ifndef _GPIO_API_
#define _GPIO_API_

#include <string>
#include <unistd.h>
#include "run.h"

using namespace std;

bool getGpioValue(int id);
/*
Gets the direction of the gpio: "in" or "out"
*/
string getGpioDirection(int id);

/*
The direction can be only in or out
*/
void setGpioDirection(int id, string val);

void setGpioValue(int id, bool val);

/*
In case the gpio folder does not exists, creates it.
*/
void exportGpio(int id);

#endif
