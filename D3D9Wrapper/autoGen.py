import os
import sys

data = []

with open(sys.argv[1], "r") as f:
    data = f.read().split("\n")

data = [x for x in data if not x.startswith("#")]
data = [x for x in data if not x.startswith("//")]
data = [x for x in data if not x == ""]
data = [x for x in data if not x == "{"]
data = [x for x in data if not x == "}"]
data = [x for x in data if not x.startswith("    return")]

for i in data:
    d = i.split()
    retType = d[0]
    callType = d[1]
    method = ' '.join(d[2:])

    funcType = method.split("::")[1]
    functionName = funcType.split("(")[0]
    args = funcType.split("(")[1].split(")")[0].split(", ")
    
    if len(args) > 0:
        args = [x.split(" ")[1] for x in args if len(x.split(" ")) > 1]
        args = ', '.join(args)
    else:
        args=""

    returnable = "return {}->{}({});".format("m_realDevice", functionName, args)

    print("{} {} {}\n{{\n\t{}\n}}\n".format(retType, callType, method, returnable))
