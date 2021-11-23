    .text
    .global main
main:
    push %ebp
    mov %esp, %ebp

    // pushf
    // orl $(1<<18), (%esp)
    // popf
    
    sub $21, %esp
    mov %esp, %ebx
    // sub $3, %esp
    
    push %ebx
    push $format
    call scanf
    
    add $8, %esp
    
    push %ebx
    push $format2
    call printf
    
    mov %ebp, %esp
    pop %ebp

    mov $0, %eax
    ret
    
    
format:
    .asciz "%20s"
    // .ascii "adadaw"
    // .byte '%'
format2:
    .asciz "%s\n"
