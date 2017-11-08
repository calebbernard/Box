import socket
TCP_IP = '127.0.0.1'
TCP_PORT = 5555

def sendMsg(s, m):
    l = str(len(m))
    while len(l) < 5:
        l = "0" + l;
    s.send(l + m)

def recvMsg(s):
    headerSize = 5
    size = int(s.recv(headerSize))
    return s.recv(size)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
sendMsg(s, "")
print(recvMsg(s))
sendMsg(s, "")
print(recvMsg(s))
sendMsg(s, "")
print(recvMsg(s))
sendMsg(s, "")
print(recvMsg(s))
s.close()

exit()