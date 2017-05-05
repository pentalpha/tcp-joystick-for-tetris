import socket
import time
import sys

HOST = "127.0.0.1"
if(len(sys.argv) == 2):
	HOST = sys.argv[1]      # Endereco IP do Servidor
PORT = 50001             # Porta que o Servidor esta
print("Hosting on " + HOST)
tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
dest = (HOST, PORT)
tcp.connect(dest)
commands = list()
commands.append("right")
commands.append("left")
commands.append("right")
commands.append("right")
commands.append("right")
commands.append("shadow")
commands.append("button")
commands.append("left")
commands.append("left")
commands.append("right")
commands.append("right")
commands.append("right")
for cmd in commands:
    time.sleep(1)
    msg = cmd
    tcp.send(msg.encode())
tcp.close()
