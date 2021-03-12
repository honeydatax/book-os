#include <stdio.h>
#include <string.h>

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
    

extern int keys( );
#pragma aux keys=    \
    "push bp"                  \
"mov ax,0" \
"int 16h" \
     "pop bp"         \
     value [ax]\
     modify [ax bx cx dx si di];

void getstring(char *s1,int x,int y,int len){
	int i=0;
	char c='0';
	int exits=0;
	int bacs=0;
	s1[0]=0;
	for(i=0;i<len;i++){
		bacs=0;
		c=keys();
		if(c==13){
			c=0;
			exits=-1;
			}
			if(c==8 && i>0){
				s1[i-1]=32;
				s1[i]=32;
				s1[i+1]=0;
				print(s1,x,y,0x70,i+1);
				i=i-1;
				c=0;
				bacs=-1;
				
				}
			s1[i]=c;
			s1[i+1]=0;
			
	if(bacs==0)print(s1,x,y,0x70,i+1);
	if(bacs==-1)i--;
	if (exits==-1) i=len+2;
	}
	}


int main(){
	char c[200];
	
getstring(&c,10,10,198);


exits();
	return 0;
}
