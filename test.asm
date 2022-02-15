org 0x0000

start:
  mov a, 0x00
  mov b, 0x01
loop:
  mov x, 0xFC00
  mov [x], a
  mov x, 0x2000
  mov [x], (a + b)
  mov a, [x]
  mov x, loop
  jmp x
