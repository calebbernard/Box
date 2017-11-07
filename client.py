

#
#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back
#

import zmq

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
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

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