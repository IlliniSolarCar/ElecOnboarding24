### DAY TWO ###
## author : Noah Breit

# NEEDED
1. C/C++ Toolchain and VSCode environment setup
  - See Day One Folder

# LEARN TO BUILD
1. OPTIONAL -- Read Text
  - pdf is provided
  - Embedded Programming Textbook; https://www.bogotobogo.com/cplusplus/files/embed/OReilly_Programming_Embedded_Systems_Second_edition_ebook.pdf
  - `read Chapter 4, pages 57-62. this will explain (better than I can) how C, C++, and high level programming languages in general actually 'run' on machines`
  - feel free to explore the remainder of Chapter 4 and the textbook. I recommend chapters 1-3.

2. Summary
  - pdf is provided
  - `Geeks 4 Geeks G++ Guide; https://www.geeksforgeeks.org/compiling-with-g-plus-plus/`
  - Geeks 4 Geeks Quick Compiler Explanation; https://www.geeksforgeeks.org/introduction-to-compilers/
  - note : options described in guide are the same for clang toolchain (mac users) 

3. Using g++
  - `follow Geeks 4 Geeks tutorial and make the following output with g++: assembly output, object output, and an executable`
      hello.s               (assembly file)
      hello.o helloWorld.o  (object file)
      main.exe              (executable)

  - format : [g++|clang] [options] [input] [output]
  - example : "g++ hello.o helloWorld.o -o main" --> main

  - note : geeksforgeeks guide writes "g++ -o main hello.o helloWorld.o"
    - while this format is accepted by g++, please avoid this. it is best to define the output file last
  - note : .exe file extension is the implied default extension on windows devices
  - note : if no output file is given, output file will be [input] + new file extension depending on compiler flags
    - example : g++ -c hello.cpp --> hello.o

4. Build Optimizing Fun
  - TODO : INSTRUCTIONS BELOW FOR MAC TO INSTALL BINUTILS (mac users)
  - binutils libref: https://www.gnu.org/software/binutils/
  - `use "size" "objdump" "file" commands to interact with otherwise difficult object files and executables`
    - example : "file hello.o" -->
        .\hello.o: Intel amd64 COFF object file, no line number info, not stripped, 9 sections, symbol offset=0x3ca, 33 symbols, 
        1st section name ".text"
    
    - ^ explanation : hello.o is defined this way because my laptop has an intel i7, 64-bit system. so, the compiler recognized 
                      this and defined the obj file to be compatable (Intel amd64 COFF object file).

    - example : "size hello.o" -->
        text    data     bss    dec    hex  filename
        352       8      16     376    178  .\hello.o
    
    - ^ explanation : hello.o is a COFF object file, one of two common obj file types (other being ELF format). Both formats follow
                      the similar structure of 'text' 'data' 'bss' sections. 'dec' 'hex' are the total file size (by line) of input 
                      file in decimal and hexadecimal respectively.
      'text' is the program + data to create an executable
      'data' is initialized variables
      'bss' is unititalized variables

    - example: "objdump -S hello.o" --> print original source code (in assembly) to the best of the tool's abilities.
    - example: "objdump -i hello.o" --> print data formats found in obj file
    - example: "objdump -f hello.o" --> print main header of obj file
    - example: "objdump -x hello.o" --> print all headers of obj file

    - note :  objdump is a basic disassembler able to translate binaries (obj files and executables) into human-readable assembly.
              I included it as a fun tool to play with. We will most likely never use it at solarcar. But, disassemblers are fundamental to cybersecurity, hacking, etc. So if you enjoy it, consider looking into those fields.
    
  - `try to make the most optimized output (smallest assembly file, objfile and executable) while preserving the output serial text.` 
  - hint : change original .cpp files and/or manipulate g++|clang options (google g++ optimization flags?)
