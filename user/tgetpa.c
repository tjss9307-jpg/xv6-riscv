#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int global_var = 100;

int main() {
    int local_var = 42;

    // 1. Test global variable
    uint64 pa_global = getpa(&global_var);
    if (pa_global == (uint64)-1)
        printf("Global var VA %p is invalid\n", &global_var);
    else
        printf("Global var VA %p -> PA 0x%lx\n", &global_var, pa_global);

    // 2. Test local (stack) variable
    uint64 pa_local = getpa(&local_var);
    if (pa_local == (uint64)-1)
        printf("Local var VA %p is invalid\n", &local_var);
    else
        printf("Local var VA %p -> PA 0x%lx\n", &local_var, pa_local);

    // 3. Test heap variable
    int *heap_var = malloc(sizeof(int));
    *heap_var = 55;
    uint64 pa_heap = getpa(heap_var);
    if (pa_heap == (uint64)-1)
        printf("Heap var VA %p is invalid\n", heap_var);
    else
        printf("Heap var VA %p -> PA 0x%lx\n", heap_var, pa_heap);

    // 4. Test invalid address
    uint64 pa_invalid = getpa((void*)0xdeadbeef);
    if (pa_invalid == (uint64)-1)
        printf("Invalid VA 0xdeadbeef correctly returned -1\n");
    else
        printf("Invalid VA returned PA 0x%lx (unexpected)\n", pa_invalid);

    free(heap_var);

    exit(0);
}