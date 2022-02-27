include utils.fth

; 48 dup while
;   dup 2 swap 255 + dup plot
;   255 + dup
; then drop

let pos_y

8 dup while
  dup = pos_y
  
  21 dup while
    dup dup ? pos_y 255 + 21 * drop + swap 255 + ? pos_y 255 + putchar
    255 + dup
  then drop
  
  255 + dup
then drop

halt
