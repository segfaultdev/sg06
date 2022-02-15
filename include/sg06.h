#ifndef __SG06_H__
#define __SG06_H__

#include <stdint.h>

typedef struct sg06_t sg06_t;
typedef struct entry_t entry_t;

struct sg06_t {
  uint8_t a, b;
  uint16_t x, y;
  
  uint8_t *data;
  int halt;
};

struct entry_t {
  char name[64];
  size_t offset;
  
  int part;
};

extern entry_t *labels;
extern int label_count;

extern entry_t *refers;
extern int refer_count;

void sg_init(sg06_t *state, const char *path);
void sg_free(sg06_t *state);
void sg_tick(sg06_t *state);

void sg_byte(FILE *output, uint8_t byte);

int  sg_token(FILE *file, char *buffer);
void sg_parse(const char *path, FILE *output);
void sg_solve(FILE *output);

uint8_t sg_read(sg06_t *state, uint16_t addr);
void    sg_write(sg06_t *state, uint16_t addr, uint8_t value);

#endif
