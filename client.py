import zmq
import socket
import time
import struct


#  Socket to talk to server
print("Connecting to hello world server...")

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
sendMsg(s, "#QUIT")
s.close()

exit()

context = zmq.Context()

socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

socket.send("\0")
print(socket.recv())

socket.send("\0")
print(socket.recv())

socket.send("\0")
print(socket.recv())

exit()

def testSuccess():
    socket.send(b"getSuccess")
    msg = socket.recv()
    if (msg == "true"):
        return True
    else:
        return False

max = 1000
counter = 0
success = False
while success == False and counter < max:
    socket.send("get(a)")
    socket.recv()
    socket.send("get(b)")
    socket.recv()
    socket.send("get(c)")
    socket.recv()
    success = testSuccess()
    counter += 1

if success == True:
    print("Hooray, you won! Took " + str(counter) + " iterations.")
else:
    print("Timed out.")