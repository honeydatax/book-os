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
int xxx=0;
int yyy=0;
unsigned axax=0;
unsigned bxbx=0;
unsigned cxcx=0;
unsigned dxdx=0;
unsigned sisi=0;
unsigned didi=0;
unsigned bpbp=0;
unsigned dsds=0;
unsigned eses=0;
char *cc="  \0";
             int aah;
             int aaa;
             int bbb;
             int ccc;
             int ddd;

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

extern int keys( );
#pragma aux keys=    \
    "push bp"                  \
"mov ax,0" \
"int 16h" \
     "pop bp"         \
     value [ax]\
     modify [ax bx cx dx si di];
     
extern void rreads();
#pragma aux rreads=    \
"push bp"\
"push es"\
"mov ax,0x2000"\
"mov es,ax"\
"mov es,ax"\
"mov dl,diskdl"\
"mov dh,diskdh"\
"mov cl,diskcl"\
"mov ch,diskch"\
"mov al,127"\
"mov ah,2"\
"mov bx,0x100"\
"int 13h"\
"pop es"\
"pop bp"\
modify [ax bx cx dx si di];

void rread(int sectores,char drive){
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
	rreads();
	}
	
extern int run( );
#pragma aux run=    \
    "push bp"                  \
"mov ax,0xffff" \
"mov sp,ax"\
"mov ax,0x2000"\
"mov ss,ax"\
"mov ax,0x1000"\
"push ax"\
"mov ax,0x100"\
"push ax"\
"mov ax,0x2000"\
"push ax"\
"mov ax,0x100"\
"push ax"\
"mov ax,0x2000"\
"mov ds,ax"\
"mov es,ax"\
"mov ax,0"\
"mov bx,0"\
"mov cx,0"\
"mov dx,0"\
"retf" \
     "pop bp"         \
     modify [ax bx cx dx si di];
     
     
     
int runs(int drive , char *file){
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
			rread(sect,drive);
			run();
			i=34;
		}
		p1=p1+32;
}
return ii;
}

extern int dss( );
#pragma aux dss=    \
"mov ax,0x1000"\
"mov ds,ax"\
  modify [ax di];

extern int dss1( );
#pragma aux dss1=    \
"mov ax,0x1000"\
"mov es,ax"\
  modify [ax di];



extern int dsss( );
#pragma aux dsss=    \
"mov ax,0x2000"\
"mov ds,ax"\
  modify [ax];

extern int retss( );
#pragma aux retss=    \
"mov ax,dsds"\
"push ax"\
"mov ax,axax"\
"push ax"\
"mov ax,eses"\
"push ax"\
"mov ax,bxbx"\
"push ax"\
"mov ax,cxcx"\
"push ax"\
"mov ax,dxdx"\
"push ax"\
"mov ax,sisi"\
"push ax"\
"mov ax,didi"\
"push ax"\
"mov ax,bpbp"\
"push ax"\
"pop bp"\
"pop di"\
"pop si"\
"pop dx"\
"pop cx"\
"pop bx"\
"pop es"\
"pop ax"\
"pop ds"\
  modify [ax bx cx dx si di];

void _interrupt int20( ){
	exits();
   }
 

void _interrupt int21( unsigned bp, unsigned di, unsigned si,
                                  unsigned ds, unsigned es, unsigned dx,
                                  unsigned cx, unsigned bx, unsigned ax){



             dss();
             aah=ax/256;
             aaa=ax &  255;
             ddd=dx & 255;
             if(aah==0)exits();
             if(aah==2){
             	dss1( );
             	cc[0]=ddd;
             print(&cc[0],xxx,yyy,0x70,1);
             xxx=xxx+1;
             if(xxx>79 || ddd== 13 || ddd==10){
             	yyy++;
             xxx=0;
             	}
             if (yyy>20)yyy=0;
             }
             axax=ax;
             bpbp=bp;
             didi=di;
             sisi=si;
             dsds=ds;
             eses=es;
             dxdx=dx;
             cxcx=cx;
             bxbx=bx;
             retss();
             
             
}




extern int internals( );
#pragma aux internals=    \
    "push bp"  \
    "push ds" \
        "push es" \
    " lea ax,int20"\
    "mov dx,ax"\
     "lea ax,int21"\
    "mov cx,ax"\
    "mov ax,0"\
    "mov ds,ax"\
   "mov bx,128"\
   "mov ax,0x1000"\
   "mov [bx],dx"\
   "inc bx"\
   "inc bx"\
   "mov [bx],ax"\
   "inc bx"\
   "inc bx"\
   "mov [bx],cx"\
   "inc bx"\
   "inc bx"\
   "mov [bx],ax"\
   "pop es"\
   "pop ds"\
   "pop bp"\
  modify [ax bx cx dx si di];

extern int status( );
#pragma aux status=    \
    "push bp"                  \
    "mov ax,0x1000"\
    "mov es,ax"\
    "mov ax,0x2000"\
    "mov ds,ax"\
  "mov ax,sp"\
  "mov si,ax"\
  "mov di,ax"\
  "status1:"\
  "mov al,[si]"\
  "mov [di],al"\
  "inc di"\
  "inc si"\
  "cmp si,0"\
  "jnz status1"\
"mov ax,0x1000"\
"mov ss,ax"\
"mov ax,0x1000"\
"push ax"\
"mov ax,0x100"\
"push ax"\
"mov ax,0x2000"\
"push ax"\
"mov ax,0x100"\
"push ax"\
"mov ax,0x2000"\
"mov ds,ax"\
"mov es,ax"\
"mov ax,0"\
"mov bx,0"\
"mov cx,0"\
"mov dx,0"\
"retf" \
     "pop bp"         \
     modify [ax bx cx dx si di];
     


void menu(){
	int i=0;
	int ii=0;
	char c[34];
	char *p1;
	// for start firth time in not to long use must run the dread 8 times firt sector to time of disk motor to start up time to motor start speed up
	for (i=0;i<8;i++)
	dread(0,0);
	diskal=4;
	dread(19,0);
	p1=bufferdisk;
	for(i=0;i<26;i++){
		selectfile(&c,p1);
		c[14]=65+i;
print(c,(i/18)*16,i-((i/18)*18),0x70,15);
p1=p1+32;

	}
select:
ii=keys() & 255;
if(ii>64 && ii<65+26)goto select2;
goto select;
select2:
ii=ii-65;
for (i=0;i<8;i++)
	dread(0,0);
	diskal=4;
	dread(19,0);
	p1=bufferdisk;
	for(i=0;i<ii+1;i++){
		selectfile(&c,p1);
p1=p1+32;

	}
	runs (0,c);
	}
	

