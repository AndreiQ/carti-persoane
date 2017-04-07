import sys
import os
import socket
from threading import Thread
class WorkerThread(Thread):
    def __init__(self, sock, addr):
        self.sock = sock
        self.addr_client = addr
        Thread.__init__(self)
    def run(self):
        print("Thread running")
        socket = self.sock
        while(True):
            message = socket.recv(1024)
            if not message:
                break
            if message == "Imi dai alea?\n":
                print "da"
                message = "da"
            else:
                print "nu"
            
            socket.send(message)
        print("Inchidem conexiunea catre " , self.addr_client)
        socket.close()    
    
server_socket = socket.socket(socket.AF_INET , socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET , socket.SO_REUSEADDR,1)
server_socket.bind(("0.0.0.0", 6161))
server_socket.listen(10)
while(True):
    socket_client, addr_client = server_socket.accept()
    myThread = WorkerThread(socket_client, addr_client)
    myThread.start()
