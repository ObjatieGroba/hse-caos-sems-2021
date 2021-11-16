    .text
    .global main
main:
    push %ebp
    mov %esp, %ebp
    
    sub $21, %esp
    mov %esp, %ebx
    
    push %ebx
    push $format
    call scanf
    
    add $8, %esp
    
    push %ebx
    push $format2
    call printf
    
    mov %ebp, %esp
    pop %ebp
    ret
    
    
format:
    .asciz "%20s"
    // .ascii "adadaw"
    // .byte '%'
format2:
    .asciz "%s\n"
