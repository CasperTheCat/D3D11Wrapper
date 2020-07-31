import sys
import matplotlib.pyplot
matplotlib.interactive(True)
matplotlib.use("TkAgg") 
import pandas
import numpy
import struct
import os
import time
from timeit import default_timer as timer
import math
import socket

matplotlib.pyplot.rcParams['toolbar'] = 'None'
#matplotlib.pyplot.tight_layout()

maxY = 200
maxTDPI = 240

if len(sys.argv) > 1:
    maxY = int(sys.argv[1])

if len(sys.argv) > 2:
    maxTDPI = int(sys.argv[2])


def rolling_window(a, window):
    pad = numpy.ones(len(a.shape), dtype=numpy.int32)
    pad[-1] = window-1
    pad = list(zip(pad, numpy.zeros(len(a.shape), dtype=numpy.int32)))
    a = numpy.pad(a, pad,mode='reflect')
    shape = a.shape[:-1] + (a.shape[-1] - window + 1, window)
    strides = a.strides + (a.strides[-1],)
    return numpy.lib.stride_tricks.as_strided(a, shape=shape, strides=strides)



index = 0
iRange = 1000
iTime = 30
smoothfactor = 30

resolution = numpy.array((1920, 1080))
TargetDPI = maxTDPI

#size = numpy.array([16,9])

solvedSize = resolution / TargetDPI

fig = matplotlib.pyplot.figure(dpi=TargetDPI, figsize=solvedSize)#figsize=(lScalar*scaleWidth, min((lScalar * scaleWidth*scaleWidth / 16), max(16, (lScalar * 18 / 16)))))
ax = matplotlib.pyplot.axes()
dra, = ax.plot([],[])

# For Green Chromakey Background
color = (0,1,0)
ax.plot([-5,iTime+5], [60,60])
ax.plot([-5,iTime+5], [30,30])

#color = (0,1,1)
#ax.plot([-5,iTime+5], [30,30])
#ax.plot([-5,iTime+5], [60,60])




ax.set_facecolor(color)
fig.set_facecolor(color)

#errorBars, = ax.plot([],[])
#errorBars, = ax.fill_between(1, 0, 1)

ax.set_xlabel("Time (Seconds)")
ax.set_ylabel("Frames Per Second")
ax.set_ylim(top=maxY, bottom=-1)
ax.set_xlim(left=-5, right=iTime+5)



dataHolder = [0]
dataHolderRt = [0]
dataStdHolder = [0]

accumulatedDeltaTime = 0

