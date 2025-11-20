# MOC (My Own Compiler) Project
MOC is a basic compiler written in C++ - made to learn compilers beyond *theory* (the way most universities teach compilers)

**Requirements:**
  - g++
  - NASM assembler
  - ld linker (GNU binutils)
  - Linux (currently supported target)
You need to write a program in the examples/ dir with the .moc extension

## Build & Run
  `git clone https://github.com/RayyanProjects/MOC`
  
  `cd MOC`
  
  `make run`
For now it's supporting an exit function as shown in examples/exit.moc, after running ./out you can check the exit code for confimation as it will exit with the same value in exit.moc:
  `./out`
  
  `echo $?`
  
  `255`
