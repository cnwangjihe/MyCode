
#1.o:     file format pe-x86-64


Disassembly of section .text:

0000000000000000 <main>:


int a=10,b=10;

int main()
{
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	48 83 ec 20          	sub    rsp,0x20
   8:	e8 00 00 00 00       	call   d <main+0xd>
	printf("%d",a+b);
   d:	8b 15 00 00 00 00    	mov    edx,DWORD PTR [rip+0x0]        # 13 <main+0x13>
  13:	8b 05 04 00 00 00    	mov    eax,DWORD PTR [rip+0x4]        # 1d <main+0x1d>
  19:	01 d0                	add    eax,edx
  1b:	89 c2                	mov    edx,eax
  1d:	48 8d 0d 00 00 00 00 	lea    rcx,[rip+0x0]        # 24 <main+0x24>
  24:	e8 00 00 00 00       	call   29 <main+0x29>
  29:	b8 00 00 00 00       	mov    eax,0x0
  2e:	48 83 c4 20          	add    rsp,0x20
  32:	5d                   	pop    rbp
  33:	c3                   	ret    
  34:	90                   	nop
  35:	90                   	nop
  36:	90                   	nop
  37:	90                   	nop
  38:	90                   	nop
  39:	90                   	nop
  3a:	90                   	nop
  3b:	90                   	nop
  3c:	90                   	nop
  3d:	90                   	nop
  3e:	90                   	nop
  3f:	90                   	nop
