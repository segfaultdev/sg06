#include <sgforth.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

entry_t *globals = NULL;
int global_count = 0;

macro_t *macros = NULL;
int macro_count = 0;

int label_count = 0;

entry_t *token_queue = NULL;

int token_read = 0;
int token_write = 0;

static int is_space(char c) {
  return (isspace(c) || c == ',');
}

static void sg_push(const char *token) {
  strcpy(token_queue[token_write].name, token);
  token_write = (token_write + 1) % TOKEN_QUEUE;
}

int sg_token(FILE *file, char *buffer) {
  if (token_read != token_write) {
    strcpy(buffer, token_queue[token_read].name);
    token_read = (token_read + 1) % TOKEN_QUEUE;
    
    return 1;
  }
  
  char *old_buffer = buffer;
  int in_string = 0;
  
  char c = ' ';
  
  while (c != EOF && is_space(c)) {
    c = fgetc(file);
    
    if (c == ';') {
      while (c != EOF && c != '\n') c = fgetc(file);
    }
  }
  
  if (c == EOF) return 0;
  
  while (c != EOF && (!is_space(c) || in_string)) {
    if (c == '"') {
      in_string = !in_string;
    } else if (!in_string) {
      if (c == ';') {
        while (c != EOF && c != '\n') c = fgetc(file);
        continue;
      }
    }
    
    *(buffer++) = c;
    
    c = fgetc(file);
  }
  
  if (c == EOF) return 0;
  *buffer = '\0';
  
  while (c != EOF && is_space(c)) {
    c = fgetc(file);
    
    if (c == ';') {
      while (c != EOF && c != '\n') c = fgetc(file);
    }
  }
  
  if (c != EOF) ungetc(c, file);
  
  for (int i = 0; i < macro_count; i++) {
    if (!strcmp(macros[i].name, old_buffer)) {
      for (int j = 0; j < macros[i].count; j++) {
        sg_push(macros[i].tokens[j].name);
      }
      
      return sg_token(file, old_buffer);
    }
  }
  
  return 1;
}

