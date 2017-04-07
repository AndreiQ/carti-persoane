import sys
import socket
from threading import Thread
clients = []
myName =""
class Worker(Thread):
    def __init__(self, sock):
        Thread.__init__(self)
        self._sock = sock
        self._run = True
    def run(self):
        print ("Worker thread started: ", self)
        sock = self._sock
        while self._run:
            data, addr = self._sock.recvfrom(1024)
            client_name = data[0:data.index(" ")];
            message = data[data.index(" "):]
            if addr[0] not in clients:   
                clients.append(addr[0])
                clients.append(client_name)
            sys.stdout.write("\n"+clients[clients.index(addr[0]) + 1]+ ":" + message)
            sys.stdout.flush()
            
def __main__():
    socket1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    socket1.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    socket1.bind ( ("0.0.0.0", 6161) )
    worker = Worker(socket1)
    worker.setDaemon(True)
    worker.start()
    sys.stdout.write("What's your name? ")
    myName = sys.stdin.readline()
    myName = myName[0:-1]
    while True:
        print (clients)
        sys.stdout.write(myName + ":")
        sys.stdout.flush()
        line = sys.stdin.readline()
        if not line:
            break
        if line == '\n':
            continue
        if line.startswith("/msgall"):
            mesaj = line[7:].strip()
            mesaj = myName + " " + mesaj
            socket1.sendto(mesaj,
                           ("255.255.255.255", 6161))
        elif line.startswith("/msg"):
            line = line[4:]
            args = line.split()
            if len(args) != 3:
                print ("Comanda gresita")
                continue
            ip, port, msg = args
            port = int(port)
            socket1.sendto(msg,
                           (ip, port))
            
if __name__ == "__main__":
   __main__()

# lista nicknames

# + 1 2 3
# = 6
