#include <sgforth.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define sg_output(...) {char line_buffer[128]; sprintf(line_buffer, __VA_ARGS__); sg_output_raw(line_buffer);}

macro_t *macros = NULL;
int macro_count = 0;

entry_t *incasms = NULL;
int incasm_count = 0;

int global_count = 0;
int label_count = 0;

entry_t *token_stack = NULL;
int token_count = 0;

entry_t *lines = NULL;
int line_count = 0;

static int is_space(char c) {
  return (isspace(c) || c == ',');
}

static void sg_push(const char *token) {
  strcpy(token_stack[token_count++].name, token);
}

static void sg_pop(char *buffer) {
  strcpy(buffer, token_stack[--token_count].name);
}

static void sg_output_raw(const char *line) {
  lines = realloc(lines, (line_count + 1) * sizeof(entry_t));
  strcpy(lines[line_count++].name, line);
}

static void sg_codegen(FILE *output) {
  entry_t *new_lines = NULL;
  int new_line_count = 0;
  
  int saved_1 = 0;
  int saved_2 = 0;
  int saved_3 = 0;
  int saved_4 = 0;
  int saved_5 = 0;
  int saved_6 = 0;
  
  for (int i = 0; i < line_count; i++) {
    if (i < line_count - 1) {
      if ((!strcmp(lines[i + 0].name, "mov [x], a") && !strcmp(lines[i + 1].name, "mov a, [x]")) ||
          (!strcmp(lines[i + 0].name, "mov [x], b") && !strcmp(lines[i + 1].name, "mov b, [x]"))) {
        if (!strcmp(lines[i + 0].name, "mov [x], a")) saved_1 += 2;
        else saved_2 += 2;
        
        i++;
        continue;
      } else if (!strcmp(lines[i + 0].name, "mov [x], a") && !strcmp(lines[i + 1].name, "mov b, [x]")) {
        new_lines = realloc(new_lines, (new_line_count + 1) * sizeof(entry_t));
        strcpy(new_lines[new_line_count++].name, "mov b, a");
        
        saved_3 += 1;
        
        i++;
        continue;
      } else if (!strcmp(lines[i + 0].name, "mov [x], b") && !strcmp(lines[i + 1].name, "mov a, [x]")) {
        new_lines = realloc(new_lines, (new_line_count + 1) * sizeof(entry_t));
        strcpy(new_lines[new_line_count++].name, "mov a, b");
        
        saved_4 += 1;
        
        i++;
        continue;
      }
    }
    
    if (i < line_count - 3) {
      if ((!strcmp(lines[i + 0].name, "mov [x], (a + b)") || !strcmp(lines[i + 0].name, "mov [x], (a ^ b)")) && (
          (!strcmp(lines[i + 1].name, "mov a, [x]") && !strcmp(lines[i + 2].name, "mov [x], a") && !strcmp(lines[i + 3].name, "mov [x], a")) ||
          (!strcmp(lines[i + 1].name, "mov b, [x]") && !strcmp(lines[i + 2].name, "mov [x], b") && !strcmp(lines[i + 3].name, "mov [x], b")))) {
        new_lines = realloc(new_lines, (new_line_count + 2) * sizeof(entry_t));
        strcpy(new_lines[new_line_count++].name, lines[i + 0].name);
        strcpy(new_lines[new_line_count++].name, lines[i + 0].name);
        
        if (!strcmp(lines[i + 1].name, "mov a, [x]")) saved_5 += 2;
        else saved_6 += 2;
        
        i += 3;
        continue;
      }
    }
    
    new_lines = realloc(new_lines, (new_line_count + 1) * sizeof(entry_t));
    new_lines[new_line_count++] = lines[i];
  }
  
  fprintf(stderr, "sgforth optimization report:\n");
  fprintf(stderr, "- %-5d: mov [x], a\n", saved_1);
  fprintf(stderr, "         mov a, [x]\n");
  fprintf(stderr, "- %-5d: mov [x], b\n", saved_2);
  fprintf(stderr, "         mov b, [x]\n");
  fprintf(stderr, "- %-5d: mov [x], a\n", saved_3);
  fprintf(stderr, "         mov b, [x]\n");
  fprintf(stderr, "- %-5d: mov [x], b\n", saved_4);
  fprintf(stderr, "         mov a, [x]\n");
  fprintf(stderr, "- %-5d: mov [x], (a +/^ b)\n", saved_5);
  fprintf(stderr, "         mov a, [x]\n");
  fprintf(stderr, "         mov [x], a\n");
  fprintf(stderr, "         mov [x], a\n");
  fprintf(stderr, "- %-5d: mov [x], (a +/^ b)\n", saved_6);
  fprintf(stderr, "         mov b, [x]\n");
  fprintf(stderr, "         mov [x], b\n");
  fprintf(stderr, "         mov [x], b\n");
  fprintf(stderr, "- %-5d: TOTAL\n", saved_1 + saved_2 + saved_3 + saved_4 + saved_5 + saved_6);
  
  for (int i = 0; i < new_line_count; i++) {
    fprintf(output, "%s%s\n", strchr(new_lines[i].name, ':') ? "" : "  ", new_lines[i].name);
  }
}

