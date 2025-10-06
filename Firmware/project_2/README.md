This is an example project that has all of the configuration settings and files
needed to run code on an LPC1549 microcontroller
using the
[mbed SDK](http://mbed.org/handbook/mbed-SDK).

The main source code is contained under the `src` directory. Header files are in
the `inc` directory.

`linkscripts` contains a custom [linker script](http://en.wikipedia.org/wiki/GNU_linker)
template. You shouldn't need to modify it.

`src/main.cpp` contains the main program file that you'll use. 
`src/pins.cpp` and `src/peripherals.cpp` are supplemental files used to split up the code into
manageable chunks. Do add your own files to help keep the code manageable.

pins.cpp is used for declaring pins and pin based input/outputs. 
peripherals.cpp is used to declare more abstract objects such as instances of ICs, communications busses, etc. 
