	.text
    .global f
f:
    mov str, %edx
    mov $0, %eax

loop:
  	// movb (%edx), %cl
    // cmpb $0, %cl
  	cmpb $0, (%edx)
    jz end
    inc %edx
    inc %eax
    jmp loop

end:
    ret
