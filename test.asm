org 0x0000

start:
  ; CLEAR STACK POINTER
  mov x, 0x20FC
  mov a, 0x00
  mov [x], a
  ; TOKEN: '3'
  mov x, 0x20FC
  mov a, [x]
  mov l, a
  mov b, 3
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: '2'
  mov x, 0x20FC
  mov a, [x]
  mov l, a
  mov b, 2
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: '+'
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov [x], (a + b)
  mov l, 0xFC
  mov a, [x]
  mov l, a
  mov b, [x]
  mov l, 0xFD
  mov [x], b
  mov l, 0xFC
  mov b, 0xFF
  mov [x], (a + b)
  mov l, 0xFC
  mov a, [x]
  mov l, a
  mov b, [x]
  mov l, 0xFD
  mov a, [x]
  mov [x], (a + b)
  mov b, [x]
  mov l, 0xFC
  mov a, [x]
  mov l, a
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: '1'
  mov x, 0x20FC
  mov a, [x]
  mov l, a
  mov b, 1
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: '+'
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov [x], (a + b)
  mov l, 0xFC
  mov a, [x]
  mov l, a
  mov b, [x]
  mov l, 0xFD
  mov [x], b
  mov l, 0xFC
  mov b, 0xFF
  mov [x], (a + b)
  mov l, 0xFC
  mov a, [x]
  mov l, a
  mov b, [x]
  mov l, 0xFD
  mov a, [x]
  mov [x], (a + b)
  mov b, [x]
  mov x, 0xFC00
  mov [x], b
end:
  mov x, end
  jmp x
