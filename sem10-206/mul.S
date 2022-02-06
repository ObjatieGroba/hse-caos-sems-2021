// float neg(float a) {return -a;}


neg:
push %ebx
        mov %esp, %ebp

        xorps %xmm0, %xmm0
        movuss 8(%ebp), %xmm0
        mulss minus_one, %xmm0

//куда возвращать?)
sub     $4, %esp        // резервируем память
movss   %xmm0, (%esp)   // копируем значение double из %xmm0 в стек
fld    (%esp)          // загружаем из стека на %st(0)
add     $4, %esp        // очищаем стек

end:
pop %ebp
        ret

.data
        minus_one:
.double -1
