

#
#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back
#

import zmq
import socket
import time

def testSuccess():
    socket.send(b"getSuccess")
    msg = socket.recv()
    if (msg == "true"):
        return True
    else:
        return False

context = zmq.Context()

#  Socket to talk to server
print("Connecting to hello world server...")


TCP_IP = '127.0.0.1'
TCP_PORT = 5555
BUFFER_SIZE = 1024
MESSAGE = "\0"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
while True:
    s.send(MESSAGE)
    data = s.recv(BUFFER_SIZE)
    print(data)
    time.sleep(1)
s.close()



exit()

socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

socket.send("")
print(socket.recv())

socket.send("")
print(socket.recv())

socket.send("")
print(socket.recv())

exit()

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