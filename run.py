#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
from __future__ import division

import os
import sys
import argparse

baseDir = os.path.dirname(os.path.abspath(__file__))
buildDir = baseDir + "/.build"

parser = argparse.ArgumentParser()
parser.add_argument('-s', '--source')
parser.add_argument('-b', '--bin', default=buildDir + "/Solution")
parser.add_argument('-d', '--debug', default=False, action="store_true")
parser.add_argument('-i', '--stdin', default=baseDir + "/_main.in")
parser.add_argument('-o', '--stdout', default=baseDir + "/_main.out")
args = parser.parse_args()

fileExt = args.source.split(".")
if len(fileExt) < 1:
    print("Cannot detect file extension name!")
    exit(-1)
else:
    fileExt = fileExt[-1]

def run(cmd):
    os.system("date")
    os.system("time %s < '%s' | tee '%s'" % (cmd, args.stdin, args.stdout))

if fileExt == "cpp":
    flag = "-g" if args.debug else "-O3"
    os.system("g++ -D__LOCAL__ --std=c++11 %s '%s' -o %s" % (flag, args.source, args.bin))
    run(args.bin)

elif fileExt == "py":
    run("python3 " + args.source)

elif fileExt == "java":
    os.system("cp %s %s/Solution.java" % (args.source, buildDir))
    os.system("javac %s/Solution.java" % buildDir)
    run("cd %s && java Solution" % buildDir)

else:
    print("unsupported source type.")