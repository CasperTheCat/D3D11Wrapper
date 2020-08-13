import sys
import matplotlib.pyplot
import pandas
import numpy
import struct
import os

data = None

with open(sys.argv[1], "rb") as f:
    data = f.read()

data = struct.unpack("{}Q".format(len(data) // 8), data)
data = numpy.array(data, dtype=numpy.uint64)[1:]

data = numpy.array([x for x in data if x < 100000])

rt = numpy.cumsum(data) / 1000000

lTime = rt[-1]
lTime += 5
lScalar = ((lTime // 60) + 1)
lTime = lScalar * 60

data = 1000000 / data

highest = numpy.max(data)
vertScale = ((highest) // 300) + 1
print(vertScale)

#pd = pandas.DataFrame(data)

print(lTime)

fig = matplotlib.pyplot.figure(figsize=(lScalar*9, 2 * vertScale))
ax = matplotlib.pyplot.axes()

ax.plot(rt, data)
#ax = pd.plot()
ax.plot([-5,lTime], [30,30])
ax.plot([-5,lTime], [60,60])
ax.plot([-5,lTime], [300,300])
ax.set_xlabel("Time (Seconds)")
ax.set_ylabel("Frames Per Second")
ax.set_ylim(top=vertScale*300, bottom=-1)
ax.set_xlim(left=-5, right=lTime)

name = os.path.basename(sys.argv[1])
ax.get_figure().savefig("FullSize_{}.png".format(name))



fig = matplotlib.pyplot.figure(figsize=(lScalar*9, min((lScalar * 81 / 16), 16)))
ax = matplotlib.pyplot.axes()
ax.plot(rt, data)
ax.plot([-5,lTime], [30,30])
ax.plot([-5,lTime], [60,60])
#ax = pd.plot()
ax.set_xlabel("Time (Seconds)")
ax.set_ylabel("Frames Per Second")
ax.set_ylim(top=300, bottom=-1)
ax.set_xlim(left=-5, right=lTime)
ax.get_figure().savefig("CapSize_300_{}.png".format(name))

print((lScalar*9, min((lScalar * 81 / 16), 16)))
fig = matplotlib.pyplot.figure(figsize=(lScalar*9, min((lScalar * 81 / 16), 16)))
ax = matplotlib.pyplot.axes()
ax.plot(rt, data)
ax.plot([-5,lTime], [30,30])
ax.plot([-5,lTime], [60,60])
#ax = pd.plot()
ax.set_xlabel("Time (Seconds)")
ax.set_ylabel("Frames Per Second")
ax.set_ylim(top=150, bottom=-1)
ax.set_xlim(left=-5, right=lTime)
ax.get_figure().savefig("CapSize_150_{}.png".format(name))

print((lScalar*9, min((lScalar * 81 / 16), 16)))
fig = matplotlib.pyplot.figure(figsize=(16, 9))
ax = matplotlib.pyplot.axes()
ax.plot(rt, data)
ax.plot([-5,lTime], [30,30])
ax.plot([-5,lTime], [60,60])
#ax = pd.plot()
ax.set_xlabel("Time (Seconds)")
ax.set_ylabel("Frames Per Second")
ax.set_ylim(top=vertScale*300, bottom=-1)
ax.set_xlim(left=-5, right=lTime)
ax.get_figure().savefig("CapSize_500_{}.png".format(name))


smoothfactor = 60

cumsum = numpy.cumsum(numpy.insert(data, 0, 0)) 
comp = (cumsum[smoothfactor:] - cumsum[:-smoothfactor]) / float(smoothfactor)

comp = numpy.convolve(data, numpy.ones((smoothfactor,))/smoothfactor, mode='valid')

print(lScalar*9, min((lScalar * 81 / 16), max(16, (lScalar * 18 / 16))))
fig = matplotlib.pyplot.figure(figsize=(lScalar*9, min((lScalar * 81 / 16), max(16, (lScalar * 9 / 16)))))
ax = matplotlib.pyplot.axes()
ax.plot(rt[:-(smoothfactor-1)], comp)
ax.plot([-5,lTime], [30,30])
ax.plot([-5,lTime], [60,60])
#ax = pd.plot()
ax.set_xlabel("Time (Seconds)")
ax.set_ylabel("Frames Per Second")
ax.set_ylim(top=500, bottom=-1)
ax.set_xlim(left=-5, right=lTime)
ax.get_figure().savefig("Sliding_{}.png".format(name))