#include <stdio.h>
#include <stdlib.h>

/* A statically allocated variable */
int foo;

extern int recur(int i);

/* A statically allocated, pre-initialized variable */
volatile int stuff = 7;

/* Print addresses in recur for stack inspection */
int recur(int i) {
    volatile int stack_var = i;
    printf("recur call %d: stack@ %p\n", i, (void*)&stack_var);
    if (i > 0) recur(i - 1);
    return 0;
}

int main(int argc, char *argv[]) {
    /* A stack allocated variable */
    volatile int i = 0;

    /* Dynamically allocate some stuff */
    volatile char *buf1 = malloc(100);
    /* ... and some more stuff */
    volatile char *buf2 = malloc(100);

    printf("_main @ %p\n", (void*)main);
    printf("foo (static) @ %p\n", (void*)&foo);
    printf("stuff (static, pre-init) @ %p\n", (void*)&stuff);
    printf("main stack var @ %p\n", (void*)&i);
    printf("Heap: malloc 1: %p\n", (void*)buf1);
    printf("Heap: malloc 2: %p\n", (void*)buf2);

    recur(3);

    free((void*)buf1);
    free((void*)buf2);
    return 0;
}