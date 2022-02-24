org 0x0000

@start:
  ; CLEAR STACK POINTER
  mov x, 0x20FC
  mov a, 0x00
  mov [x], a
  ; TOKEN: 'macro'
  ; TOKEN: '252'
  mov x, 0x20FC
  mov a, [x]
  mov l, a
  mov b, 252
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: 'dup'
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov l, (a + b)
  mov b, [x]
  mov l, a
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: 'while'
@label_0:
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov l, (a + b)
  mov b, [x]
  mov l, 0xFD
  mov [x], b
  mov l, 0xFC
  mov b, 0xFF
  mov [x], (a + b)
  mov l, 0xFD
  mov b, [x]
  mov a, 0x00
  meq x, @label_1
  jeq x
  ; TOKEN: 'dup'
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov l, (a + b)
  mov b, [x]
  mov l, a
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: '255'
  mov x, 0x20FC
  mov a, [x]
  mov l, a
  mov b, 255
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
  ; TOKEN: 'dup'
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov l, (a + b)
  mov b, [x]
  mov l, a
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: '!'
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov l, (a + b)
  mov b, [x]
  mov l, 0xFD
  mov [x], b
  mov l, 0xFC
  mov b, 0xFF
  mov [x], (a + b)
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov l, (a + b)
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov l, (a + b)
  mov b, [x]
  mov l, 0xFB
  mov [x], b
  mov l, 0xFC
  mov b, 0xFF
  mov [x], (a + b)
  mov l, 0xFB
  mov b, [x]
  mov l, 0xFD
  mov a, [x]
  mov h, 252
  mov l, a
  mov [x], b
  ; TOKEN: '255'
  mov x, 0x20FC
  mov a, [x]
  mov l, a
  mov b, 255
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
  ; TOKEN: 'dup'
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov l, (a + b)
  mov b, [x]
  mov l, a
  mov [x], b
  mov l, 0xFC
  mov b, 0x01
  mov [x], (a + b)
  ; TOKEN: 'then'
  mov x, @label_0
  jmp x
@label_1:
  ; TOKEN: 'drop'
  mov x, 0x20FC
  mov a, [x]
  mov b, 0xFF
  mov [x], (a + b)
  ; TOKEN: 'halt'
  hlt
