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

let temp_12
let temp_13
let temp_14

let temp_15
let temp_16
let temp_17
let temp_18
let temp_19
let temp_20

ptr start jump

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
  = temp_2 = temp_1
  ? temp_1 2 + ? temp_2 ? temp_1 2 carry +
  ? temp_1 1 + ? temp_2 ? temp_1 2 carry +
  ? temp_1 ? temp_2
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
func plot
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
then

; (char x y --)
macro putchar
  times_6 = temp_7 times_4 = temp_8 3 * 0x1E + putchar_dup
  ; low+2 high low+1 high low+0 high
  
  3 dup while
    = temp_11
    read = temp_9
    
    4 dup while
      255 + dup = temp_10 ? temp_9 swap shr 1 & times_3 ? temp_8 ? temp_10 + ? temp_7 call plot
      ? temp_10 dup
    then drop
    
    ? temp_7 1 + = temp_7
    ? temp_9 4 shr = temp_9
    
    4 dup while
      255 + dup = temp_10 ? temp_9 swap shr 1 & times_3 ? temp_8 ? temp_10 + ? temp_7 call plot
      ? temp_10 dup
    then drop
    
    ? temp_7 1 + = temp_7
    ? temp_11 255 + dup
  then drop
end

; (low high x y --)
func puts
  = temp_12 = temp_13
  
  dup_2 read dup while
    224 + ? temp_13 ? temp_12 putchar
    ? temp_13 1 + = temp_13
    swap 1 dup_2 + = temp_14 carry + ? temp_14 swap
    dup_2 read dup
  then
  
  drop drop drop
then

; (color w h x y --)
func rect
  = temp_15 = temp_16 = temp_17 = temp_18
  
  ? temp_17 dup while
    255 + = temp_19
    
    ? temp_18 dup while
      255 + = temp_20
      
      dup ? temp_16 ? temp_20 + ? temp_15 ? temp_19 + call plot
      
      ? temp_20 dup
    then drop
    
    ? temp_19 dup
  then drop drop
then

incasm "fnttable.asm"
