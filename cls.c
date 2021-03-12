#include <stdio.h>

extern void cls( );
#pragma aux cls=    \
    "push bp"                  \
    "mov cx,2000" \
    "mov ax,0xb800 " \
    "push ds" \
   "mov ds,ax" \
   "mov bx,0" \
   "mov ax,720h"\
    "x:"                 \
    "mov [bx],ax" \
    "inc bx" \
    "inc bx"\
    "inc al" \
    "dec cx"\
    "jnz x"\
    "pop ds" \
     "pop bp"          \
     modify [ax bx cx dx si di];
     
extern void exits( );
#pragma aux exits=    \
"mov ax,0ffffh"\
"mov sp,ax"\
    "mov ax,1000h"\
    "push ax"\
     "mov ax,100h"\
    "push ax"\   
             "retf"\
    modify [ax bx cx dx si di];

extern void esckeys( );
#pragma aux esckeys=    \
    "push bp"                  \
"esckeyss:" \
"mov ax,0" \
"int 16h" \
"cmp al,27"\
"jnz esckeyss" \
     "pop bp"         \
modify [ax bx cx dx si di];


int main(){
	cls();
	
	//esckeys();

	exits();
	return 0;
}
