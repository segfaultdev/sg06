#ifndef __SG_FORTH_H__
#define __SG_FORTH_H__

#include <stdio.h>

#define TOKEN_QUEUE 128

// 0x2000 - 0x20EF: stack
// 0x20F0 - 0x20FB: internal temp. data
// 0x20FC - 0x20FC: stack pointer
// 0x20FD - 0x20FD: (more) internal temp. data
// 0x20FE - 0x20FF: external temp. data for macros and such

// +, ^, ~, @, ! [PAGE], ? [NAME/ADDR], = [NAME/ADDR], dup, swap(TODO), rot(TODO), drop, halt, if-then, while-then, let [NAME] [VALUE], ptr [NAME/ADDR]

// if and while work when the top value not 0
// ~ will push 1 if 0, or 0 otherwise
// ptr will first push the lower byte
// HUGE NOTE: ! reads an 8-bit address(the byte to write is pushed before the address), as the upper 8 bits are fixed(and passed AFTER the operator)
// ANOTHER HUGE NOTE: ? and = should be used for reading/writing to fixed addresses or globals, where you push the value(if writing), then place the operator and THEN the variable name or constant address (:

// macros: working! (macro [NAME] ... end)
// include: TODO ):

typedef struct entry_t entry_t;
typedef struct macro_t macro_t;

struct entry_t {
  char name[64];
};

struct macro_t {
  char name[64];
  
  entry_t *tokens;
  int count;
};

int  sg_token(FILE *file, char *buffer);
void sg_parse(const char *path, FILE *output);

#endif
