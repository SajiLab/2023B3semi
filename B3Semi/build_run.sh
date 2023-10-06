#!/bin/sh

echo "+++++++  build start........."
cmake .
make
echo "+++++++  build success!"
echo "+++++++  ........run"
./Program
