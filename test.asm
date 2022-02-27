org 0x0000
@start:
  mov x, 0xFFF7
  mov a, 48
  mov [x], a
  mov [x], a
@label_0:
  mov x, 0xFFF7
  mov a, [x]
  mov b, 0x00
  meq x, @label_1
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 2
  mov b, [x]
  mov [x], a
  mov [x], b
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2004
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 3
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFA
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2005
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFC
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov x, 0x2005
  mov [x], a
  mov x, 0x2004
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov [x], b
  mov a, 2
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFD
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov b, [x]
  mov [x], a
  mov [x], b
  mov a, 21
  mov b, [x]
  mov l, 0xF8
  mov [x], a
  mov l, 0xF9
  mov [x], b
  mov l, 0xFE
  mov a, [x]
  mov l, 0xF7
  mov [x], a
  mov l, 0xFF
  mov a, [x]
  mov l, 0xF7
  mov x, 0x2002
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov x, 0x2000
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov x, 0x2001
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2001
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2003
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov l, 0xF9
  mov [x], a
  mov l, 0xF8
  mov [x], b
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov x, 0x2002
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a + b)
  mov a, 252
  mov b, [x]
  mov [x], (a + b)
  mov x, 0x2003
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov x, 0x2000
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov x, 0x2001
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2001
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov b, a
  mov a, [x]
  mov h, b
  mov l, a
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov x, 0x2005
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 252
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_2
  jne x
  mov b, 0x01
@label_2:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_3
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFC00
  mov l, a
  mov [x], b
@label_3:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 253
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_4
  jne x
  mov b, 0x01
@label_4:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_5
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFD00
  mov l, a
  mov [x], b
@label_5:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 254
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_6
  jne x
  mov b, 0x01
@label_6:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_7
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFE00
  mov l, a
  mov [x], b
@label_7:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 255
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_8
  jne x
  mov b, 0x01
@label_8:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_9
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFF00
  mov l, a
  mov [x], b
@label_9:
  mov x, 0xFFF7
  mov a, [x]
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov x, @label_0
  jmp x
@label_1:
  mov x, 0xFFF7
  mov a, [x]
  mov a, 21
  mov [x], a
  mov [x], a
@label_10:
  mov x, 0xFFF7
  mov a, [x]
  mov b, 0x00
  meq x, @label_11
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov [x], a
  mov a, 31
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov a, 0
  mov [x], a
  mov [x], a
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov a, [x]
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2006
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov a, [x]
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2007
  mov [x], a
  mov x, 0xFFF7
  mov a, 3
  mov b, [x]
  mov l, 0xF8
  mov [x], a
  mov l, 0xF9
  mov [x], b
  mov l, 0xFE
  mov a, [x]
  mov l, 0xF7
  mov [x], a
  mov l, 0xFF
  mov a, [x]
  mov l, 0xF7
  mov [x], a
  mov a, 30
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2000
  mov [x], a
  mov x, 0xFFF7
  mov a, 2
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2001
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2001
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2001
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov a, 3
  mov [x], a
  mov [x], a
@label_12:
  mov x, 0xFFF7
  mov a, [x]
  mov b, 0x00
  meq x, @label_13
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov x, 0x200A
  mov [x], a
  mov x, 0xFFF7
  mov b, [x]
  mov a, [x]
  mov h, b
  mov l, a
  mov a, [x]
  mov x, 0xFFF7
  mov x, 0x2008
  mov [x], a
  mov x, 0xFFF7
  mov a, 4
  mov [x], a
  mov [x], a
