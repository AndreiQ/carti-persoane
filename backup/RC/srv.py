import sys
import socket
from threading import Thread

class Worker(Thread):
    def __init__(self, sock):
        Thread.__init__(self)
        self._sock = sock
        self._run = True
    def run(self):
        print ("Worker thread started: ", self)
        sock = self._sock
        while self._run:
            data, addr = socket1.recvfrom(1024)
            sys.stdout.write("Msg From %s %d: %s\n"% (addr[0],
                                                    addr[1],
                                                    data))
            sys.stdout.flush()

socket1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket1.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
socket1.bind ( ("0.0.0.0", 6161) )

worker = Worker(socket1)
worker.setDaemon(True)
worker.start()

while True:
    sys.stdout.write("Mesaj: ")
    sys.stdout.flush()
    line = sys.stdin.readline()
    if not line:
        break
    if line == '\n':
        continue
    if line.startswith("/msgall"):
        mesaj = line[7:].strip()
        socket1.sendto(bytes(mesaj, "utf8"),
                       ("255.255.255.255", 6161))
    elif line.startswith("/msg"):
        line = line[4:]
        args = line.split()
        if len(args) != 3:
            print ("Comanda gresita")
            continue
        ip, port, msg = args
        port = int(port)
        socket1.sendto(bytes(msg, "utf8"),
                       (ip, port))

# nicknames