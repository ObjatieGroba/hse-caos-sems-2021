    .global main
main:
    call readi32
cycle:
    call writei32

    cmp $1, %eax
    je  end

    mov %eax, %ebx
    sar $1, %ebx
    jc odd
    mov %ebx, %eax

    jmp  cycle
odd:
    mov %eax, %ebx
    add %eax, %ebx
    add %eax, %ebx
    add $1, %ebx
    mov %ebx, %eax
    jmp cycle

end:
    call finish