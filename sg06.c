#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <sg06.h>

#define FREQ  1048576
#define SCALE 12

uint8_t key_queue[256] = {0};

uint8_t key_write_head = 0;
uint8_t key_read_head = 0;

entry_t *labels = NULL;
int label_count = 0;

entry_t *refers = NULL;
int refer_count = 0;

uint16_t rel_addr = 0x0000;

void sg_init(sg06_t *state, const char *path) {
  state->a = 0;
  state->b = 0;
  
  state->x = 0;
  state->y = 0;
  
  state->data = calloc(65536, 1);
  state->halt = 0;
  
  if (path) {
    FILE *file = fopen(path, "rb");
    if (!file) return;
    
    fread(state->data, 1, 8192, file);
    fclose(file);
  }
}

void sg_free(sg06_t *state) {
  free(state->data);
}

void sg_tick(sg06_t *state) {
  uint8_t oper = sg_read(state, state->y++);
  uint8_t cond = (oper >> 5) & 3;
  uint8_t data = 0;
  
  uint8_t sum = state->a + state->b;
  uint8_t xor = state->a ^ state->b;
  
  oper &= 31;
  
  if (oper == 0x00 || oper == 0x03 || oper == 0x06 || oper == 0x0B) {
    data = sg_read(state, state->y++);
  }
  
  if (cond == 1) {
    if (state->a != state->b) return;
  } else if (cond == 2) {
    if (state->a == state->b) return;
  }
  
  switch (oper) {
    case 0x00:
      state->a = data;
      break;
      
    case 0x01:
      state->a = state->b;
      break;
      
    case 0x02:
      state->a = sg_read(state, state->x);
      break;
      
    case 0x03:
      state->b = data;
      break;
      
    case 0x04:
      state->b = state->a;
      break;
      
    case 0x05:
      state->b = sg_read(state, state->x);
      break;
      
    case 0x06:
      state->x = (state->x & 0xFF00) | (uint16_t)(data);
      break;
      
    case 0x07:
      state->x = (state->x & 0xFF00) | (uint16_t)(state->a);
      break;
      
    case 0x08:
      state->x = (state->x & 0xFF00) | (uint16_t)(state->b);
      break;
      
    case 0x09:
      state->x = (state->x & 0xFF00) | (uint16_t)(sum);
      break;
      
    case 0x0A:
      state->x = (state->x & 0xFF00) | (uint16_t)(xor);
      break;
      
    case 0x0B:
      state->x = (state->x & 0x00FF) | ((uint16_t)(data) << 8);
      break;
      
    case 0x0C:
      state->x = (state->x & 0x00FF) | ((uint16_t)(state->a) << 8);
      break;
      
    case 0x0D:
      state->x = (state->x & 0x00FF) | ((uint16_t)(state->b) << 8);
      break;
      
    case 0x0E:
      state->x = (state->x & 0x00FF) | ((uint16_t)(sum) << 8);
      break;
      
    case 0x0F:
      state->x = (state->x & 0x00FF) | ((uint16_t)(xor) << 8);
      break;
      
    case 0x10:
      sg_write(state, state->x, state->a);
      break;
      
    case 0x11:
      sg_write(state, state->x, state->b);
      break;
      
    case 0x12:
      sg_write(state, state->x, sum);
      break;
      
    case 0x13:
      sg_write(state, state->x, xor);
      break;
      
    case 0x14:
      state->y = state->x;
      break;
      
    case 0x15:
      state->halt = 1;
      break;
    
    case 0x16:
      break;
  }
}

uint8_t sg_read(sg06_t *state, uint16_t addr) {
  if (addr >= 0xFFF8) return 0x00;
  
  if (addr == 0xFFF0) {
    if (key_read_head == key_write_head) return 0x00;
    return key_queue[key_read_head++];
  }
  
  return state->data[addr];
}

static int is_space(char c) {
  return (isspace(c) || c == ',');
}

void sg_write(sg06_t *state, uint16_t addr, uint8_t value) {
  if (addr < 0x2000 || addr == 0xFFF0 || addr >= 0xFFF8) return;
  state->data[addr] = value;
}

void sg_byte(FILE *output, uint8_t byte) {
  fwrite(&byte, 1, 1, output);
  rel_addr++;
}

