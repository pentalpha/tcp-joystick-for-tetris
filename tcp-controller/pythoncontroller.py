import Adafruit_BBIO.ADC as ADC
import Adafruit_BBIO.GPIO as GPIO
import time
import socket
from threading import Thread
from Queue import Queue

HOST = "10.7.120.14"
PORT = 4325

POTENCIOMETER_TOLERANCE = 0.02
LIGHT_TOLERANCE = 0.1
KEEP_UPDATING = True
POTENCIOMETER_PORT = "P9_40"
LIGHT_PORT = "P9_38"
BUTTON_PORT = "P9_27"
SHADOW_STR = "shadow"
BUTTON_STR = "button"
LEFT_STR = "left"
RIGHT_STR = "right"
NO_COMMAND_STR = ""

cmds = Queue()
class LightWatcher(Thread):
	def __init__(self):
		Thread.__init__(self)
	
	def run(self):
		ADC.setup()
		shadowed = False
		old_light_factor = ADC.read(LIGHT_PORT)
		light_factor = ADC.read(LIGHT_PORT)
		while KEEP_UPDATING:
			light_factor = ADC.read(LIGHT_PORT)
			if not shadowed:
				if light_factor - old_light_factor >= LIGHT_TOLERANCE:
					cmds.put(SHADOW_STR)
					shadowed = True
					pass
				pass
			else:
				if light_factor - old_light_factor >= LIGHT_TOLERANCE:
					old_light_factor = light_factor
					shadowed = False
					pass
				pass
			pass
		pass
			
		

class ButtonWatcher(Thread):
	def __init__(self):
		Thread.__init__(self)
	
	def run(self):
		GPIO.setup(BUTTON_PORT, GPIO.IN)
		button_value = GPIO.input(BUTTON_PORT)
		old_button_value = GPIO.input(BUTTON_PORT)
		while KEEP_UPDATING:
			time.sleep(0.2)
			p = GPIO.input(BUTTON_PORT)
			if old_button_value == False and p == True:
				cmds.put(BUTTON_STR)
				pass
			old_button_value = button_value
			button_value = p
			pass
		pass


class MoveWatcher(Thread):
	def __init__(self):
		Thread.__init__(self)
	
	def run(self):
		ADC.setup()
		old_potenciometer = ADC.read(POTENCIOMETER_PORT)
		while KEEP_UPDATING:
			potenciometer = ADC.read(POTENCIOMETER_PORT)
			if (potenciometer - old_potenciometer) > POTENCIOMETER_TOLERANCE:
				cmds.put(LEFT_STR)
				pass
			if (old_potenciometer - potenciometer) > POTENCIOMETER_TOLERANCE:
				cmds.put(RIGHT_STR)
				pass
			old_potenciometer = potenciometer
			pass
		pass

			

tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
dest = (HOST, PORT)
tcp.connect(dest)

move_watcher = MoveWatcher()
button_watcher = ButtonWatcher()
light_watcher = LightWatcher()

move_watcher.start()
button_watcher.start()
light_watcher.start()

while True:
	#print "Nenhum comando encontrado."
	while not cmds.empty():
		tcp.send(cmds.get().encode())
	#time.sleep(0.5)


