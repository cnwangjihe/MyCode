
asm_1.o:     file format pe-x86-64


Disassembly of section .text:

0000000000000000 <_Z11add_a_and_bii>:
int add_a_and_b(int a, int b) {
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	89 4d 10             	mov    DWORD PTR [rbp+0x10],ecx
   7:	89 55 18             	mov    DWORD PTR [rbp+0x18],edx
   return a + b;
   a:	8b 55 10             	mov    edx,DWORD PTR [rbp+0x10]
   d:	8b 45 18             	mov    eax,DWORD PTR [rbp+0x18]
  10:	01 d0                	add    eax,edx
}
  12:	5d                   	pop    rbp
  13:	c3                   	ret    

0000000000000014 <main>:

int main() {
  14:	55                   	push   rbp
  15:	48 89 e5             	mov    rbp,rsp
  18:	48 83 ec 20          	sub    rsp,0x20
  1c:	e8 00 00 00 00       	call   21 <main+0xd>
   return add_a_and_b(2, 3);
  21:	ba 03 00 00 00       	mov    edx,0x3
  26:	b9 02 00 00 00       	mov    ecx,0x2
  2b:	e8 d0 ff ff ff       	call   0 <_Z11add_a_and_bii>
  30:	90                   	nop
  31:	48 83 c4 20          	add    rsp,0x20
  35:	5d                   	pop    rbp
  36:	c3                   	ret    
  37:	90                   	nop
  38:	90                   	nop
  39:	90                   	nop
  3a:	90                   	nop
  3b:	90                   	nop
  3c:	90                   	nop
  3d:	90                   	nop
  3e:	90                   	nop
  3f:	90                   	nop
