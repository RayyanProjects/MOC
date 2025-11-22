# MOC (My Own Compiler) Project
MOC is a basic compiler written in C++ - made to learn compilers beyond *theory*.

**Requirements:**
  - g++
  - Make (or compile it by hand)
  - NASM assembler
  - ld linker (GNU binutils)
  - Linux (currently supported target)

You need to write a program in the examples/ dir with the .moc extension

## Build & Run
```
$ git clone https://github.com/RayyanProjects/MOC
$ cd MOC
$ make run
```
  
For now it's supporting declaring variables and a builtin exit function as shown in examples/main.moc, after running ./out you can check the exit code for confimation as it will exit with the same value in main.moc:

example/main.moc:
```
let x = 46;
let y = 123;
let z = x;
exit(z);
```

```
$ ./out
$ echo $?
$ 46
```


You can also check out.asm after running the compiler to see the generated x86_64 code.
## Build & Run
```
$ git clone https://github.com/RayyanProjects/MOC
$ cd MOC
$ make run
```
  
For now it's supporting declaring variables and a builtin exit function as shown in examples/main.moc.

example/main.moc:
```
let x = 46;
let y = 123;
let z = x;
exit(z);
```
Now run the output binary and check exit code.
```
$ ./out
$ echo $?
$ 46
```

You can also check out.asm after running the compiler to see the generated x86_64 code.
