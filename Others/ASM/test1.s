
test1.o:     file format pe-x86-64


Disassembly of section .text:

0000000000000000 <main>:
int a=3,b=2;

int main()
{
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	48 83 ec 30          	sub    rsp,0x30
   8:	e8 00 00 00 00       	call   d <main+0xd>
	int c=0;
   d:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [rbp-0x4],0x0
	for (int i=0;i<100;i++)
  14:	c7 45 f8 00 00 00 00 	mov    DWORD PTR [rbp-0x8],0x0
  1b:	83 7d f8 63          	cmp    DWORD PTR [rbp-0x8],0x63
  1f:	7f 0a                	jg     2b <main+0x2b>
		c+=2;
  21:	83 45 fc 02          	add    DWORD PTR [rbp-0x4],0x2
	for (int i=0;i<100;i++)
  25:	83 45 f8 01          	add    DWORD PTR [rbp-0x8],0x1
  29:	eb f0                	jmp    1b <main+0x1b>
	a=a+c;
  2b:	8b 15 00 00 00 00    	mov    edx,DWORD PTR [rip+0x0]        # 31 <main+0x31>
  31:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
  34:	01 d0                	add    eax,edx
  36:	89 05 00 00 00 00    	mov    DWORD PTR [rip+0x0],eax        # 3c <main+0x3c>
    b++;
  3c:	8b 05 04 00 00 00    	mov    eax,DWORD PTR [rip+0x4]        # 46 <main+0x46>
  42:	83 c0 01             	add    eax,0x1
  45:	89 05 04 00 00 00    	mov    DWORD PTR [rip+0x4],eax        # 4f <main+0x4f>
    ++a;
  4b:	8b 05 00 00 00 00    	mov    eax,DWORD PTR [rip+0x0]        # 51 <main+0x51>
  51:	83 c0 01             	add    eax,0x1
  54:	89 05 00 00 00 00    	mov    DWORD PTR [rip+0x0],eax        # 5a <main+0x5a>
    b+=a;
  5a:	8b 15 04 00 00 00    	mov    edx,DWORD PTR [rip+0x4]        # 64 <main+0x64>
  60:	8b 05 00 00 00 00    	mov    eax,DWORD PTR [rip+0x0]        # 66 <main+0x66>
  66:	01 d0                	add    eax,edx
  68:	89 05 04 00 00 00    	mov    DWORD PTR [rip+0x4],eax        # 72 <main+0x72>
	return a;
  6e:	8b 05 00 00 00 00    	mov    eax,DWORD PTR [rip+0x0]        # 74 <main+0x74>
  74:	48 83 c4 30          	add    rsp,0x30
  78:	5d                   	pop    rbp
  79:	c3                   	ret    
  7a:	90                   	nop
  7b:	90                   	nop
  7c:	90                   	nop
  7d:	90                   	nop
  7e:	90                   	nop
  7f:	90                   	nop
