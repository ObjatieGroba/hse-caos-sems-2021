/// int nth_elem(int a, int b, int n) - nый член арифметической прогрессии

    .text
    .global nth_elem
nth_elem:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %eax
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx

    sub %eax, %ecx
    dec %edx
    imul %edx, %ecx

    add %ecx, %eax

    mov %ebp, %esp
    pop %ebp
    ret
