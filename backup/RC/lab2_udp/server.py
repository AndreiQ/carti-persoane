import socket
from	threading import Thread

class Worker(Thread):
	def __init__(self,sock):
		Thread.__init__(self)
		self._sock = sock
		self._run = True
	def start(self):
		print("Worker thread started")
		sock = self._sock
		while self._run:
			data, addr = socket1.recvfrom(1024)
			sys.stdout.write("MSG from %s %d: %S",addr[0],addr[1],data)	
socket1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket1.bind(("0.0.0.0", 6161))
socket1.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST,1)
worker = Worker(socket1)
worker.setDaemon(True)
worker.start()
while True:
	sys.stdout.printLine("Mesaj:")
 	sys.stdout.flush()
 	line = sys.stdin.readline()#input("Mesaj:")
 	if not line:
 		break
 	if line == '\n':
 		continue
 	#if(line .startswith("/msgall")):

 	socket1.sendto(line,("255.255.255.255",6161))
 	