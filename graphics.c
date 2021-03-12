#include <stdio.h>
char screenn=3;
char backcolor=0;
int screenxx=0;
int screensize=1;

extern void vlines( );
#pragma aux vlines=    \
"push bp"\
"push ds"\
"mov bx,screenxx"\
"mov cx,screensize"\
"mov dh,backcolor"\
"mov ax,0xa000"\
"mov ds,ax"\
"mov al,dh"\
"xxxx:"\
"mov [bx],al"\
"add bx,320"\
"dec cx"\
"cmp cx,-1"\
"jnz xxxx"\
"pop ds"\
"pop bp"\
 modify [ax bx cx dx];
 
 void vline(int x,int y,int h,char color){
	screenxx=y*320+x;
	backcolor=color;
	screensize=h;
	vlines();
	
	}


extern void hlines( );
#pragma aux hlines=    \
"push bp"\
"push ds"\
"mov bx,screenxx"\
"mov cx,screensize"\
"mov dh,backcolor"\
"mov ax,0xa000"\
"mov ds,ax"\
"mov al,dh"\
"xxxx:"\
"mov [bx],al"\
"inc bx"\
"dec cx"\
"cmp cx,-1"\
"jnz xxxx"\
"pop ds"\
"pop bp"\
 modify [ax bx cx dx];


void hline(int x,int y,int w,char color){
	screenxx=y*320+x;
	backcolor=color;
	screensize=w;
	hlines();
	
	}


extern void backs( );
#pragma aux backs=    \
"push bp"\
"push ds"\
"mov bl,backcolor"\
"mov ax,0xa000"\
"mov ds,ax"\
"mov al,bl"\
"mov bx,64000"\
"xxx:"\
"mov[bx],al"\
"dec bx"\
"cmp bx,-1"\
"jnz xxx"\
"pop ds"\
"pop bp"\
 modify [ax bx];


void back(char color){
	backcolor=color;
	backs();
	}


extern void screennn( );
#pragma aux screennn=    \
    "push bp"                  \
     "xor ax,ax"\
     "mov al,screenn"\
     "int 0x10"\
     "pop bp"          \
     modify [ax];

void screen(int n){
	screenn=(char)n;
	screennn();
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
	int i=0;
	int color =0;
	screen(0x13);
	
	back(8);
	for(i=0;i<201;i=i+8){
	hline(0,i,320,color);
	color++;
	}
	color=0;
	for(i=0;i<321;i=i+8){
	vline(i,0,199,color);
	color++;
	}
	esckeys();
screen(0x3);
	exits();
	return 0;
}
