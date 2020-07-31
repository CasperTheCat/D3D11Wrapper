import socket
import time
import struct
import os
import numpy
import sys

with open(sys.argv[1], "rb") as f:
    data = f.read()[8:]

datarts = numpy.array(struct.unpack("{}Q".format(len(data) // 8), data))

nEvents = 8

HOST = 'localhost'    # The remote host
PORT = 6666              # The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    index = 0
    while True:
        s.sendall(data[index*8*nEvents:(index+1)*8*nEvents])
        index+=1
        #s.sendall(b'\x55\x55\x00\x00\x00\x00\x00\x00')
        time.sleep(datarts[index] / 1000000)