    .global diag
diag:

    push %ebp
    mov  %esp, %ebp

    movss	8(%ebp), %xmm0
    movss	12(%ebp), %xmm1
    movss	16(%ebp), %xmm2

		mulss	%xmm0, %xmm0
    mulss	%xmm1, %xmm1
    mulss	%xmm2, %xmm2

    addss	%xmm0, %xmm1
    addss %xmm1, %xmm2

    sqrtss %xmm2, %xmm2

    movss %xmm2, -4(%esp)
    flds -4(%esp)

    pop  %ebp
    ret