@label_14:
  mov x, 0xFFF7
  mov a, [x]
  mov b, 0x00
  meq x, @label_15
  jeq x
  mov x, 0xFFF7
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2009
  mov [x], a
  mov x, 0x2008
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFD
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov a, 1
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFA
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov [x], a
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov b, [x]
  mov [x], (a + b)
  mov x, 0x2007
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2009
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a + b)
  mov x, 0x2006
  mov a, [x]
  mov x, 0xFFF7
  mov x, 0x2004
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 3
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFA
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2005
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFC
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov x, 0x2005
  mov [x], a
  mov x, 0x2004
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov [x], b
  mov a, 2
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFD
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov b, [x]
  mov [x], a
  mov [x], b
  mov a, 21
  mov b, [x]
  mov l, 0xF8
  mov [x], a
  mov l, 0xF9
  mov [x], b
  mov l, 0xFE
  mov a, [x]
  mov l, 0xF7
  mov [x], a
  mov l, 0xFF
  mov a, [x]
  mov l, 0xF7
  mov x, 0x2002
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov x, 0x2000
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov x, 0x2001
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2001
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2003
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov l, 0xF9
  mov [x], a
  mov l, 0xF8
  mov [x], b
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov x, 0x2002
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a + b)
  mov a, 252
  mov b, [x]
  mov [x], (a + b)
  mov x, 0x2003
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov x, 0x2000
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov x, 0x2001
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2001
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov b, a
  mov a, [x]
  mov h, b
  mov l, a
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov x, 0x2005
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 252
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_16
  jne x
  mov b, 0x01
@label_16:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_17
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFC00
  mov l, a
  mov [x], b
@label_17:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 253
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_18
  jne x
  mov b, 0x01
@label_18:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_19
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFD00
  mov l, a
  mov [x], b
@label_19:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 254
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_20
  jne x
  mov b, 0x01
@label_20:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_21
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFE00
  mov l, a
  mov [x], b
@label_21:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 255
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_22
  jne x
  mov b, 0x01
@label_22:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_23
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFF00
  mov l, a
  mov [x], b
@label_23:
  mov x, 0xFFF7
  mov a, [x]
  mov x, 0x2009
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov [x], a
  mov x, @label_14
  jmp x
@label_15:
  mov x, 0xFFF7
  mov a, [x]
  mov x, 0x2006
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov a, 1
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2006
  mov [x], a
  mov x, 0x2008
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov a, 4
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFD
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov x, 0x2008
  mov [x], a
  mov x, 0xFFF7
  mov a, 4
  mov [x], a
  mov [x], a
@label_24:
  mov x, 0xFFF7
  mov a, [x]
  mov b, 0x00
  meq x, @label_25
  jeq x
  mov x, 0xFFF7
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2009
  mov [x], a
  mov x, 0x2008
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFD
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov a, 1
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFA
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov [x], a
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov b, [x]
  mov [x], (a + b)
  mov x, 0x2007
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2009
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a + b)
  mov x, 0x2006
  mov a, [x]
  mov x, 0xFFF7
  mov x, 0x2004
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 3
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFA
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2005
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFC
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov x, 0x2005
  mov [x], a
  mov x, 0x2004
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov [x], b
  mov a, 2
  mov b, [x]
  mov l, 0xF8
  mov [x], b
  mov l, 0xF9
  mov [x], a
  mov l, 0xFD
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov b, [x]
  mov [x], a
  mov [x], b
  mov a, 21
  mov b, [x]
  mov l, 0xF8
  mov [x], a
  mov l, 0xF9
  mov [x], b
  mov l, 0xFE
  mov a, [x]
  mov l, 0xF7
  mov [x], a
  mov l, 0xFF
  mov a, [x]
  mov l, 0xF7
  mov x, 0x2002
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov x, 0x2000
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov x, 0x2001
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2001
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2003
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov l, 0xF9
  mov [x], a
  mov l, 0xF8
  mov [x], b
  mov a, [x] ; DONT_OPTIMIZE
  mov l, 0xF7
  mov [x], a
  mov x, 0x2002
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a + b)
  mov a, 252
  mov b, [x]
  mov [x], (a + b)
  mov x, 0x2003
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov x, 0x2000
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov x, 0x2001
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2001
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2000
  mov a, [x]
  mov x, 0xFFF7
  mov b, a
  mov a, [x]
  mov h, b
  mov l, a
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov x, 0x2005
  mov [x], a
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 252
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_26
  jne x
  mov b, 0x01
