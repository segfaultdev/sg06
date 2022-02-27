include utils.fth

48 dup while
  dup 2 swap 255 + dup plot
  255 + dup
then drop

21 dup while
  dup dup 31 + swap 255 + 0 putchar
  255 + dup
then drop

halt
