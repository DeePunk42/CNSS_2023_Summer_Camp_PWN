#include<stdlib.h>
#define s 0x430
int main(){
        void * a[100];
//        for(int i=1;i<=7;i++)
//                a[i]=malloc(s);
        void * ptr =malloc(s);
        malloc(s);
//        for(int i=1;i<=7;i++)
//                free(a[i]);
        free(ptr);
        malloc(0x500);
       }
