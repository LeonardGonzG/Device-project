import socket

HEADER = 64
PORT = 15200
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "!DISCONNECT"
SERVER = "192.168.139.2"
ADDR = (SERVER, PORT)

class clientSocket:

    def __init__(self):
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect(ADDR)
    
    def send(self, msg):
        message = msg.encode(FORMAT)
        msg_length = len(message)
        send_length = str(msg_length).encode(FORMAT)
        send_length += b' ' * (HEADER - len(send_length))
        self.client.send(send_length)
        self.client.send(message)
        print(client.recv(2048).decode(FORMAT))

    def closeConection(self):
        send(DISCONNECT_MESSAGE)