static void sg_parse_raw(FILE *file, FILE *output) {
  char buffer[64];
  
  while (sg_token(file, buffer)) {
    fprintf(output, "  ; TOKEN: '%s'\n", buffer);
    if (!strcmp(buffer, "then")) break;
    
    if (!strcmp(buffer, "+") || !strcmp(buffer, "^")) {
      // load, decrease and save stack pointer
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // get stack pointer into x
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // read value at stack pointer to b
      fprintf(output, "  mov b, [x]\n");
      
      // save b to 0x20FD
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov [x], b\n");
      
      // decrease and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // get stack pointer into x
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // read value at stack pointer to b
      fprintf(output, "  mov b, [x]\n");
      
      // load a with the value at 0x20FD
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov a, [x]\n");
      
      // store sum/xor into b(by using 0x20FD already set in x)
      fprintf(output, "  mov [x], (a %c b)\n", *buffer);
      fprintf(output, "  mov b, [x]\n");
      
      // get stack pointer into x
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // store b at stack pointer
      fprintf(output, "  mov [x], b\n");
      
      // increase and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0x01\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "~")) {
      // get stack pointer minus 1 into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov l, (a + b)\n");
      
      // read value at stack pointer to b
      fprintf(output, "  mov b, [x]\n");
      
      // clear value at stack pointer
      fprintf(output, "  mov a, 0x00\n");
      fprintf(output, "  mov [x], a\n");
      
      int label = label_count++;
      
      // compare b with 0 and do jump if not equal(we use "mne" instead of "mov" as we want to preserve x if a and b are equal)
      fprintf(output, "  mne x, @label_%d\n", label);
      fprintf(output, "  jne x\n", label);
      
      // set value at stack pointer to 1
      fprintf(output, "  mov a, 0x01\n");
      fprintf(output, "  mov [x], a\n");
      
      // declare label
      fprintf(output, "@label_%d:\n", label);
    } else if (!strcmp(buffer, "@")) {
      // get stack pointer minus 1 into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov l, (a + b)\n");
      
      // read value at stack pointer to 0x20FD
      fprintf(output, "  mov b, [x]\n");
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov [x], b\n");
      
      // save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // get stack pointer minus 1 into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov l, (a + b)\n");
      
      // read value at stack pointer to 0x20FB
      fprintf(output, "  mov b, [x]\n");
      fprintf(output, "  mov l, 0xFB\n");
      fprintf(output, "  mov [x], b\n");
      
      // save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // read 0x20FB to b
      fprintf(output, "  mov l, 0xFB\n");
      fprintf(output, "  mov b, [x]\n");
      
      // now b contains the lower part and 0x20FD the higher one
      
      // read 0x20FD into a
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov a, [x]\n");
      
      // set the address and read into b
      fprintf(output, "  mov h, a\n");
      fprintf(output, "  mov l, b\n");
      fprintf(output, "  mov b, [x]\n");
      
      // get stack pointer into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // store value at stack pointer
      fprintf(output, "  mov [x], b\n");
      
      // increase and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0x01\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "!")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      char *end;
      uint8_t value = strtol(value_raw, &end, 0);
      
      if (end == value_raw + strlen(value_raw)) {
        // get stack pointer minus 1 into x
        fprintf(output, "  mov x, 0x20FC\n");
        fprintf(output, "  mov a, [x]\n");
        fprintf(output, "  mov b, 0xFF\n");
        fprintf(output, "  mov l, (a + b)\n");
        
        // read value at stack pointer to 0x20FD
        fprintf(output, "  mov b, [x]\n");
        fprintf(output, "  mov l, 0xFD\n");
        fprintf(output, "  mov [x], b\n");
        
        // save new stack pointer
        fprintf(output, "  mov l, 0xFC\n");
        fprintf(output, "  mov b, 0xFF\n");
        fprintf(output, "  mov [x], (a + b)\n");
        
        // get stack pointer minus 1 into x
        fprintf(output, "  mov x, 0x20FC\n");
        fprintf(output, "  mov a, [x]\n");
        fprintf(output, "  mov b, 0xFF\n");
        fprintf(output, "  mov l, (a + b)\n");
        
        // get stack pointer minus 1 into x
        fprintf(output, "  mov x, 0x20FC\n");
        fprintf(output, "  mov a, [x]\n");
        fprintf(output, "  mov b, 0xFF\n");
        fprintf(output, "  mov l, (a + b)\n");
        
        // read value at stack pointer to 0x20FB
        fprintf(output, "  mov b, [x]\n");
        fprintf(output, "  mov l, 0xFB\n");
        fprintf(output, "  mov [x], b\n");
        
        // save new stack pointer
        fprintf(output, "  mov l, 0xFC\n");
        fprintf(output, "  mov b, 0xFF\n");
        fprintf(output, "  mov [x], (a + b)\n");
        
        // read 0x20FB to b
        fprintf(output, "  mov l, 0xFB\n");
        fprintf(output, "  mov b, [x]\n");
        
        // now b contains the byte to write and 0x20FD the low part of the address
        
        // read 0x20FD into a
        fprintf(output, "  mov l, 0xFD\n");
        fprintf(output, "  mov a, [x]\n");
        
        // set address and write to it
        fprintf(output, "  mov h, %d\n", value);
        fprintf(output, "  mov l, a\n");
        fprintf(output, "  mov [x], b\n");
      } else {
        // TODO: error
      }
    } else if (!strcmp(buffer, "?")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      // set address and read to b
      fprintf(output, "  mov x, %s\n", value_raw);
      fprintf(output, "  mov b, [x]\n");
      
      // get stack pointer into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // store value at stack pointer
      fprintf(output, "  mov [x], b\n");
      
      // increase and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0x01\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "=")) {
      // get stack pointer minus 1 into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov l, (a + b)\n");
      
      // read value at stack pointer to 0x20FD
      fprintf(output, "  mov b, [x]\n");
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov [x], b\n");
      
      // save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // read 0x20FD to b
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov b, [x]\n");
      
      char value_raw[64];
      sg_token(file, value_raw);
      
      // set address and write to it
      fprintf(output, "  mov x, %s\n", value_raw);
      fprintf(output, "  mov [x], b\n");
    } else if (!strcmp(buffer, "drop")) {
      // load, decrease and save stack pointer
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "halt")) {
      // halt
      fprintf(output, "  hlt\n");
    } else if (!strcmp(buffer, "dup")) {
      // get stack pointer minus 1 into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov l, (a + b)\n");
      
      // read value at stack pointer to b
      fprintf(output, "  mov b, [x]\n");
      
      // get stack pointer into x
      fprintf(output, "  mov l, a\n");
        
      // store value in b at stack pointer
      fprintf(output, "  mov [x], b\n");
      
      // increase and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0x01\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "if")) {
      // get stack pointer minus 1 into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov l, (a + b)\n");
      
      // read value at stack pointer to 0x20FD
      fprintf(output, "  mov b, [x]\n");
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov [x], b\n");
      
      // save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // read 0x20FD to b
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov b, [x]\n");
      
      int label = label_count++;
      
      // jump to end if 0
      fprintf(output, "  mov a, 0x00\n");
      fprintf(output, "  meq x, @label_%d\n", label);
      fprintf(output, "  jeq x\n");
      
      // if statement inner code
      sg_parse_raw(file, output);
      
      // add end label
      fprintf(output, "@label_%d:\n", label);
    } else if (!strcmp(buffer, "while")) {
      int label_1 = label_count++;
      int label_2 = label_count++;
      
      // starting label
      fprintf(output, "@label_%d:\n", label_1);
      
      // get stack pointer minus 1 into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov l, (a + b)\n");
      
      // read value at stack pointer to 0x20FD
      fprintf(output, "  mov b, [x]\n");
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov [x], b\n");
      
      // save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // read 0x20FD to b
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov b, [x]\n");
      
      // jump to end if 0
      fprintf(output, "  mov a, 0x00\n");
      fprintf(output, "  meq x, @label_%d\n", label_2);
      fprintf(output, "  jeq x\n");
      
      // while statement inner code
      sg_parse_raw(file, output);
      
      // jump to start
      fprintf(output, "  mov x, @label_%d\n", label_1);
      fprintf(output, "  jmp x\n");
      
      // add end label
      fprintf(output, "@label_%d:\n", label_2);
    } else if (!strcmp(buffer, "let")) {
      sg_token(file, buffer);
      
      for (int i = 0; i < global_count; i++) {
        if (!strcmp(globals[i].name, buffer)) {
          printf("error: global '%s' already exists\n", buffer);
          exit(1);
        }
      }
      
      globals = realloc(globals, (global_count + 1) * sizeof(entry_t));
      strcpy(globals[global_count++].name, buffer);
      
      char value_raw[64];
      sg_token(file, value_raw);
      
      char *end;
      uint8_t value = strtol(value_raw, &end, 0);
      
      if (end == value_raw + strlen(value_raw)) {
        // jump to after the global variable
        fprintf(output, "  mov x, @global_end_%s\n", buffer);
        fprintf(output, "  jmp x\n");
        
        fprintf(output, "%s:\n", buffer);
        fprintf(output, "  db %d\n", value);
        fprintf(output, "@global_end_%s:\n", buffer);
      } else {
        // TODO: error
      }
    } else if (!strcmp(buffer, "ptr")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      // set b to lower part
      fprintf(output, "  mov d, %s\n", value_raw);
      fprintf(output, "  mov b, a\n");
      
      // get stack pointer into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // store b at stack pointer
      fprintf(output, "  mov [x], b\n");
      
      // increase and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0x01\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // set b to higher part
      fprintf(output, "  mov d, %s\n", value_raw);
      
      // get stack pointer into x
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // store b at stack pointer
      fprintf(output, "  mov [x], b\n");
      
      // increase and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0x01\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "macro")) {
      macro_t macro;
      sg_token(file, macro.name);
      
      macro.tokens = NULL;
      macro.count = 0;
      
      while (sg_token(file, buffer)) {
        if (!strcmp(buffer, "end")) break;
        
        macro.tokens = realloc(macro.tokens, (macro.count + 1) * sizeof(entry_t));
        strcpy(macro.tokens[macro.count++].name, buffer);
      }
      
      macros = realloc(macros, (macro_count + 1) * sizeof(macro_t));
      macros[macro_count++] = macro;
    } else {
      char *end;
      uint8_t value = strtol(buffer, &end, 0);
      
      if (end == buffer + strlen(buffer)) {
        // get stack pointer into x
        fprintf(output, "  mov x, 0x20FC\n");
        fprintf(output, "  mov a, [x]\n");
        fprintf(output, "  mov l, a\n");
        
        // store value at stack pointer
        fprintf(output, "  mov b, %d\n", value);
        fprintf(output, "  mov [x], b\n");
        
        // increase and save new stack pointer
        fprintf(output, "  mov l, 0xFC\n");
        fprintf(output, "  mov b, 0x01\n");
        fprintf(output, "  mov [x], (a + b)\n");
      }
    }
  }
}

void sg_parse(const char *path, FILE *output) {
  FILE *file = fopen(path, "r");
  
  if (!file) {
    printf("error: cannot open file: '%s'\n", path);
    exit(1);
  }
  
  sg_parse_raw(file, output);
  fclose(file);
}

int main(void) {
  token_queue = malloc(TOKEN_QUEUE * sizeof(entry_t));
  printf("org 0x0000\n\n");
  
  printf("@start:\n");
  printf("  ; CLEAR STACK POINTER\n");
  printf("  mov x, 0x20FC\n");
  printf("  mov a, 0x00\n");
  printf("  mov [x], a\n");
  
  sg_parse("test.fth", stdout);
  
  return 0;
}
