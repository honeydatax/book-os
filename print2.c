#include <stdio.h>

int cursorx=0;
int cursory=0;
char *cursors1;
int cursorsize=1;
char cursorcolor =7;
int cursorpos=0;

extern void printss();
#pragma aux printss=    \
    "push bp"                  \
    "push es"\
    "push ds" \
    "push si" \
        "push di" \
   "mov ax,cursors1"\
   "mov si,ax"\
"mov ax,cursorpos"\
         "mov di,ax"\
     "mov cx,cursorsize" \
    "mov bx,0xb800 " \
    "mov dx,ds" \
       "mov es,ax" \
     "mov ah,cursorcolor"\  
    "wx:"                 \
    "mov ds,dx"\
    "ds"\
        "mov al,[si]" \
                "mov ds,bx"\
        "ds"\
    "mov [di],ax" \
    "inc si" \
     "inc di" \
     "inc di" \
    "dec cx"\
    "jnz wx"\
    "pop  di"\
    "pop si"\
    "pop ds"\
    "pop es" \
     "pop bp"            \
modify [ax bx cx dx si di];
     
void print(char *s1,int x , int y, int color,int size){
	cursorpos=y*160+x*2;
	cursorcolor=(char) color;
	cursors1=s1;
	cursorsize=size;
	
     printss();
    
     
}
     
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
	char *c="hello world.";
	int i=0;
	for(i=0; i<16;i++){
print(c,i,i,i+0x70,12);
}

	
	esckeys();
exits();
	return 0;
}
