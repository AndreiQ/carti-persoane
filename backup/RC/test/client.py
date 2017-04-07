import socket
import sys
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
if len(sys.argv) != 3:
	print(" argumente gresite")
	sys.exit(1)

addr, port = sys.argv[1:]
sock.connect((addr, int(port)))


while True:
	date_fisier = sys.stdin.readline()
	continut_fisier = sys.stdin.readline()
	data = date_fisier + continut_fisier
	if not data:
		break
	#trimitem ce am scris
	sock.send(data)
	#printam ce am scris
	#print (date_fisier,continut_fisier)
	f = sock.recv(1024)
	#printam ce am primit de la server
	print(f)
f.close()