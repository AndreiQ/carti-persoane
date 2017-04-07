import sys
import socket

if len(sys.argv) != 3:
	print(" argumente gresite. Sintaxa '%s adresa port: %s", sys.argv[0])
	sys.exit(1)

addr, port = sys.argv[1:]
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((addr, int(port)))

#CU FISIER

f = sock.makefile("wr")
while True:
	linie = sys.stdin.readline()
	if not linie:
		break
	f.write(linie)
	f.flush()
	print (f.readline())
f.close()



#FARA FISIER
'''
while True:
	linie = sys.stdin.readline()
	if not linie:
		break
	#trimitem ce am scris
	sock.send(linie)
	#printam ce am scris
	print (linie)
	f = sock.recv(1024)
	#printam ce am primit de la server
	print(f)
f.close()
'''