# registers:

```
(lsb)               (msb)
| A | B | L | H |       |
|   D   |   X   |   Y   |

- a, b: 8-bit, general purpose
- l, h: 8-bit, low and high parts of x
- x, y: 16-bit, data and instruction pointers
```

# opcode format:

```
0cciiiii

i: instruction
c: condition
```

# instructions:

```
00 00000: mov a, imm
01 00001: mov a, b
02 00010: mov a, [x]
03 00011: mov b, imm
04 00100: mov b, a
05 00101: mov b, [x]
06 00110: mov l, imm
07 00111: mov l, a
08 01000: mov l, b
09 01001: mov l, (a + b)
0A 01010: mov l, (a ^ b)
0B 01011: mov h, imm
0C 01100: mov h, a
0D 01101: mov h, b
0E 01110: mov h, (a + b)
0F 01111: mov h, (a ^ b)
10 10000: mov [x], a
11 10001: mov [x], b
12 10010: mov [x], (a + b)
13 10011: mov [x], (a ^ b)
14 10100: jmp x
15 10101: hlt
16 10110: nop
```

# conditions:

```
00: always true: mov h, 2 / hlt / nop / jmp x
01: if a == b:   meq h, 2 / heq / neq / jeq x
10: if a != b:   mne h, 2 / hne / nne / jne x
```

# video:

- 84x48, 4 colors, 2 bits per pixel -> least significant bits are leftmost pixel

# drive:

control register(read): 000000br
- b: buffer flag, 1 if data ready to be read or to be written
- r: ready flag, 1 if ready to take commands

control register(write):
- 

# memory map:

0x0000 - 0x1FFF -> ROM(8k)
0x2000 - 0xFBFF -> RAM(55k)
0xFC00 - 0xFFEF -> VRAM(1008 bytes)
0xFFF0 - 0xFFF0 -> keyboard buffer register(r)
0xFFF1 - 0xFFF1 -> drive control register(r/w)
0xFFF2 - 0xFFF5 -> drive LBA address register(r/w)
0xFFF6 - 0xFFF6 -> drive data register(r/w)
0xFFF7 - 0xFFF7 -> external hardware stack register
0xFFF8 - 0xFFF8 -> external ALU first operand / external ALU carry from addition
0xFFF9 - 0xFFF9 -> external ALU second operand / external ALU carry from subtraction
0xFFFA - 0xFFFA -> external ALU & result
0xFFFB - 0xFFFB -> external ALU | result
0xFFFC - 0xFFFC -> external ALU shl result
0xFFFD - 0xFFFD -> external ALU shr result
0xFFFE - 0xFFFF -> external ALU multiplication result(first byte represents lsb)
