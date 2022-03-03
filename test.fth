include utils.fth

label start
  ptr line_1 0 0 call puts
  ptr line_2 0 1 call puts
  ptr line_3 0 2 call puts
  ptr line_4 0 3 call puts
  
  2 30 10 4 30 call rect
  1 30 10 17 35 call rect
  
  halt
then

str line_1 "hello guys! i'm using"
str line_2 "function calls to run"
str line_3 "this, instead of huge"
str line_4 "and shitty macros  :D"
