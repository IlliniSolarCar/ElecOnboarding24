#!/bin/bash

unzip project_files.zip

cp project_files/mbed/.*project mbed
cp project_files/common/.*project common
cp project_files/wheel/.*project wheel
cp project_files/blinky/.*project blinky
rm -r project_files
echo "Common, wheel, and MBED Project files updated"