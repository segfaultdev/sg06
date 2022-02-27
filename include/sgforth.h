#ifndef __SG_FORTH_H__
#define __SG_FORTH_H__

#include <stdio.h>

#define TOKEN_STACK 1024

// +, ^, *, carry, <, &, |, shl, shr, ~, read, @ [NAME/ADDR], ! [NAME/ADDR], ? [NAME/ADDR], = [NAME/ADDR], dup, drop, swap, halt, if-then, while-then, asm [STRING], let [NAME], ptr [NAME/ADDR], lsb [NAME/ADDR]

// the stack sgforth uses by default uses the hardware acceleration expansion
// *, carry, <, &, |, shl and shr use the hardware acceleration expansion

// if and while work when the top value is not 0
// ~ will push 1 if 0, or 0 otherwise
// * and ptr will first push the lower byte, and read will first pop the higher byte
// @ and ! will first pop the lower byte(! will also pop the value when writing), and take the higher one from the constant address or label specified AFTER the operator
// ? and = should be used for reading/writing to fixed addresses or globals, where you push the value(if writing), then place the operator and THEN the variable name or constant address (:

// macros: working! (macro [NAME] ... end)
// include: working! (include "path/to/file.fth")
// incasm: working!

typedef struct entry_t entry_t;
typedef struct macro_t macro_t;

struct entry_t {
  char name[128];
};

struct macro_t {
  char name[128];
  
  entry_t *tokens;
  int count;
};

int  sg_token(FILE *file, char *buffer);
void sg_parse(const char *path);

#endif
