macro dup_2
  = 0x20FE ; y
  dup
  = 0x20FF ; x
  ? 0x20FE ; y
  ? 0x20FF ; x
  ? 0x20FE ; y
end

macro -
  255 ^ 1 + +
end

macro &
  0 = 0x20F0 ; result
  = 0x20F1 ; x
  = 0x20F2 ; y  
  
  8 dup while
    = 0x20F3
    
    ? 0x20F1 ? 0x20F3 255 + bit if
      ? 0x20F2 ? 0x20F3 255 + bit if
        ? 0x20F0
        128 ? 0x20F3 255 + shr ^
        = 0x20F0
      then
    then
    
    ? 0x20F3
    255 + dup
  then drop
  
  ? 0x20F0
end

macro |
  ; TODO
end

macro shl_1
  dup +
end

macro shr_1
  @ shr_table
end

; (x count -- y)
macro shl
  dup while
    swap shl_1 swap
    255 + dup
  then drop
end

; (x count -- y)
macro shr
  dup while
    swap shr_1 swap
    255 + dup
  then drop
end

; (x index -- y)
macro bit
  shl 7 shr
end

; (color x y --)
macro plot
  
end

incasm "fnttable.asm"
incasm "shrtable.asm"