int sg_token(FILE *file, char *buffer) {
  if (token_count > 0) {
    sg_pop(buffer);
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
      for (int j = macros[i].count - 1; j >= 0; j--) {
        sg_push(macros[i].tokens[j].name);
      }
      
      return sg_token(file, old_buffer);
    }
  }
  
  return 1;
}

static void sg_incasm(const char *path) {
  incasms = realloc(incasms, (incasm_count + 1) * sizeof(entry_t));
  strcpy(incasms[incasm_count++].name, path);
}

static void sg_parse_raw(FILE *file) {
  char buffer[64];
  int x_is_stack = 0;
  
  while (sg_token(file, buffer)) {
    // sg_output("; TOKEN: '%s'", buffer);
    if (!strcmp(buffer, "then")) break;
    
    if (!strcmp(buffer, "+") || !strcmp(buffer, "^")) {
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
      sg_output("mov b, [x]");
      sg_output("mov [x], (a %c b)", *buffer);
    } else if (!strcmp(buffer, "carry") || !strcmp(buffer, "<") || !strcmp(buffer, "&") || !strcmp(buffer, "|") || !strcmp(buffer, "shl") || !strcmp(buffer, "shr")) {
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
      sg_output("mov b, [x]");
      
      if (!strcmp(buffer, "carry")) {
        sg_output("mov l, 0xF9");
        sg_output("mov [x], a");
        sg_output("mov l, 0xF8");
        sg_output("mov [x], b");
      } else {
        sg_output("mov l, 0xF8");
        sg_output("mov [x], b");
        sg_output("mov l, 0xF9");
        sg_output("mov [x], a");
        
        if (!strcmp(buffer, "&")) {
          sg_output("mov l, 0xFA");
        } else if (!strcmp(buffer, "|")) {
          sg_output("mov l, 0xFB");
        } else if (!strcmp(buffer, "shl")) {
          sg_output("mov l, 0xFC");
        } else if (!strcmp(buffer, "shr")) {
          sg_output("mov l, 0xFD");
        }
      }
      
      sg_output("mov a, [x] ; DONT_OPTIMIZE");
      sg_output("mov l, 0xF7");
      sg_output("mov [x], a");
    } else if (!strcmp(buffer, "*")) {
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
      sg_output("mov b, [x]");
      sg_output("mov l, 0xF8");
      sg_output("mov [x], a");
      sg_output("mov l, 0xF9");
      sg_output("mov [x], b");
      sg_output("mov l, 0xFE")
      sg_output("mov a, [x]");
      sg_output("mov l, 0xF7");
      sg_output("mov [x], a");
      sg_output("mov l, 0xFF")
      sg_output("mov a, [x]");
      sg_output("mov l, 0xF7");
      sg_output("mov [x], a");
    } else if (!strcmp(buffer, "~")) {
      int label_1 = label_count++;
      
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
      sg_output("mov b, 0x00");
      sg_output("mne x, @label_%d", label_1);
      sg_output("jne x");
      sg_output("mov b, 0x01");
      sg_output("@label_%d:", label_1);
      sg_output("mov x, 0xFFF7");
      sg_output("mov [x], b");
    } else if (!strcmp(buffer, "read")) {
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov b, [x]"); // high
      sg_output("mov a, [x]"); // low
      sg_output("mov h, b");
      sg_output("mov l, a");
      sg_output("mov a, [x]");
      sg_output("mov x, 0xFFF7");
      sg_output("mov [x], a");
    } else if (!strcmp(buffer, "@")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]"); // low
      sg_output("mov h, msb %s", value_raw);
      sg_output("mov l, a");
      sg_output("mov a, [x]");
      sg_output("mov x, 0xFFF7");
      sg_output("mov [x], a");
    } else if (!strcmp(buffer, "!")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]"); // low
      sg_output("mov b, [x]"); // value
      sg_output("mov h, msb %s", value_raw);
      sg_output("mov l, a");
      sg_output("mov [x], b");
      
      x_is_stack = 0;
    } else if (!strcmp(buffer, "?")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      sg_output("mov x, %s", value_raw);
      sg_output("mov a, [x]");
      sg_output("mov x, 0xFFF7");
      sg_output("mov [x], a");
      
      x_is_stack = 1;
    } else if (!strcmp(buffer, "=")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
      sg_output("mov x, %s", value_raw);
      sg_output("mov [x], a");
      
      x_is_stack = 0;
    } else if (!strcmp(buffer, "drop")) {
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
    } else if (!strcmp(buffer, "halt")) {
      sg_output("hlt");
    } else if (!strcmp(buffer, "dup")) {
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
      sg_output("mov [x], a");
      sg_output("mov [x], a");
    } else if (!strcmp(buffer, "swap")) {
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
      sg_output("mov b, [x]");
      sg_output("mov [x], a");
      sg_output("mov [x], b");
    } else if (!strcmp(buffer, "if")) {
      int label_1 = label_count++;
      
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, [x]");
      sg_output("mov b, 0x00");
      sg_output("meq x, @label_%d", label_1);
      sg_output("jeq x");
      
      sg_parse_raw(file);
      
      sg_output("@label_%d:", label_1);
      x_is_stack = 0;
    } else if (!strcmp(buffer, "while")) {
      int label_1 = label_count++;
      int label_2 = label_count++;
      
      sg_output("@label_%d:", label_1);
      sg_output("mov x, 0xFFF7");
      sg_output("mov a, [x]");
      sg_output("mov b, 0x00");
      sg_output("meq x, @label_%d", label_2);
      sg_output("jeq x");
      
      x_is_stack = 1;
      sg_parse_raw(file);
      
      sg_output("mov x, @label_%d", label_1);
      sg_output("jmp x");
      sg_output("@label_%d:", label_2);
      x_is_stack = 0;
    } else if (!strcmp(buffer, "let")) {
      macro_t macro;
      sg_token(file, macro.name);
      
      macro.tokens = malloc(sizeof(entry_t));
      macro.count = 1;
      
      sprintf(macro.tokens[0].name, "0x%04X", 0x2000 + global_count++);
      
      for (int i = 0; i < macro_count; i++) {
        if (!strcmp(macros[i].name, macro.name)) {
          fprintf(stderr, "error: global or macro with name '%s' already exists\n", buffer);
          exit(1);
        }
      }
      
      macros = realloc(macros, (macro_count + 1) * sizeof(macro_t));
      macros[macro_count++] = macro;
    } else if (!strcmp(buffer, "ptr")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov d, %s", value_raw);
      sg_output("mov [x], a");
      sg_output("mov [x], b");
    } else if (!strcmp(buffer, "lsb")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      if (!x_is_stack) {
        sg_output("mov x, 0xFFF7");
        x_is_stack = 1;
      }
      
      sg_output("mov a, lsb %s", value_raw);
      sg_output("mov [x], a");
    } else if (!strcmp(buffer, "macro")) {
      macro_t macro;
      sg_token(file, macro.name);
      
      macro.tokens = NULL;
      macro.count = 0;
      
      for (int i = 0; i < macro_count; i++) {
        if (!strcmp(macros[i].name, macro.name)) {
          fprintf(stderr, "error: global or macro with name '%s' already exists\n", buffer);
          exit(1);
        }
      }
      
      while (sg_token(file, buffer)) {
        if (!strcmp(buffer, "end")) break;
        
        macro.tokens = realloc(macro.tokens, (macro.count + 1) * sizeof(entry_t));
        strcpy(macro.tokens[macro.count++].name, buffer);
      }
      
      macros = realloc(macros, (macro_count + 1) * sizeof(macro_t));
      macros[macro_count++] = macro;
    } else if (!strcmp(buffer, "include")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      if (value_raw[0] == '"') {
        value_raw[strlen(value_raw) - 1] = '\0';
        sg_parse(value_raw + 1);
      } else {
        sg_parse(value_raw);
      }
    } else if (!strcmp(buffer, "incasm")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      if (value_raw[0] == '"') {
        value_raw[strlen(value_raw) - 1] = '\0';
        sg_incasm(value_raw + 1);
      } else {
        sg_incasm(value_raw);
      }
      
      x_is_stack = 0;
    } else if (!strcmp(buffer, "asm")) {
      char value_raw[64];
      sg_token(file, value_raw);
      
      if (value_raw[0] == '"') {
        value_raw[strlen(value_raw) - 1] = '\0';
        sg_output("%s", value_raw + 1);
      } else {
        sg_output("%s", value_raw);
      }
      
      x_is_stack = 0;
    } else {
      char *end;
      uint8_t value = strtol(buffer, &end, 0);
      
      if (end == buffer + strlen(buffer)) {
        if (!x_is_stack) {
          sg_output("mov x, 0xFFF7");
          x_is_stack = 1;
        }
        
        sg_output("mov a, %d", value);
        sg_output("mov [x], a");
      } else {
        // TODO: error
      }
    }
  }
}

void sg_parse(const char *path) {
  FILE *file = fopen(path, "r");
  
  if (!file) {
    fprintf(stderr, "error: cannot open file: '%s'\n", path);
    exit(1);
  }
  
  sg_parse_raw(file);
  fclose(file);
}

int main(void) {
  token_stack = malloc(TOKEN_STACK * sizeof(entry_t));
  printf("org 0x0000\n");
  
  printf("@start:\n");
  sg_parse("test.fth");
  
  sg_codegen(stdout);
  
  for (int i = 0; i < incasm_count; i++) {
    FILE *file = fopen(incasms[i].name, "r");
    
    if (!file) {
      // TODO: error
      continue;
    }
    
    while (!feof(file)) {
      char chr;
      
      fread(&chr, 1, 1, file);
      fwrite(&chr, 1, 1, stdout);
    }
    
    fclose(file);
  }
  
  return 0;
}
