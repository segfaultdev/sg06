; global variables
let term_x 0
let term_y 0

macro putc
  ; actually draw the character
  ...
  
  ; increase x cursor
  term_x @ 1 + dup
  
  >= 21 if
    ; wrap around
    drop 0
    
    ; increase y cursor
    term_y @ 1 + dup
    
    >= 8 if
      ; wrap around
      drop 0
    end
    
    term_y !
  end
  
  term_x !
end

macro puts
  dup @ dup while
    putc
    dup @ dup
  end
  
  drop drop
end

"hello, world!" puts

; infinite loop
1 while 1 end

; goal: simple forth in those 8k, able to load programs, edit files and such
