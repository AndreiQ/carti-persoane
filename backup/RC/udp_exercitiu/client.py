import sys
import socket


client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ("0.0.0.0", 6161)
while True:
	#trimitem message la server
	message = sys.stdin.readline()
	client_socket.sendto(message,addr)
	#primim de la server
	data, server = client_socket.recvfrom(1024)
	print data