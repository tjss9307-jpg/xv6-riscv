#include "kernel/types.h"
#include "user/user.h"

int main(){
    int y = getNumProc();
    printf("no of active procs = %d\n" , y);
    return 0;
}