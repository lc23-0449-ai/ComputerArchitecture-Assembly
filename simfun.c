#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

  /*
  
0b000 BRA imm - jump to instruction at next PC + imm. 

0b001 BZ x1 = 0 imm. - jump to instr. at next PC unless x1 is zero,
 in whcih case go to next PC + imm
0b001 imm,50


0b010 LD R, [S] - load register R with content of memory from register S
0b010 0,54, S,32 R,10


0b011 LDI X0, imm - load X0 with immediate value of imm
0b011 imm,50

0b100 ST R, [S] - store content of register R into the adress in memory 
from register S
0b100 0,54 S,32 R,10


0b101 ADD R, S - adds content of reg R and S and stores into register R
0b101 0,54 S,32 R,10

0b111 0b00000 HLT - stops the machine // ends while loop 

   */

int decode( int pc, uint8_t * mem, uint8_t * regs){  //returns updated PC 

  uint8_t insB;
  uint8_t f1,f2;
  printf("Mem[pc]: %hhd\n",mem[pc]);
  insB = (mem[pc] >> 5) & 0x7;
  printf("InsB: %hhd\n",insB);
  if(insB == 0){ //jump to next PC instruction
    f1 = ((mem[pc] << 3) >> 3 ) & 0x1F;
    printf("F1: %hhd\n",f1);
    return pc + 1 + f1;
  }
  else if(insB == 1){  //conditional jump if register x1 = 0;
    if(regs[1] == 0){
      if (f1 & 0x10) {  // need check to see if imm is negative
	f1 = f1 | 0xFFFFFFFE0;  // fill upper bits with 1s
      }
      else{
	f1 = ((mem[pc] << 3) >>3) & 0x1F;
      }
      return pc + 1 + f1;
    }
    else{
      return pc + 1;
    }
  }
  else if(insB == 2){  //Load register R with content of memory from register S
    f1 = ((mem[pc] >>2)) & 0x3;
    uint8_t R = f1;
    f2 = ((mem[pc])) & 0x3;
    uint8_t S = f2;
    regs[R] = mem[regs[S]];
    return pc + 1;
  }
  else if(insB == 3){  //Load register X0 with immediate value of imm

    if (f1 & 0x10) {  // need check to see if imm is negative
      f1 = f1 | 0xFFFFFFFE0;  // fill upper bits with 1s
    }
    else{
      f1 = ((mem[pc] << 3)>>3) & 0x1F;
    }
    
    regs[0] = f1;
    return pc + 1;
  }
  else if(insB == 4){  //store content of reg R into address in mem from reg S
    f1 = ((mem[pc] >>2)) & 0x3;
    int R = f1;
    f2 = ((mem[pc])) & 0x3;
    int S = f2;
    mem[regs[S]] = regs[R];
    return pc + 1;
  }
  else if(insB == 5){ //Add content of register R and s and stores in register R
    f1 = ((mem[pc] >>2)) & 0x3;
    int R = f1;
    f2 = ((mem[pc])) & 0x3;
    int S = f2;
    regs[R] = regs[R] + regs[S];
    return pc + 1;
  }
  else if(insB == 7){  //HLT return 0 
    return -1;
  }
  else return pc+1;
}



int main(){

  //init (memory, registers, prg );
  uint8_t regs[4] = {0};
  uint8_t memory[256] = {0};
  int pc = 0; int ip = 0;

  
  int i = 0;
  while(fread(&memory[i], 1, 1, stdin) == 1){
    i++;
  }
  printf("PC: %d\n",pc);
  pc = decode(pc,memory,regs);
  ip = pc;
  
  while (pc >= 0){
    pc = decode(pc,memory,regs);
    if(pc >= 0){ ip = pc;}
    printf("PC: %d\n",pc);
  }

  
  printf("HLT encountered at PC = %d\n",ip);
  printf("PC: 0 --> %d\n",ip);
  if(regs[0] != 0){printf("X0: 0 --> %hhd\n",regs[0]);}
  if(regs[1] != 0){printf("X1: 0 --> %hhd\n",regs[1]);}
  if(regs[2] != 0){printf("X2: 0 --> %hhd\n",regs[2]);}
  if(regs[3] != 0){printf("X3: 0 --> %hhd\n",regs[3]);}
  if(memory[2] != 0){printf("Mem[2]: 0 --> %hhd\n",memory[2]);}
}
