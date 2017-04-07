import sys
import socket

if len(sys.argv) != 3:
	print(" argumente gresite")
	sys.exit(1)

addr, port = sys.argv[1:]
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((addr, int(port)))

f = sock.makefile("wr")
while True:
	linie = sys.stdin.readline()
	if not linie:
		break
	f.write(linie)
	f.flush()
	print (f.readline())
f.close()