int sg_token(FILE *file, char *buffer) {
  // TODO: parentheses
  
  int in_string = 0;
  int in_paren = 0;
  
  char c = ' ';
  
  while (c != EOF && is_space(c)) {
    c = fgetc(file);
    
    if (c == ';') {
      while (c != EOF && c != '\n') c = fgetc(file);
    }
  }
  
  if (c == EOF) return 0;
  
  while (c != EOF && (!is_space(c) || in_string || in_paren)) {
    if (c == '"') {
      in_string = !in_string;
    } else if (!in_string) {
      if (c == '(') {
        in_paren = 1;
      } else if (c == ')') {
        in_paren = 0;
      } else if (c == ';') {
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
  return 1;
}

static void sg_error(const char *path, const char *msg, const char *instr, const char *arg_1, const char *arg_2, int index) {
  printf("error in '%s': %s\n", path, msg);
  printf("  %s %s, %s\n", instr, arg_1 ? arg_1 : "", arg_2 ? arg_2 : "");
  
  switch (index) {
    case 0:
      printf("  ");
      for (int i = 0; i < strlen(instr); i++) putchar('^');
      
      break;
    
    case 1:
      printf("  ");
      for (int i = 0; i < strlen(instr); i++) putchar(' ');
      
      printf(" ");
      for (int i = 0; i < strlen(arg_1); i++) putchar('^');
      
      break;
    
    case 2:
      printf("  ");
      for (int i = 0; i < strlen(instr); i++) putchar(' ');
      
      printf(" ");
      for (int i = 0; i < strlen(arg_1); i++) putchar(' ');
      
      printf("  ");
      for (int i = 0; i < strlen(arg_2); i++) putchar('^');
      
      break;
  }
  
  putchar('\n');
  exit(1);
}

void sg_parse(const char *path, FILE *output) {
  FILE *file = fopen(path, "r");
  
  if (!file) {
    printf("error: cannot open file: '%s'\n", path);
    exit(1);
  }
  
  char buffer[64];
  
  while (sg_token(file, buffer)) {
    if (buffer[strlen(buffer) - 1] == ':') {
      labels = realloc(labels, (label_count + 1) * sizeof(entry_t));
      
      strcpy(labels[label_count].name, buffer);
      labels[label_count].name[strlen(buffer) - 1] = '\0';
      
      labels[label_count++].offset = rel_addr;
    } else if (!strcmp(buffer, "org")) {
      char arg_1[64];
      sg_token(file, arg_1);
      
      char *end;
      
      uint16_t value = strtol(arg_1, &end, 0);
      
      if (end == arg_1 + strlen(arg_1)) {
        rel_addr = value;
      } else {
        sg_error(path, "invalid address", buffer, arg_1, NULL, 1);
      }
    } else if (!strcmp(buffer, "inc")) {
      char arg_1[256];
      sg_token(file, arg_1);
      
      if (*arg_1 == '"') {
        arg_1[strlen(arg_1) - 1] = '\0';
        sg_parse(arg_1 + 1, output);
      } else {
        sg_parse(arg_1, output);
      }
    } else if (!strcmp(buffer, "str")) {
      char arg_1[256];
      sg_token(file, arg_1);
      
      if (*arg_1 == '"') {
        for (int i = 1; i < strlen(arg_1) - 2; i++) {
          sg_byte(output, arg_1[i]);
        }
      } else {
        sg_error(path, "invalid string", buffer, arg_1, NULL, 1);
      }
    } else if (!strcmp(buffer, "db")) {
      char arg_1[64];
      sg_token(file, arg_1);
      
      char *end;
      
      uint8_t value = strtol(arg_1, &end, 0);
      
      if (end == arg_1 + strlen(arg_1)) {
        sg_byte(output, value);
      } else {
        sg_error(path, "invalid constant", buffer, arg_1, NULL, 1);
      }
    } else if (!strcmp(buffer, "dw")) {
      char arg_1[64];
      sg_token(file, arg_1);
      
      char *end;
      
      uint16_t value = strtol(arg_1, &end, 0);
      
      if (end == arg_1 + strlen(arg_1)) {
        sg_byte(output, value);
      } else {
        refers = realloc(refers, (refer_count + 1) * sizeof(entry_t));
          
        strcpy(refers[refer_count].name, arg_1);
        refers[refer_count].offset = ftell(output);
        refers[refer_count++].part = 0;
        
        sg_byte(output, 0x00);
        refers = realloc(refers, (refer_count + 1) * sizeof(entry_t));
        
        strcpy(refers[refer_count].name, arg_1);
        refers[refer_count].offset = ftell(output);
        refers[refer_count++].part = 1;
        
        sg_byte(output, 0x00);
      }
    } else if (!strcmp(buffer, "mov") || !strcmp(buffer, "meq") || !strcmp(buffer, "mne")) {
      uint8_t mask = 0x00;
      
      if (buffer[1] == 'e') mask |= 0x20;
      if (buffer[1] == 'n') mask |= 0x40;
      
      char arg_1[64];
      sg_token(file, arg_1);
      
      char arg_2[64];
      sg_token(file, arg_2);
      
      if (!strcmp(arg_1, "a")) {
        if (!strcmp(arg_2, "b")) {
          sg_byte(output, 0x01 | mask);
        } else if (!strcmp(arg_2, "[x]")) {
          sg_byte(output, 0x02 | mask);
        } else {
          char *end;
          
          uint8_t value = strtol(arg_2, &end, 0);
          
          if (end == arg_2 + strlen(arg_2)) {
            sg_byte(output, 0x00 | mask);
            sg_byte(output, value);
          } else {
            sg_error(path, "invalid register or constant", buffer, arg_1, arg_2, 2);
            // TODO: msb and lsb of labels
          }
        }
      } else if (!strcmp(arg_1, "b")) {
        if (!strcmp(arg_2, "a")) {
          sg_byte(output, 0x04 | mask);
        } else if (!strcmp(arg_2, "[x]")) {
          sg_byte(output, 0x05 | mask);
        } else {
          char *end;
          
          uint8_t value = strtol(arg_2, &end, 0);
          
          if (end == arg_2 + strlen(arg_2)) {
            sg_byte(output, 0x03 | mask);
            sg_byte(output, value);
          } else {
            sg_error(path, "invalid register or constant", buffer, arg_1, arg_2, 2);
            // TODO: msb and lsb of labels
          }
        }
      } else if (!strcmp(arg_1, "l")) {
        if (!strcmp(arg_2, "a")) {
          sg_byte(output, 0x07 | mask);
        } else if (!strcmp(arg_2, "b")) {
          sg_byte(output, 0x08 | mask);
        } else if (!strcmp(arg_2, "(a + b)")) {
          sg_byte(output, 0x09 | mask);
        } else if (!strcmp(arg_2, "(a ^ b)")) {
          sg_byte(output, 0x0A | mask);
        } else {
          char *end;
          
          uint8_t value = strtol(arg_2, &end, 0);
          
          if (end == arg_2 + strlen(arg_2)) {
            sg_byte(output, 0x06 | mask);
            sg_byte(output, value);
          } else {
            sg_error(path, "invalid register or constant", buffer, arg_1, arg_2, 2);
            // TODO: msb and lsb of labels
          }
        }
      } else if (!strcmp(arg_1, "h")) {
        if (!strcmp(arg_2, "a")) {
          sg_byte(output, 0x0C | mask);
        } else if (!strcmp(arg_2, "b")) {
          sg_byte(output, 0x0D | mask);
        } else if (!strcmp(arg_2, "(a + b)")) {
          sg_byte(output, 0x0E | mask);
        } else if (!strcmp(arg_2, "(a ^ b)")) {
          sg_byte(output, 0x0F | mask);
        } else {
          char *end;
          
          uint8_t value = strtol(arg_2, &end, 0);
          
          if (end == arg_2 + strlen(arg_2)) {
            sg_byte(output, 0x0B | mask);
            sg_byte(output, value);
          } else {
            sg_error(path, "invalid register or constant", buffer, arg_1, arg_2, 2);
            // TODO: msb and lsb of labels
          }
        }
      } else if (!strcmp(arg_1, "x")) {
        char *end;
        
        uint16_t value = strtol(arg_2, &end, 0);
        sg_byte(output, 0x06 | mask);
        
        if (end == arg_2 + strlen(arg_2)) {
          sg_byte(output, (value >> 0) & 0xFF);
          sg_byte(output, 0x0B | mask);
          sg_byte(output, (value >> 8) & 0xFF);
        } else {
          refers = realloc(refers, (refer_count + 1) * sizeof(entry_t));
          
          strcpy(refers[refer_count].name, arg_2);
          refers[refer_count].offset = ftell(output);
          refers[refer_count++].part = 0;
          
          sg_byte(output, 0x00);
          sg_byte(output, 0x0B | mask);
          
          refers = realloc(refers, (refer_count + 1) * sizeof(entry_t));
          
          strcpy(refers[refer_count].name, arg_2);
          refers[refer_count].offset = ftell(output);
          refers[refer_count++].part = 1;
          
          sg_byte(output, 0x00);
        }
      } else if (!strcmp(arg_1, "d")) {
        char *end;
        
        uint16_t value = strtol(arg_2, &end, 0);
        sg_byte(output, 0x00 | mask);
        
        if (end == arg_2 + strlen(arg_2)) {
          sg_byte(output, (value >> 0) & 0xFF);
          sg_byte(output, 0x03 | mask);
          sg_byte(output, (value >> 8) & 0xFF);
        } else {
          refers = realloc(refers, (refer_count + 1) * sizeof(entry_t));
          
          strcpy(refers[refer_count].name, arg_2);
          refers[refer_count].offset = ftell(output);
          refers[refer_count++].part = 0;
          
          sg_byte(output, 0x00);
          sg_byte(output, 0x03 | mask);
          
          refers = realloc(refers, (refer_count + 1) * sizeof(entry_t));
          
          strcpy(refers[refer_count].name, arg_2);
          refers[refer_count].offset = ftell(output);
          refers[refer_count++].part = 1;
          
          sg_byte(output, 0x00);
        }
      } else if (!strcmp(arg_1, "[x]")) {
        if (!strcmp(arg_2, "a")) {
          sg_byte(output, 0x10 | mask);
        } else if (!strcmp(arg_2, "b")) {
          sg_byte(output, 0x11 | mask);
        } else if (!strcmp(arg_2, "(a + b)")) {
          sg_byte(output, 0x12 | mask);
        } else if (!strcmp(arg_2, "(a ^ b)")) {
          sg_byte(output, 0x13 | mask);
        } else {
          sg_error(path, "invalid register or basic expression", buffer, arg_1, arg_2, 2);
        }
      } else {
        sg_error(path, "invalid destination", buffer, arg_1, arg_2, 1);
      }
    } else if (!strcmp(buffer, "jmp") || !strcmp(buffer, "jeq") || !strcmp(buffer, "jne")) {
      uint8_t mask = 0x00;
      
      if (buffer[1] == 'e') mask |= 0x20;
      if (buffer[1] == 'n') mask |= 0x40;
      
      char arg_1[64];
      sg_token(file, arg_1);
      
      if (!strcmp(arg_1, "x")) {
        sg_byte(output, 0x14 | mask);
      } else {
        sg_error(path, "invalid register", buffer, arg_1, NULL, 1);
      }
    } else if (!strcmp(buffer, "hlt") || !strcmp(buffer, "heq") || !strcmp(buffer, "hne")) {
      uint8_t mask = 0x00;
      
      if (buffer[1] == 'e') mask |= 0x20;
      if (buffer[1] == 'n') mask |= 0x40;
      
      sg_byte(output, 0x15 | mask);
    } else if (!strcmp(buffer, "nop") || !strcmp(buffer, "neq") || !strcmp(buffer, "nne")) {
      uint8_t mask = 0x00;
      
      if (buffer[1] == 'e') mask |= 0x20;
      if (buffer[1] == 'n') mask |= 0x40;
      
      sg_byte(output, 0x16 | mask);
    } else {
      sg_error(path, "invalid instruction or compiler signal", buffer, NULL, NULL, 0);
    }
  }
  
  fclose(file);
}

void sg_solve(FILE *output) {
  for (int i = 0; i < refer_count; i++) {
    int solved = 0;
    
    for (int j = 0; j < label_count; j++) {
      if (!strcmp(refers[i].name, labels[j].name)) {
        fseek(output, refers[i].offset, SEEK_SET);
        sg_byte(output, (labels[j].offset >> (refers[i].part * 8)) & 0xFF);
        
        solved = 1;
        break;
      }
    }
    
    if (solved) continue;
    
    printf("error: undefined label: '%s'\n", refers[i].name);
    exit(1);
  }
  
  printf("%d references solved\n", refer_count);
}

static int usage(const char *arg0, int value) {
  printf("usage: %s -c FILE.asm [...]\n", arg0);
  printf("       %s -r BOOT.bin [...]\n", arg0);
  printf("       %s -h\n\n", arg0);
  
  printf("general options:\n");
  printf("  -c / --compile FILE.asm -> compiles a sg06 assembly file\n");
  printf("  -r / --run BOOT.bin     -> starts the sg06 virtual machine with a specified boot rom\n");
  printf("  -h / --help             -> shows this help information\n\n");
  
  printf("compile options:\n");
  printf("  -o / --output FILE.bin -> sets the output filename(by default the same filename as the input file but with the extension changed to '.bin')\n");
  printf("  -s / --start ADDRESS   -> sets the origin address(by default 0x0000)\n\n");
  
  printf("run options:\n");
  printf("  -d / --drive DRIVE.img -> loads a hard drive image, read-only by default\n");
  printf("  -w / --writable        -> makes the loaded drive image writable(if any)\n");
  printf("  -v / --verbose         -> prints some CPU information every single cycle(for debugging)\n");
  printf("  -s / --start ADDRESS   -> sets the boot address(by default 0x0000, should not change)\n\n");
  
  printf("made by segfaultdev, 2022\n");
  return value;
}

int main(int argc, const char **argv) {
  if (argc < 2) {
    printf("error: missing arguments\n\n");
    return usage(argv[0], 1);
  }
  
  if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
    usage(argv[0], 0);
  } else if (!strcmp(argv[1], "-c") || !strcmp(argv[1], "--compile")) {
    if (argc < 3) {
      printf("error: missing input file\n\n");
      return usage(argv[0], 1);
    }
    
    char output[256] = {0};
    
    const char *ptr = strrchr(argv[2], '.');
    if (!ptr) ptr = argv[2] + strlen(argv[2]);
    
    memcpy(output, argv[2], ptr - argv[2]);
    strcat(output, ".bin");
    
    for (int i = 3; i < argc; i++) {
      if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
        strcpy(output, argv[++i]);
      } else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--start")) {
        rel_addr = strtol(argv[++i], NULL, 0);
      } else {
        printf("error: invalid argument: '%s'\n\n", argv[i]);
        return usage(argv[0], 1);
      }
    }
    
    FILE *file = fopen(output, "wb");
    
    if (!file) {
      printf("error: cannot create or open file: '%s'\n\n", output);
      return usage(argv[0], 1);
    }
    
    sg_parse(argv[2], file);
    sg_solve(file);
    
    fclose(file);
  } else if (!strcmp(argv[1], "-r") || !strcmp(argv[1], "--run")) {
    if (argc < 3) {
      printf("error: missing boot rom\n\n");
      return usage(argv[0], 1);
    }
    
    uint16_t start = 0x0000;
    
    for (int i = 3; i < argc; i++) {
      if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--start")) {
        start = strtol(argv[++i], NULL, 0);
      } else {
        printf("error: invalid argument: '%s'\n\n", argv[i]);
        return usage(argv[0], 1);
      }
    }
    
    sg06_t state;
    sg_init(&state, argv[2]);
    
    state.y = start;
    
    InitWindow(84 * SCALE, 48 * SCALE, "sg06");
    
    while (!WindowShouldClose() && !state.halt) {
      BeginDrawing();
      ClearBackground(BLACK);
      
      uint16_t video_addr = 0xFC00;
      
      for (int i = 0; i < 48; i++) {
        uint8_t data;
        
        for (int j = 0; j < 84; j++) {
          if (!(j % 4)) {
            data = sg_read(&state, video_addr++);
          }
          
          switch (data % 4) {
            case 1:
              DrawRectangle(j * SCALE, i * SCALE, SCALE, SCALE, (Color){0, 127, 255, 255});
              break;
              
            case 2:
              DrawRectangle(j * SCALE, i * SCALE, SCALE, SCALE, (Color){255, 127, 0, 255});
              break;
              
            case 3:
              DrawRectangle(j * SCALE, i * SCALE, SCALE, SCALE, (Color){255, 255, 255, 255});
              break;
          }
          
          data >>= 2;
        }
      }
      
      EndDrawing();
      
      int count = (int)(FREQ * GetFrameTime());
      for (int i = 0; i < count; i++) sg_tick(&state);
    }
    
    sg_free(&state);
  } else {
    printf("error: invalid argument: '%s'\n\n", argv[1]);
    return usage(argv[0], 1);
  }
  
  return 0;
}
