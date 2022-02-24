macro swap
  ! 0x20FE
  ! 0x20FF
  ? 0x20FE
  ? 0x20FF
end

252 dup while
  dup 255 + dup ! 0xFC
  255 + dup
then

drop halt
