struct A {
    char x;
    int y;
};

struct A * glob_a;

struct A glob_s_a[100];

void process(struct A * a, int i) {
    void * v = (void*)a; // reitrerpret_cast<void *>(a):
    char * x = (char*)v; // %eax

    *x = 'a'; /// movb 'a', (%eax)

    int * y = (int *)((intptr_t)a + sizeof(int)); /// %ebx = %eax + 4

    *y = 2; /// movl $2, 4(%eax)
    *y = 2; /// movl $2, (%ebx)

    // T * t;
    // t + n; (t) + n * sizeof(T);

//    a += i;
    i = i; // %esi
    // lea (%eax, %esi, 8);

    // lea glob_s_a(, %esi, 8);

}
