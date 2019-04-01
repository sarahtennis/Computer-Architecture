##### Objective
Write an emulator for an 8-bit computer with 8-bit memory addressing

##### Example
```
# print8.ls8: Print the number 8 on the screen

10000010 # LDI R0,8
00000000
00001000
01000111 # PRN R0
00000000
00000001 # HLT
```

##### Files
- examples - sample programs to run on emulator
- cpu.c - represents CPU for 8-bit computer (ls8.c)
  - TODO: initialize CPU struct
  - TODO: refactor cpu_load, read file after cpu_init()
  - TODO: additional ALU options
  - TODO: complete cpu_run()
- cpu.h - header file for cpu.c 
- ls8.c - represents 8-bit computer