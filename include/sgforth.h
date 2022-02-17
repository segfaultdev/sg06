#ifndef __SG_FORTH_H__
#define __SG_FORTH_H__

#include <stdio.h>

// 0x2000 - 0x20FB: stack
// 0x20FC - 0x20FC: stack pointer
// 0x20FD - 0x20FF: temp. data

// +, ^, ~(TODO), @(TODO), !(TODO), dup, swap(TODO), rot(TODO), drop, halt, if-end(TODO), while-end(TODO), let [NAME](TODO), ptr [NAME or ADDR](TODO)

// if and while work when the top value is 0, not 1
// ~ will push 1 if 0, or 0 otherwise

int  sg_token(FILE *file, char *buffer);
void sg_parse(const char *path, FILE *output);

#endif
