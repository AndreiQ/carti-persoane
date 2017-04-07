import sys
import socket


socket1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket1.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
socket1.bind ( ("0.0.0.0", 6161) )

while True:
	#primim de la client
	message, addr = socket1.recvfrom(1024)
	print message
	#parse message
	message += "xxxxxx";
	#trimitem inapoi 
	socket1.sendto(message,addr)