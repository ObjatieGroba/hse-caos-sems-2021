    .text
    .global f

f:
    /// Пролог
    // push %ebp
    // mov %esp, %ebp

    sub $4, %esp
    //subl $4, %esp
    //nop
    add $4, %esp

    /// Эпилог
    // mov %ebp, %esp
    // pop %ebp

    mov $xxxx, %eax
    mov $7, (%eax)

    ret

    //.data
    //.global xxxx
//xxxx:
    //.int 0
