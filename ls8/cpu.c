#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
      // From print8.ls8
      0b10000010, // LDI R0,8
      0b00000000,
      0b00001000,
      0b01000111, // PRN R0
      0b00000000,
      0b00000001 // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->ram[address++] = data[i];
  }

  // initialize PC
  cpu->PC = &cpu->ram[0];

  // initialize PC register
  cpu->registers[0] = cpu->PC;

  // initialize IR instruction register
  cpu->registers[1] = &(cpu->PC);

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
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    break;

    // TODO: implement more ALU ops
  }
}

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
    unsigned char instruction = cpu->registers[1];

    // Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    switch (instruction)
    {
    // LDI
    // Set the value of a register to an integer.
    case LDI:
      int reg = cpu->ram[(cpu->registers[0]) + 1];
      int value = cpu->ram[(cpu->registers[0]) + 2];

      cpu->registers[reg] = value;
    }
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
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
 * 
 * unsigned char *PC;
 * unsigned char **registers;
 * unsigned char **ram;
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
  cpu->registers[6] = &cpu->ram[0xF4];
}
