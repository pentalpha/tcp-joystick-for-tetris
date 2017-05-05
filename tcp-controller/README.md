## Python code for an analogic joystick for a Tetris game with a Beaglebone Black.

### Controls:

#### ADC:

- A potenciometer in /sys/bus/iio/devices/iio:device0/in_voltage1_raw

- A LDR sendor in /sys/bus/iio/devices/iio:device0/in_voltage3_raw

#### GPIO:

- An input button in /sys/class/gpio/gpio115;

### The full circuit on a proto-board:

![Controller on Beaglebone Black](./image2.jpg)

## To Run:
```sh
    $ sudo python2 pythoncontroller.py <host game IPv4 address>
```
