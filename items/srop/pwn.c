#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

char bss[0x300];

int LiTangSt4r(){
    return 15;
}

void foo(){
    asm volatile (
        "syscall\n"
        "ret\n"
    );
}

int main() {
    char buf[0x20];
    read(0, buf, 0x200);
    return 0;
}
