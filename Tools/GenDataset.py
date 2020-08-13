import sys
import numpy
import struct
import os

numElements = 1000000
data = []

data = (numpy.sin(numpy.arange(numElements) * 0.01) + 1) * 0.5
data *= 1 + (numpy.sin(numpy.arange(numElements) * 0.1) * 0.1)
data *= 1 + (numpy.sin(numpy.arange(numElements) * 0.5) * 0.3)
data *= 1 + (numpy.sin(numpy.arange(numElements) * 0.0001) * 1)

maxVal = max(1, numpy.max(data))
minVal = min(0, numpy.min(data))

maxFPS = 160
minFPS = 25

data = minFPS + (maxFPS - minFPS) * ((data - minVal) / (maxVal - minVal))

#data *= (2**63 - 1)
#data *= 160 # 160 FPS max
data = 1000000 / data

newMaxVal = numpy.max(data)
newMinVal = numpy.min(data)

print("{},{} mapped to {},{}".format(maxVal, minVal, newMaxVal, newMinVal))

#dataOut = struct.pack("{}Q".format(numElements), data.astype("Q"))

with open(sys.argv[1], "wb") as f:
    f.write(data.astype("Q"))
