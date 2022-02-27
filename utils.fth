let temp_1
let temp_2

let temp_3
let temp_4

let temp_5
let temp_6

let temp_7
let temp_8
let temp_9
let temp_10
let temp_11

macro times_2
  dup +
end

macro times_3
  dup dup + +
end

macro times_4
  times_2 times_2
end

macro times_6
  times_3 times_2
end

macro dup_2
  = temp_1 ; y
  dup
  = temp_2 ; x
  ? temp_1 ; y
  ? temp_2 ; x
  ? temp_1 ; y
end

macro putchar_dup
  = temp_1 ; y
  2 + dup 255 +
  = temp_2 ; x
  ? temp_1 ; y
  ? temp_2 ; x
  ? temp_1 ; y
  ? temp_2 ; x
  255 +
  ? temp_1 ; y
end

macro -
  255 ^ 1 + +
end

; (x index -- y)
macro bit
  shl 7 shr
end

; (x y -- low high)
macro pos_to_addr
  swap 2 shr swap 21 * = temp_3 dup_2 + = temp_4 carry ? temp_3 + 0xFC + ? temp_4 swap
end

; (color x y --)
macro plot
  = temp_5 dup 3 & dup + = temp_6 swap ? temp_6 shl = temp_6 ? temp_5 pos_to_addr dup_2 read ? temp_6 ^ = temp_6
  
  dup 0xFC ^ ~ if
    swap ? temp_6 swap ! 0xFC00
  then
  
  dup 0xFD ^ ~ if
    swap ? temp_6 swap ! 0xFD00
  then
  
  dup 0xFE ^ ~ if
    swap ? temp_6 swap ! 0xFE00
  then
  
  dup 0xFF ^ ~ if
    swap ? temp_6 swap ! 0xFF00
  then
  
  drop
end

; (char x y --)
macro putchar
  times_6 = temp_7 times_4 = temp_8 3 * 0x1E + putchar_dup
  ; low+2 high low+1 high low+0 high
  
  3 dup while
    = temp_11
    read = temp_9
    
    4 dup while
      255 + dup = temp_10 ? temp_9 swap shr 1 & times_3 ? temp_8 ? temp_10 + ? temp_7 plot
      ? temp_10 dup
    then drop
    
    ? temp_7 1 + = temp_7
    ? temp_9 4 shr = temp_9
    
    4 dup while
      255 + dup = temp_10 ? temp_9 swap shr 1 & times_3 ? temp_8 ? temp_10 + ? temp_7 plot
      ? temp_10 dup
    then drop
    
    ? temp_7 1 + = temp_7
    ? temp_11 255 + dup
  then drop
end

incasm "fnttable.asm"
