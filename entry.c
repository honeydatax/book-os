#include <stdio.h>

int cursorx=0;
int cursory=0;
char *cursors1;
int cursorsize=1;
char cursorcolor =7;
int cursorpos=0;
char bufferdisk[520];
char diskal=1; //sectores to read
char diskch=0 ;//cilinder
char diskcl=1; //sector
char diskdh=0 ;//head
char diskdl=0;//drive 0
int diskes=0;//segment
char *diskbx=&bufferdisk;//buffer

extern void dreads();
#pragma aux dreads=    \
"push bp"\
"push es"\
"mov ax,ds"\
"mov es,ax"\
"mov es,ax"\
"mov dl,diskdl"\
"mov dh,diskdh"\
"mov cl,diskcl"\
"mov ch,diskch"\
"mov al,diskal"\
"mov ah,2"\
"mov bx,diskbx"\
"int 13h"\
"pop es"\
"pop bp"\
modify [ax bx cx dx si di];



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
	cursorpos=y*80+x*2;
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
	int i=0;
	diskcl=2;
	// for start firth time in not to long use must run the dread 8 times firt sector to time of disk motor to start up time to motor start speed up
for (i=0;i<8;i++)
	dreads();
print(bufferdisk,0,0,0x70,512);

	
	esckeys();
exits();
	return 0;
}
