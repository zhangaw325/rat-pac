#!/bin/sh
RATROOT=/home/aw325/Downloads/rat-pac
PATH=$RATROOT/bin:$PATH
LD_LIBRARY_PATH=$RATROOT/lib:$LD_LIBRARY_PATH
# For Mac OS X
DYLD_LIBRARY_PATH=$RATROOT/lib:$DYLD_LIBRARY_PATH
GLG4DATA=$RATROOT/data
PYTHONPATH=$RATROOT/python:$PYTHONPATH
export RATROOT PATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH GLG4DATA PYTHONPATH