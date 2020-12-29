import socket 
import threading

HEADER = 64
PORT = 15200
#SERVER = socket.gethostbyname(socket.gethostname())
SERVER = '192.168.101.8'
ADDR = (SERVER, PORT)
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "!DISCONNECT"

clientes = []

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

def msg_to_user(msg):
    clientes[0].send(msg)

def handle_client(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected.")
    connected = True
    while connected:
        msg_client = conn.recv(HEADER).decode(FORMAT)
        if msg_client.startswith('200'):
            inform = msg_client.split(' ')
            print (inform)    
            data = 'Hola amigo!'.encode()   
            msg_to_user(data)
             #conn.send(msg_client.encode(FORMAT))
  #  conn.close()
        

def start():
    server.listen()
    print(f"[LISTENING] Server is listening on {SERVER}")
    while True:
        conn, addr = server.accept()
        clientes.append(conn)
        
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()

        print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")






if __name__ == '__main__':
    print("[STARTING] server is starting...")
    start()
    
#python servers\serverSocket.py