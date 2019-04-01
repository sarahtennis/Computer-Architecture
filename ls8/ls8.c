#include <stdio.h>
#include "cpu.h"

/**
 * Main
 */
int main(void)
{
  struct cpu cpu;

  // clear ram & registers, initialize R7 to SP
  cpu_init(&cpu);

  // load program into RAM
  cpu_load(&cpu);

  cpu_run(&cpu);

  return 0;
}