@label_26:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_27
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFC00
  mov l, a
  mov [x], b
@label_27:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 253
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_28
  jne x
  mov b, 0x01
@label_28:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_29
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFD00
  mov l, a
  mov [x], b
@label_29:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 254
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_30
  jne x
  mov b, 0x01
@label_30:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_31
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFE00
  mov l, a
  mov [x], b
@label_31:
  mov x, 0xFFF7
  mov a, [x]
  mov [x], a
  mov [x], a
  mov a, 255
  mov b, [x]
  mov [x], (a ^ b)
  mov a, [x]
  mov b, 0x00
  mne x, @label_32
  jne x
  mov b, 0x01
@label_32:
  mov x, 0xFFF7
  mov a, b
  mov b, 0x00
  meq x, @label_33
  jeq x
  mov x, 0xFFF7
  mov a, [x]
  mov b, [x]
  mov [x], a
  mov [x], b
  mov x, 0x2005
  mov a, [x]
  mov x, 0xFFF7
  mov b, [x]
  mov [x], a
  mov a, b
  mov b, [x]
  mov h, msb 0xFF00
  mov l, a
  mov [x], b
@label_33:
  mov x, 0xFFF7
  mov a, [x]
  mov x, 0x2009
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov [x], a
  mov x, @label_24
  jmp x
@label_25:
  mov x, 0xFFF7
  mov a, [x]
  mov x, 0x2006
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov a, 1
  mov b, [x]
  mov [x], (a + b)
  mov a, [x]
  mov x, 0x2006
  mov [x], a
  mov x, 0x200A
  mov a, [x]
  mov x, 0xFFF7
  mov [x], a
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov x, @label_12
  jmp x
@label_13:
  mov x, 0xFFF7
  mov a, [x]
  mov a, 255
  mov b, [x]
  mov [x], (a + b)
  mov [x], (a + b)
  mov x, @label_10
  jmp x
@label_11:
  mov x, 0xFFF7
  mov a, [x]
  hlt
align 0x1E00

