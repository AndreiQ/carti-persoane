import os
import time
import socket
from threading import Thread

class WorkerThread(Thread):
	def __init__(self, sock,client_addr):
		self._sock = sock
		self._clien_addr = client_addr
		Thread.__init__(self)

	def run(self):
		print ("Thread running!")
		sock = self._sock
		while(True):
			#recieve data from client
			buffer = sock.recv(1024)
			if not buffer:
				break
			# Parse Data
			print("Trimitem asta clientului: " + buffer)
			buffer+= " --de la server"
			#Send data to client
			sock.send(buffer)
		print("Inchidem conexiunea spre:", self._clien_addr)
		sock.close()

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("Setam opt socketului..")
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
print ("Legam socketul...")
server_socket.bind(("0.0.0.0", 6161))
print(" Asteptam dupa clienti...")
server_socket.listen(10)
while(True):
	print(" Asteptam clienti")
	client_socket ,client_addr= server_socket.accept()
	print(" Pornim thread nou pt:",client_addr)
	myThread = WorkerThread(client_socket,client_addr)
	myThread.start()
