    .global main
main:
    call    readi64
    jc      fail
    mov  %eax, %ebx
    mov  %edx, %ecx
    // movl  %al, %bl

    call    readi32
    jc      fail
    cdq

    add  %ebx, %eax
    adc  %ecx, %edx

    call writei64

    call    finish
fail:
    mov $-1, %eax
    call writei32
    call finish

loop:
    jmp loop