fnt_table:
  ; char: ' '
  db 0
  db 0
  db 0
  ; char: '!'
  db 34
  db 2
  db 2
  ; char: '"'
  db 85
  db 0
  db 0
  ; char: '#'
  db 245
  db 245
  db 5
  ; char: '$'
  db 114
  db 99
  db 3
  ; char: '%'
  db 69
  db 18
  db 5
  ; char: '&'
  db 22
  db 82
  db 6
  ; char: '''
  db 34
  db 0
  db 0
  ; char: '('
  db 36
  db 34
  db 4
  ; char: ')'
  db 66
  db 68
  db 2
  ; char: '*'
  db 37
  db 5
  db 0
  ; char: '+'
  db 32
  db 39
  db 0
  ; char: ','
  db 0
  db 32
  db 1
  ; char: '-'
  db 0
  db 7
  db 0
  ; char: '.'
  db 0
  db 0
  db 2
  ; char: '/'
  db 36
  db 34
  db 1
  ; char: '0'
  db 82
  db 87
  db 2
  ; char: '1'
  db 100
  db 69
  db 4
  ; char: '2'
  db 67
  db 18
  db 7
  ; char: '3'
  db 67
  db 66
  db 3
  ; char: '4'
  db 85
  db 70
  db 4
  ; char: '5'
  db 23
  db 66
  db 3
  ; char: '6'
  db 22
  db 83
  db 2
  ; char: '7'
  db 71
  db 34
  db 2
  ; char: '8'
  db 82
  db 82
  db 2
  ; char: '9'
  db 82
  db 70
  db 3
  ; char: ':'
  db 32
  db 32
  db 0
  ; char: ';'
  db 64
  db 64
  db 2
  ; char: '<'
  db 36
  db 33
  db 4
  ; char: '='
  db 112
  db 112
  db 0
  ; char: '>'
  db 33
  db 36
  db 1
  ; char: '?'
  db 67
  db 2
  db 2
  ; char: '@'
  db 82
  db 23
  db 6
  ; char: 'A'
  db 82
  db 87
  db 5
  ; char: 'B'
  db 83
  db 83
  db 3
  ; char: 'C'
  db 22
  db 17
  db 6
  ; char: 'D'
  db 83
  db 85
  db 3
  ; char: 'E'
  db 23
  db 19
  db 7
  ; char: 'F'
  db 23
  db 19
  db 1
  ; char: 'G'
  db 22
  db 85
  db 2
  ; char: 'H'
  db 85
  db 87
  db 5
  ; char: 'I'
  db 39
  db 34
  db 7
  ; char: 'J'
  db 71
  db 84
  db 2
  ; char: 'K'
  db 85
  db 83
  db 5
  ; char: 'L'
  db 17
  db 17
  db 7
  ; char: 'M'
  db 117
  db 85
  db 5
  ; char: 'N'
  db 117
  db 119
  db 5
  ; char: 'O'
  db 82
  db 85
  db 2
  ; char: 'P'
  db 83
  db 19
  db 1
  ; char: 'Q'
  db 82
  db 85
  db 66
  ; char: 'R'
  db 83
  db 83
  db 5
  ; char: 'S'
  db 22
  db 66
  db 3
  ; char: 'T'
  db 39
  db 34
  db 2
  ; char: 'U'
  db 85
  db 85
  db 6
  ; char: 'V'
  db 85
  db 117
  db 2
  ; char: 'W'
  db 85
  db 117
  db 5
  ; char: 'X'
  db 85
  db 82
  db 5
  ; char: 'Y'
  db 85
  db 34
  db 2
  ; char: 'Z'
  db 71
  db 18
  db 7
  ; char: '['
  db 23
  db 17
  db 7
  ; char: '\'
  db 33
  db 34
  db 4
  ; char: ']'
  db 71
  db 68
  db 7
  ; char: '^'
  db 82
  db 0
  db 0
  ; char: '_'
  db 0
  db 0
  db 7
  ; char: '`'
  db 66
  db 0
  db 0
  ; char: 'a'
  db 0
  db 82
  db 6
  ; char: 'b'
  db 17
  db 83
  db 3
  ; char: 'c'
  db 0
  db 22
  db 6
  ; char: 'd'
  db 68
  db 86
  db 6
  ; char: 'e'
  db 32
  db 53
  db 6
  ; char: 'f'
  db 22
  db 19
  db 1
  ; char: 'g'
  db 0
  db 82
  db 54
  ; char: 'h'
  db 17
  db 83
  db 5
  ; char: 'i'
  db 2
  db 34
  db 2
  ; char: 'j'
  db 4
  db 84
  db 2
  ; char: 'k'
  db 17
  db 53
  db 5
  ; char: 'l'
  db 34
  db 34
  db 4
  ; char: 'm'
  db 0
  db 119
  db 5
  ; char: 'n'
  db 0
  db 83
  db 5
  ; char: 'o'
  db 0
  db 82
  db 2
  ; char: 'p'
  db 0
  db 83
  db 19
  ; char: 'q'
  db 0
  db 86
  db 70
  ; char: 'r'
  db 0
  db 53
  db 1
  ; char: 's'
  db 0
  db 38
  db 3
  ; char: 't'
  db 32
  db 39
  db 6
  ; char: 'u'
  db 0
  db 85
  db 6
  ; char: 'v'
  db 0
  db 117
  db 2
  ; char: 'w'
  db 0
  db 117
  db 7
  ; char: 'x'
  db 0
  db 37
  db 5
  ; char: 'y'
  db 0
  db 85
  db 54
  ; char: 'z'
  db 0
  db 39
  db 7
  ; char: '{'
  db 38
  db 33
  db 6
  ; char: '|'
  db 34
  db 34
  db 2
  ; char: '}'
  db 35
  db 36
  db 3
  ; char: '~'
  db 37
  db 0
  db 0
  ; char: ''
  db 119
  db 119
  db 7

