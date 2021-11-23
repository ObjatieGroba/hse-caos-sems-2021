/// Написать void my_call(int *elem, func p);
/// typedef void (*func)(int *);

    .global my_call
my_call:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %ecx     // elem
    mov 12(%ebp), %edx    // p

    push %ecx
    call *%edx

    mov %ebp, %esp
    pop %ebp
    ret


/// void foreach(int *arr, unsigned size, func p);

    .global foreach
foreach:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %eax     // arr
    mov 12(%ebp), %ecx    // size
    mov 16(%ebp), %edx    // func

loop:
	cmp $0, %ecx
    je return

    push %edx
    push %ecx
    push %eax
    call *%edx // calling conv
    /// addl $4, %esp
    pop %eax
    pop %ecx
    pop %edx

    dec %ecx
    add $4, %eax
    jmp loop

return:
    mov %ebp, %esp
    pop %ebp
    ret