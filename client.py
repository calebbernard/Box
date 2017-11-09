import socket
TCP_IP = '127.0.0.1'
TCP_PORT = 5555
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

def sendMsg(m):
    l = str(len(m))
    while len(l) < 5:
        l = "0" + l;
    s.send(l + m)

def recvMsg():
    headerSize = 5
    size = int(s.recv(headerSize))
    if size > 0:
        return s.recv(size)
    else:
        return ""

def get(m):
    sendMsg(m)
    return recvMsg()

def g(m):
    reply = get(m)
    print reply
    return reply

# client code goes here

s.close()

exit()