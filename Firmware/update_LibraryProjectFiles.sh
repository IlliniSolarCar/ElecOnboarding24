#!/bin/bash

unzip project_files.zip

cp project_files/mbed/.*project mbed
cp project_files/common/.*project common
rm -r project_files
echo "Common and MBED Project files updated"