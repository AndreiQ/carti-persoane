
import socket
from threading import Thread


class WorkerThread(Thread):
	def __init__(self, sock,client_addr):
		self._sock = sock
		self._clien_addr = client_addr
		Thread.__init__(self)

	def run(self):
		socket = self._sock
		while(True):
			#recieve data from client

			buffer = socket.recv(1024)
			if not buffer:
				break
			# Parse Data
			file_name = buffer.split(" ")[0];
			data_dim = buffer.split(" ")[1][0];
			data = buffer.split("\n")[1:];
			
			f = open(file_name,"w+")
			if not f:
				socket.send("< NOK")
			else:
				f.write(str(data))
				socket.send("< OK")

			print buffer ," file_name: ",file_name ,"    data_dim:", data_dim ,"  ce sa scrie: ",data

		socket.close()

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
server_socket.bind(("0.0.0.0", 2222))
server_socket.listen(10)

while(True):
	client_socket ,client_addr = server_socket.accept()
	myThread = WorkerThread(client_socket,client_addr)
	myThread.start()
