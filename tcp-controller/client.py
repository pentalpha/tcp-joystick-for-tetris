import socket
import time
HOST = '127.0.0.1'      # Endereco IP do Servidor
PORT = 4325             # Porta que o Servidor esta
tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
dest = (HOST, PORT)
tcp.connect(dest)
i = 0;
while i < 10:
    time.sleep(1)
    msg = "Message " + str(i) + " from client"
    tcp.send(msg.encode())
    i = i + 1
tcp.close()
