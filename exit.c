

extern void shutdown( );
#pragma aux shutdown=    \
"xor ax,ax"\
 "int 0x19"\
    "mov ax,0xf000"                  \
    "push ax"\
    "mov ax,0xfff0"\
    "push ax"\
 "retf"\
   modify [ax];
     
int main(){
	shutdown();
	
	

	
	return 0;
}
