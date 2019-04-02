#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, int argc, char **argv)
{
  // ----------------------------
  // char data[DATA_LEN] = {
  //     // From print8.ls8
  //     0b10000010, // LDI R0,8
  //     0b00000000,
  //     0b00001000,
  //     0b01000111, // PRN R0
  //     0b00000000,
  //     0b00000001 // HLT
  // };

  // int address = 0;
  // for (int i = 0; i < DATA_LEN; i++)
  // {
  //   cpu->ram[address++] = data[i];
  // }

  // cpu->registers[3] = cpu->PC;
  // ---------------------------

  // declare file pointer
  FILE *fp;

  // holder for current instruction
  char instruction[256];

  // if anything but 2 args in command line, exit
  if (argc != 2)
  {
    printf("Usage: cpu filename\n");
    exit(EXIT_FAILURE);
  }

  // open file
  // printf("argv[1]: %s\n", argv[1]);
  fp = fopen(argv[1], "r");

  // if file pointer is null, exit
  if (fp == NULL)
  {
    printf("Error opening file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  int address = 0;

  while (fgets(instruction, 256, fp) != NULL)
  {
    unsigned char value = strtoul(instruction, NULL, 2);
    // printf("instruction: %x\n", value);
    cpu->ram[address++] = value;
  }

  fclose(fp);

  // initialize PC
  cpu->registers[3] = cpu->PC;

  // initialize stack head and update SP?

  // TODO: Replace this with something less hard-coded
}

/**
 * Read ram inside struct cpu
 **/
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char index)
{
  return cpu->ram[index];
};

/**
 * Write to ram inside struct cpu
 **/
void cpu_ram_write(struct cpu *cpu, unsigned char index, unsigned char value)
{
  cpu->ram[index] = value;
};

/**
 * Arithmetic logic unit, ALU
 */
// void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
// {
//   switch (op)
//   {
//   case ALU_MUL:
//     // TODO
//     break;

//     // TODO: implement more ALU ops
//   }
// }

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running)
  {
    // Get the value of the current instruction
    // (in address PC).
    unsigned char currentPC = cpu->registers[3];
    unsigned char instruction = cpu->ram[currentPC];
    // printf("PC: %d - instruction: %x\n", currentPC, instruction);
    // break;

    // Figure out how many operands this next instruction requires
    // AABCDDDD ---> AA is number of operands
    int countOperands = instruction >> 6;
    // printf("# operands: %d\n", countOperands);

    // Get the appropriate value(s) of the operands following this instruction
    int operandA = 0;
    int operandB = 0;

    if (countOperands == 1)
    {
      operandA = cpu->ram[currentPC + 1];
    }

    if (countOperands == 2)
    {
      operandB = cpu->ram[currentPC + 2];
    }

    // printf("operandA: %d, operandB: %d\n", operandA, operandB);

    // switch() over it to decide on a course of action.
    // Do whatever the instruction should do according to the spec.
    switch (instruction)
    {
    // LDI: Set value of register (operandA) to integer (operandB)
    case LDI:
      cpu->registers[operandA] = operandB;
      break;

    // PRN : print value stored in given register to console
    case PRN:
      printf("%d\n", cpu->registers[operandA]);
      break;

    case HLT:
      running = 0;
      break;

    default:
      printf("ERROR: Invalid instruction");
      running = 0;
      break;
    }

    // Move the PC to the next instruction.
    // printf("pc before: %d\n", cpu->PC);
    cpu->PC = (cpu->PC) + countOperands + 1;
    cpu->registers[3] = cpu->PC;
    // printf("pc after: %d\n", cpu->PC);
  }
}

/**
 * Initialize a CPU struct
 * PC, registers, and RAM should be cleared to zero
 * 
 * R0-R6 are cleared to 0.
 * R7 is set to 0xF4.
 * PC and FL registers are cleared to 0.
 * RAM is cleared to 0.
 */
void cpu_init(struct cpu *cpu)
{
  // Initialize the PC to 0
  cpu->PC = 0;

  // ram and registers to 0
  memset(cpu->ram, 0, sizeof(cpu->ram));
  memset(cpu->registers, 0, sizeof(cpu->registers));

  // initialize special registers
  // R7 --> stack pointer (SP)
  // SP points at the value at the top of the stack
  // (most recently pushed), or at address F4 if the
  // stack is empty.
  // cpu->registers[6] = &cpu->ram[0xF4];
}