input("Press Any Key")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.bind(("localhost", 6666))
    sock.listen(1)

    while True:
        try:
            conn, addr = sock.accept()

            with conn:
                print("Got Conn from {}".format(addr))
                while True:
                    # 512 int64s
                    data = conn.recv(8 * 1024)

                    if not data:
                        break

                    fStart = timer()

                    data = numpy.array(struct.unpack("{}Q".format(len(data) // 8), data))
                    #print(data)

                    #print(data)

                    rt = numpy.cumsum(data) / 1000000
                    #print(rt[0])
                    # #rt = numpy.arange(0)
                    data = 1000000 / data

                    # How much time did this update contain?
                    deltaT = rt[-1]

                    # # base time
                    baseTime = dataHolderRt[-1]
                    #print("RT", rt[0])
                    rt += baseTime
                    #print("RTM", rt[0])

            
                    dataHolderRt =  numpy.concatenate([dataHolderRt,rt])
                    dataHolder =  numpy.concatenate([dataHolder,data])

                    #print(dataHolder.shape)
                    #print(dataHolder[-realWindow:].shape)
                    
                    #print([stddev])
                    #dataStdHolder = numpy.concatenate([dataStdHolder, [stddev]])

                    #dataHolderRt = numpy.cumsum(dataHolder) / 1000000

                    removalCutter = numpy.argmax(dataHolderRt > (dataHolderRt[-1] - iTime))
                    #print(removalCutter)

                    dataHolder = dataHolder[removalCutter:]
                    holdout = dataHolderRt[removalCutter]
                    dataHolderRt = dataHolderRt[removalCutter:] - holdout
                   # dataStdHolder = dataStdHolder[removalCutter:]

                    #print(dataHolder)
                    
                    #dataHolder = dataHolder[max(0, len(dataHolder) - iRange):]
                    #dataHolderRt = dataHolderRt[max(0, len(dataHolderRt) - iRange):]

                   
                    #cumTimePassed = dataHolderRt[0]
                    
                    #modRT = rt[index: iRange + index]
                    #modData = data[index: iRange + index]
                    
                    #RealWindow
                    
                    #print("RW Size: {}".format(realWindow))
                    realWindow = min(smoothfactor, len(dataHolder))
                    rolled = rolling_window(dataHolder, realWindow)
                    dataStdHolder = numpy.std(rolled, axis=-1)

                    comp = numpy.convolve(dataHolder, numpy.ones((realWindow,))/realWindow, mode='valid')
                    err = dataStdHolder[realWindow-1:realWindow+len(comp)]

                    #RAW
                    #comp = dataHolder
                    #err = dataStdHolder

                    # print(len(comp))
                    # print(dataHolder.shape)
                    # print(err.shape)
                    # print(dataHolderRt[:len(comp)].shape)
                    # dra.set_xdata(modRT[:-(smoothfactor-1)] - cumTimePassed)
                    # dra.set_ydata(comp)

                    #errorBars.set_xdata(dataHolderRt[:len(comp)])
                    #errorBars.set_ydata(dataStdHolder[:len(comp)])

                    ax.collections.clear()
                    ax.fill_between(dataHolderRt[:len(comp)], comp - (2 * err), comp + (2 * err), facecolor='blue', alpha=0.25)

                    dra.set_xdata(dataHolderRt[:len(comp)])
                    dra.set_ydata(comp)

                    #print(dataHolderRt[:len(comp)].shape)
                    #print(comp.shape)


                    # RAW
                    #dra.set_xdata(dataHolderRt)# - cumTimePassed)
                    #dra.set_ydata(dataHolder)

                    fig.canvas.draw()
                    fig.canvas.flush_events()

                    fFinish = timer()

                    # How much time did it take to process the update of size DeltaT
                    procTime = fFinish - fStart


                    accumulatedDeltaTime = max(0, accumulatedDeltaTime + procTime - deltaT)

                    print("Processed {:05g} events in {:0.5f} seconds (Currently lagging by {:0.5f} seconds). {:0.5f}".format(len(data), procTime, accumulatedDeltaTime, deltaT))

        except KeyboardInterrupt as kbi:
            raise kbi
        except ConnectionResetError as e:
            continue
        except Exception as e:
            raise e
            continue









print(1/0)


data = None

# with open(sys.argv[1], "rb") as f:
#     data = f.read()

data = numpy.array(struct.unpack("{}Q".format(len(data) // 8), data))

rt = numpy.cumsum(data) / 1000000

# FPS
data = 1000000 / data

# highest = numpy.max(data)
# vertScale = ((highest) // 300) + 1
# print(vertScale)

#pd = pandas.DataFrame(data)

# print(lTime)

#fig = matplotlib.pyplot.figure(figsize=(lScalar*9, 2 * vertScale))
#ax = matplotlib.pyplot.axes()

smoothfactor = 60
scaleWidth = 16

cumsum = numpy.cumsum(numpy.insert(data, 0, 0)) 
comp = (cumsum[smoothfactor:] - cumsum[:-smoothfactor]) / float(smoothfactor)



modSecondsPassedInLoop = 0
modTotalEvaledTime = 0
modAbleIndxInc = 0
modTrueIndexChangeAmount = 0

modUncountedDelta = 0

while(True):
    fStart = timer()
    cumTimePassed = rt[index]
    
    modRT = rt[index: iRange + index]
    modData = data[index: iRange + index]
    

    #print(lScalar*scaleWidth, min((lScalar * scaleWidth*scaleWidth / 16), max(16, (lScalar * 18 / 16))))
    #ax.plot(modRT[:-(smoothfactor-1)], comp)
    #ax.plot([-5,lTime], [30,30])
    #ax.plot([-5,lTime], [60,60])


    # comp = numpy.convolve(modData, numpy.ones((smoothfactor,))/smoothfactor, mode='valid')
    # dra.set_xdata(modRT[:-(smoothfactor-1)] - cumTimePassed)
    # dra.set_ydata(comp)
    dra.set_xdata(modRT - cumTimePassed)
    dra.set_ydata(modData)

    #ax = pd.plot()
    fig.canvas.draw()
    fig.canvas.flush_events()

    fFinish = timer()

    # SliceTime
    slicedTime = cumTimePassed - modTotalEvaledTime
    actualExeTime = fFinish - fStart
    deltaAck = actualExeTime - slicedTime
    modTotalEvaledTime = cumTimePassed

    #print("ST: {}, AT: {}, DT: {}".format(slicedTime, actualExeTime, deltaAck))

    # If delta is > 0, we took longer to draw the change than the change represent.
    # Accumulate this error
    modUncountedDelta += deltaAck

    #print("ST: {}, AT: {}, DT: {}, ACC: {}".format(slicedTime, actualExeTime, deltaAck, modUncountedDelta))



    #PID#
    modAbleIndxInc += deltaAck * 0.1
    modAbleIndxInc += actualExeTime * modUncountedDelta

    modTrueIndexChangeAmount = max(0, math.floor(modAbleIndxInc))

    index += (1 + modTrueIndexChangeAmount)

    print("ST: {}, AT: {}, DT: {}, ACC: {}, IDXD: {}, IDX: {}".format(slicedTime, actualExeTime, deltaAck, modUncountedDelta, modAbleIndxInc, index))

#matplotlib.pyplot.show()#savefig("Sliding_{}.png".format(name))