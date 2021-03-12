#include <stdio.h>
#include <string.h>

int cursorx=0;
int cursory=0;
char *cursors1;
int cursorsize=1;
char cursorcolor =7;
int cursorpos=0;
char bufferdisk[4100];
char diskal=1; //sectores to read
char diskch=0 ;//cilinder
char diskcl=1; //sector
char diskdh=0 ;//head
char diskdl=0;//drive 0
int diskes=0;//segment
char *diskbx=&bufferdisk;//buffer
int diskheads=2;
int diskcilinders=80;
int disksectores=18;

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

void dread(int sectores,char drive){
	int headcilinder=diskheads*disksectores;
	int head=0;
	int cilinder=0;
	int sector=0;
	int i=0;
	diskdl=drive;
	cilinder=sectores/headcilinder;
	i=sectores-(headcilinder*cilinder);
	head=i/diskcilinders;
	sector=i-(head*diskcilinders);
	sector++;
	diskcl=(char)sector;
	diskch=(char)cilinder;
	cilinder=cilinder/256;
	cilinder=cilinder*16;
	diskdh=head | cilinder;
	dreads();
	}

void selectfile(char *into,char *from){
	int i=0;
	char *s1;
	char namef[9];
	char extf[4];
	char *names;
	char *exts;
	names=from;
	exts=names+8;
	strncpy(&namef,names,9);
	strncpy(&extf,exts,3);
	namef[8]=0;
	extf[3]=0;
	s1=strstr(&namef," ");
	if(s1!=NULL)s1[0]=0;
	s1=strstr(&extf," ");
	if(s1!=NULL)s1[0]=0;
	
	for (i=0;i<31;i++)
	   into[i]=32;
	
	sprintf(into,"%s.%s",&namef,&extf);
	
	
	}

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

int loads(int drive , char *file){
	int i ;
	int ii;
	char c[34];
	char *p1;
	int sect=0;
	// for start firth time in not to long use must run the dread 8 times firt sector to time of disk motor to start up time to motor start speed up
	for (i=0;i<8;i++)
	dread(0,0);
	diskal=4;
	dread(19,0);
	p1=bufferdisk;
	for(i=0;i<32;i++){
		selectfile(&c,p1);
		if (strcmp(&c,file)==0){
			p1=p1+0x1a;
			sect=p1[0]+p1[1]*256+31;
			ii=p1[2]+p1[3]*256;
			dread(sect,drive);
			i=34;
		}
		p1=p1+32;
}
return ii;
}

char *labels(int drive){
	char *p1;
	int i;
	int sect=0;
	diskal=1; 
	// for start firth time in not to long use must run the dread 8 times firt sector to time of disk motor to start up time to motor start speed up
	for (i=0;i<8;i++)
	dread(sect,drive);
	p1=bufferdisk;
	p1=p1+0x2B;
	p1[12]=0;
	return p1;
	}

extern void dwrites();
#pragma aux dwrites=    \
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
"mov ah,3"\
"mov bx,diskbx"\
"int 13h"\
"pop es"\
"pop bp"\
modify [ax bx cx dx si di];


void dwrite(int sectores,char drive){
	int headcilinder=diskheads*disksectores;
	int head=0;
	int cilinder=0;
	int sector=0;
	int i=0;
	diskdl=drive;
	cilinder=sectores/headcilinder;
	i=sectores-(headcilinder*cilinder);
	head=i/diskcilinders;
	sector=i-(head*diskcilinders);
	sector++;
	diskcl=(char)sector;
	diskch=(char)cilinder;
	cilinder=cilinder/256;
	cilinder=cilinder*16;
	diskdh=head | cilinder;
	dwrites();
	}

void setlabels(int drive,char *name){
	char names[12];
	char *p1;
	int i;
	int sect=0;
	diskal=1; 
	// for start firth time in not to long use must run the dread 8 times firt sector to time of disk motor to start up time to motor start speed up
	for (i=0;i<8;i++)
	dread(sect,drive);
	for (i=0;i<12;i++)
	names[i]=32;
	i=strlen(name);
	if(i>11)i=11;
	strncpy(names,name,i);
	p1=bufferdisk;
	p1=p1+0x2B;
	strncpy(p1,names,11);
	diskal=1; 
	dwrite(sect,drive);
	}

int saves(int drive , char *file,char *text){
	int i ;
	int ii;
	int iii=0;
	char c[34];
	char *p1;
	int sect=0;
	diskal=1;
	// for start firth time in not to long use must run the dread 8 times firt sector to time of disk motor to start up time to motor start speed up
	for (i=0;i<8;i++)
	dread(0,0);
	diskal=4;
	dread(19,0);
	p1=bufferdisk;
	for(i=0;i<32;i++){
		selectfile(&c,p1);
		if (strcmp(&c,file)==0){
			p1=p1+0x1a;
			sect=p1[0]+p1[1]*256+31;
			ii=p1[2]+p1[3]*256;
			ii=ii/512+1;
			if(ii>4)ii=4;
			diskal=ii;
		      strncpy(diskbx,text,4096);
			dwrite(sect,drive);
			i=34;
			iii=1;
		}
		p1=p1+32;
}
if(iii==0)print("workspace of name must be on table...........",0,3,0x70,35);
return iii;
}

int main(){
	char *name="hello hi theres 1234567890";
	char *p;
	int i=11;
saves(0,"OUT.TXT",name);
	
	esckeys();
exits();
	return 0;
}
