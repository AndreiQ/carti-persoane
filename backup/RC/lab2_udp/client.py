import socket

socket1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket1.bind(("0.0.0.0", 0))
socket1.sendto(" Cucu",("127.0.0.1",6161))