
P4035.o:     file format pe-x86-64


Disassembly of section .text:

0000000000000000 <_Z5GaussPA13_di>:

double a[MAXN][MAXN],f[MAXN][MAXN];
int n;

bool Gauss(double a[MAXN][MAXN],int n)
{
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	48 83 ec 40          	sub    rsp,0x40
   8:	48 89 4d 10          	mov    QWORD PTR [rbp+0x10],rcx
   c:	89 55 18             	mov    DWORD PTR [rbp+0x18],edx
	int id;
	for (int i=1;i<=n;i++)
   f:	c7 45 f8 01 00 00 00 	mov    DWORD PTR [rbp-0x8],0x1
  16:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
  19:	3b 45 18             	cmp    eax,DWORD PTR [rbp+0x18]
  1c:	0f 8f fa 01 00 00    	jg     21c <_Z5GaussPA13_di+0x21c>
	{
		id=i;
  22:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
  25:	89 45 fc             	mov    DWORD PTR [rbp-0x4],eax
		for (int j=i+1;j<=n;j++)
  28:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
  2b:	83 c0 01             	add    eax,0x1
  2e:	89 45 f4             	mov    DWORD PTR [rbp-0xc],eax
  31:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
  34:	3b 45 18             	cmp    eax,DWORD PTR [rbp+0x18]
  37:	7f 66                	jg     9f <_Z5GaussPA13_di+0x9f>
			if (fabs(a[j][i])-fabs(a[id][i])>eps)
  39:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
  3c:	48 98                	cdqe   
  3e:	48 6b c0 68          	imul   rax,rax,0x68
  42:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
  46:	48 01 c2             	add    rdx,rax
  49:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
  4c:	48 98                	cdqe   
  4e:	f2 0f 10 04 c2       	movsd  xmm0,QWORD PTR [rdx+rax*8]
  53:	f3 0f 7e 0d c0 00 00 	movq   xmm1,QWORD PTR [rip+0xc0]        # 11b <_Z5GaussPA13_di+0x11b>
  5a:	00 
  5b:	66 0f 54 c1          	andpd  xmm0,xmm1
  5f:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
  62:	48 98                	cdqe   
  64:	48 6b c0 68          	imul   rax,rax,0x68
  68:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
  6c:	48 01 c2             	add    rdx,rax
  6f:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
  72:	48 98                	cdqe   
  74:	f2 0f 10 0c c2       	movsd  xmm1,QWORD PTR [rdx+rax*8]
  79:	f3 0f 7e 15 c0 00 00 	movq   xmm2,QWORD PTR [rip+0xc0]        # 141 <_Z5GaussPA13_di+0x141>
  80:	00 
  81:	66 0f 54 ca          	andpd  xmm1,xmm2
  85:	f2 0f 5c c1          	subsd  xmm0,xmm1
  89:	66 0f 2f 05 d0 00 00 	comisd xmm0,QWORD PTR [rip+0xd0]        # 161 <_Z5GaussPA13_di+0x161>
  90:	00 
  91:	76 06                	jbe    99 <_Z5GaussPA13_di+0x99>
				id=j;
  93:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
  96:	89 45 fc             	mov    DWORD PTR [rbp-0x4],eax
		for (int j=i+1;j<=n;j++)
  99:	83 45 f4 01          	add    DWORD PTR [rbp-0xc],0x1
  9d:	eb 92                	jmp    31 <_Z5GaussPA13_di+0x31>
		if (id!=i)
  9f:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
  a2:	3b 45 f8             	cmp    eax,DWORD PTR [rbp-0x8]
  a5:	74 58                	je     ff <_Z5GaussPA13_di+0xff>
			for (int j=1;j<=n+1;j++)
  a7:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
  ae:	8b 45 18             	mov    eax,DWORD PTR [rbp+0x18]
  b1:	83 c0 01             	add    eax,0x1
  b4:	39 45 f0             	cmp    DWORD PTR [rbp-0x10],eax
  b7:	7f 46                	jg     ff <_Z5GaussPA13_di+0xff>
				std::swap(a[id][j],a[i][j]);
  b9:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
  bc:	48 98                	cdqe   
  be:	48 6b c0 68          	imul   rax,rax,0x68
  c2:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
  c6:	48 01 c2             	add    rdx,rax
  c9:	8b 45 f0             	mov    eax,DWORD PTR [rbp-0x10]
  cc:	48 98                	cdqe   
  ce:	48 c1 e0 03          	shl    rax,0x3
  d2:	48 01 c2             	add    rdx,rax
  d5:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
  d8:	48 98                	cdqe   
  da:	48 6b c0 68          	imul   rax,rax,0x68
  de:	48 8b 4d 10          	mov    rcx,QWORD PTR [rbp+0x10]
  e2:	48 01 c1             	add    rcx,rax
  e5:	8b 45 f0             	mov    eax,DWORD PTR [rbp-0x10]
  e8:	48 98                	cdqe   
  ea:	48 c1 e0 03          	shl    rax,0x3
  ee:	48 01 c8             	add    rax,rcx
  f1:	48 89 c1             	mov    rcx,rax
  f4:	e8 00 00 00 00       	call   f9 <_Z5GaussPA13_di+0xf9>
			for (int j=1;j<=n+1;j++)
  f9:	83 45 f0 01          	add    DWORD PTR [rbp-0x10],0x1
  fd:	eb af                	jmp    ae <_Z5GaussPA13_di+0xae>
		if (fabs(a[i][i])<eps)
  ff:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 102:	48 98                	cdqe   
 104:	48 6b c0 68          	imul   rax,rax,0x68
 108:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 10c:	48 01 c2             	add    rdx,rax
 10f:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 112:	48 98                	cdqe   
 114:	f2 0f 10 04 c2       	movsd  xmm0,QWORD PTR [rdx+rax*8]
 119:	f3 0f 7e 0d c0 00 00 	movq   xmm1,QWORD PTR [rip+0xc0]        # 1e1 <_Z5GaussPA13_di+0x1e1>
 120:	00 
 121:	66 0f 54 c8          	andpd  xmm1,xmm0
 125:	f2 0f 10 05 d0 00 00 	movsd  xmm0,QWORD PTR [rip+0xd0]        # 1fd <_Z5GaussPA13_di+0x1fd>
 12c:	00 
 12d:	66 0f 2f c1          	comisd xmm0,xmm1
 131:	76 0a                	jbe    13d <_Z5GaussPA13_di+0x13d>
			return 0;
 133:	b8 00 00 00 00       	mov    eax,0x0
 138:	e9 51 01 00 00       	jmp    28e <_Z5GaussPA13_di+0x28e>
		for (int j=1;j<=n;j++)
 13d:	c7 45 ec 01 00 00 00 	mov    DWORD PTR [rbp-0x14],0x1
 144:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
 147:	3b 45 18             	cmp    eax,DWORD PTR [rbp+0x18]
 14a:	0f 8f c3 00 00 00    	jg     213 <_Z5GaussPA13_di+0x213>
		{
			if (i==j)
 150:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 153:	3b 45 ec             	cmp    eax,DWORD PTR [rbp-0x14]
 156:	0f 84 ad 00 00 00    	je     209 <_Z5GaussPA13_di+0x209>
				continue;
			for (int k=1;k<=n+1;k++)
 15c:	c7 45 e8 01 00 00 00 	mov    DWORD PTR [rbp-0x18],0x1
 163:	8b 45 18             	mov    eax,DWORD PTR [rbp+0x18]
 166:	83 c0 01             	add    eax,0x1
 169:	39 45 e8             	cmp    DWORD PTR [rbp-0x18],eax
 16c:	0f 8f 98 00 00 00    	jg     20a <_Z5GaussPA13_di+0x20a>
				a[j][k]-=a[i][k]*a[j][i]/a[i][i];
 172:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
 175:	48 98                	cdqe   
 177:	48 6b c0 68          	imul   rax,rax,0x68
 17b:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 17f:	48 01 c2             	add    rdx,rax
 182:	8b 45 e8             	mov    eax,DWORD PTR [rbp-0x18]
 185:	48 98                	cdqe   
 187:	f2 0f 10 04 c2       	movsd  xmm0,QWORD PTR [rdx+rax*8]
 18c:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 18f:	48 98                	cdqe   
 191:	48 6b c0 68          	imul   rax,rax,0x68
 195:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 199:	48 01 c2             	add    rdx,rax
 19c:	8b 45 e8             	mov    eax,DWORD PTR [rbp-0x18]
 19f:	48 98                	cdqe   
 1a1:	f2 0f 10 14 c2       	movsd  xmm2,QWORD PTR [rdx+rax*8]
 1a6:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
 1a9:	48 98                	cdqe   
 1ab:	48 6b c0 68          	imul   rax,rax,0x68
 1af:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 1b3:	48 01 c2             	add    rdx,rax
 1b6:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 1b9:	48 98                	cdqe   
 1bb:	f2 0f 10 0c c2       	movsd  xmm1,QWORD PTR [rdx+rax*8]
 1c0:	f2 0f 59 ca          	mulsd  xmm1,xmm2
 1c4:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 1c7:	48 98                	cdqe   
 1c9:	48 6b c0 68          	imul   rax,rax,0x68
 1cd:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 1d1:	48 01 c2             	add    rdx,rax
 1d4:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 1d7:	48 98                	cdqe   
 1d9:	f2 0f 10 14 c2       	movsd  xmm2,QWORD PTR [rdx+rax*8]
 1de:	f2 0f 5e ca          	divsd  xmm1,xmm2
 1e2:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
 1e5:	48 98                	cdqe   
 1e7:	48 6b c0 68          	imul   rax,rax,0x68
 1eb:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 1ef:	48 01 c2             	add    rdx,rax
 1f2:	f2 0f 5c c1          	subsd  xmm0,xmm1
 1f6:	8b 45 e8             	mov    eax,DWORD PTR [rbp-0x18]
 1f9:	48 98                	cdqe   
 1fb:	f2 0f 11 04 c2       	movsd  QWORD PTR [rdx+rax*8],xmm0
			for (int k=1;k<=n+1;k++)
 200:	83 45 e8 01          	add    DWORD PTR [rbp-0x18],0x1
 204:	e9 5a ff ff ff       	jmp    163 <_Z5GaussPA13_di+0x163>
				continue;
 209:	90                   	nop
		for (int j=1;j<=n;j++)
 20a:	83 45 ec 01          	add    DWORD PTR [rbp-0x14],0x1
 20e:	e9 31 ff ff ff       	jmp    144 <_Z5GaussPA13_di+0x144>
	for (int i=1;i<=n;i++)
 213:	83 45 f8 01          	add    DWORD PTR [rbp-0x8],0x1
 217:	e9 fa fd ff ff       	jmp    16 <_Z5GaussPA13_di+0x16>
		}
	}
	for (int i=1;i<=n;i++)
 21c:	c7 45 e4 01 00 00 00 	mov    DWORD PTR [rbp-0x1c],0x1
 223:	8b 45 e4             	mov    eax,DWORD PTR [rbp-0x1c]
 226:	3b 45 18             	cmp    eax,DWORD PTR [rbp+0x18]
 229:	7f 5e                	jg     289 <_Z5GaussPA13_di+0x289>
		a[i][n+1]/=a[i][i];
 22b:	8b 45 e4             	mov    eax,DWORD PTR [rbp-0x1c]
 22e:	48 98                	cdqe   
 230:	48 6b c0 68          	imul   rax,rax,0x68
 234:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 238:	48 01 c2             	add    rdx,rax
 23b:	8b 45 18             	mov    eax,DWORD PTR [rbp+0x18]
 23e:	83 c0 01             	add    eax,0x1
 241:	48 98                	cdqe   
 243:	f2 0f 10 04 c2       	movsd  xmm0,QWORD PTR [rdx+rax*8]
 248:	8b 45 e4             	mov    eax,DWORD PTR [rbp-0x1c]
 24b:	48 98                	cdqe   
 24d:	48 6b c0 68          	imul   rax,rax,0x68
 251:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 255:	48 01 c2             	add    rdx,rax
 258:	8b 45 e4             	mov    eax,DWORD PTR [rbp-0x1c]
 25b:	48 98                	cdqe   
 25d:	f2 0f 10 0c c2       	movsd  xmm1,QWORD PTR [rdx+rax*8]
 262:	8b 45 e4             	mov    eax,DWORD PTR [rbp-0x1c]
 265:	48 98                	cdqe   
 267:	48 6b c0 68          	imul   rax,rax,0x68
 26b:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
 26f:	48 01 c2             	add    rdx,rax
 272:	8b 45 18             	mov    eax,DWORD PTR [rbp+0x18]
 275:	83 c0 01             	add    eax,0x1
 278:	f2 0f 5e c1          	divsd  xmm0,xmm1
 27c:	48 98                	cdqe   
 27e:	f2 0f 11 04 c2       	movsd  QWORD PTR [rdx+rax*8],xmm0
	for (int i=1;i<=n;i++)
 283:	83 45 e4 01          	add    DWORD PTR [rbp-0x1c],0x1
 287:	eb 9a                	jmp    223 <_Z5GaussPA13_di+0x223>
	return 1;
 289:	b8 01 00 00 00       	mov    eax,0x1
}
 28e:	48 83 c4 40          	add    rsp,0x40
 292:	5d                   	pop    rbp
 293:	c3                   	ret    

0000000000000294 <main>:

int main()
{
 294:	55                   	push   rbp
 295:	48 89 e5             	mov    rbp,rsp
 298:	48 83 ec 40          	sub    rsp,0x40
 29c:	e8 00 00 00 00       	call   2a1 <main+0xd>
//	freopen("P4035.in","r",stdin);
//	freopen("P4035.out","w",stdout);
	scanf("%d",&n);
 2a1:	48 8d 15 a8 0a 00 00 	lea    rdx,[rip+0xaa8]        # d50 <_ZStL8__ioinit+0x2a4>
 2a8:	48 8d 0d b0 00 00 00 	lea    rcx,[rip+0xb0]        # 35f <main+0xcb>
 2af:	e8 00 00 00 00       	call   2b4 <main+0x20>
	for (int i=1;i<=n+1;i++)
 2b4:	c7 45 fc 01 00 00 00 	mov    DWORD PTR [rbp-0x4],0x1
 2bb:	8b 05 a8 0a 00 00    	mov    eax,DWORD PTR [rip+0xaa8]        # d69 <_ZStL8__ioinit+0x2bd>
 2c1:	83 c0 01             	add    eax,0x1
 2c4:	39 45 fc             	cmp    DWORD PTR [rbp-0x4],eax
 2c7:	7f 5e                	jg     327 <main+0x93>
		for (int j=1;j<=n;j++)
 2c9:	c7 45 f8 01 00 00 00 	mov    DWORD PTR [rbp-0x8],0x1
 2d0:	8b 05 a8 0a 00 00    	mov    eax,DWORD PTR [rip+0xaa8]        # d7e <_ZStL8__ioinit+0x2d2>
 2d6:	39 45 f8             	cmp    DWORD PTR [rbp-0x8],eax
 2d9:	7f 46                	jg     321 <main+0x8d>
			scanf("%lf",&a[i][j]);
 2db:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
 2de:	48 63 c8             	movsxd rcx,eax
 2e1:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
 2e4:	48 63 d0             	movsxd rdx,eax
 2e7:	48 89 d0             	mov    rax,rdx
 2ea:	48 01 c0             	add    rax,rax
 2ed:	48 01 d0             	add    rax,rdx
 2f0:	48 c1 e0 02          	shl    rax,0x2
 2f4:	48 01 d0             	add    rax,rdx
 2f7:	48 01 c8             	add    rax,rcx
 2fa:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 301:	00 
 302:	48 8d 05 00 00 00 00 	lea    rax,[rip+0x0]        # 309 <main+0x75>
 309:	48 01 d0             	add    rax,rdx
 30c:	48 89 c2             	mov    rdx,rax
 30f:	48 8d 0d b3 00 00 00 	lea    rcx,[rip+0xb3]        # 3c9 <main+0x135>
 316:	e8 00 00 00 00       	call   31b <main+0x87>
		for (int j=1;j<=n;j++)
 31b:	83 45 f8 01          	add    DWORD PTR [rbp-0x8],0x1
 31f:	eb af                	jmp    2d0 <main+0x3c>
	for (int i=1;i<=n+1;i++)
 321:	83 45 fc 01          	add    DWORD PTR [rbp-0x4],0x1
 325:	eb 94                	jmp    2bb <main+0x27>
	for (int i=2;i<=n+1;i++)
 327:	c7 45 f4 02 00 00 00 	mov    DWORD PTR [rbp-0xc],0x2
 32e:	8b 05 a8 0a 00 00    	mov    eax,DWORD PTR [rip+0xaa8]        # ddc <_ZStL8__ioinit+0x330>
 334:	83 c0 01             	add    eax,0x1
 337:	39 45 f4             	cmp    DWORD PTR [rbp-0xc],eax
 33a:	0f 8f 29 02 00 00    	jg     569 <main+0x2d5>
		for (int j=1;j<=n;j++)
 340:	c7 45 f0 01 00 00 00 	mov    DWORD PTR [rbp-0x10],0x1
 347:	8b 05 a8 0a 00 00    	mov    eax,DWORD PTR [rip+0xaa8]        # df5 <_ZStL8__ioinit+0x349>
 34d:	39 45 f0             	cmp    DWORD PTR [rbp-0x10],eax
 350:	0f 8f 0a 02 00 00    	jg     560 <main+0x2cc>
		{
			f[i-1][j]=2*(a[i][j]-a[i-1][j]);
 356:	8b 45 f0             	mov    eax,DWORD PTR [rbp-0x10]
 359:	48 63 c8             	movsxd rcx,eax
 35c:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 35f:	48 63 d0             	movsxd rdx,eax
 362:	48 89 d0             	mov    rax,rdx
 365:	48 01 c0             	add    rax,rax
 368:	48 01 d0             	add    rax,rdx
 36b:	48 c1 e0 02          	shl    rax,0x2
 36f:	48 01 d0             	add    rax,rdx
 372:	48 01 c8             	add    rax,rcx
 375:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 37c:	00 
 37d:	48 8d 05 00 00 00 00 	lea    rax,[rip+0x0]        # 384 <main+0xf0>
 384:	f2 0f 10 04 02       	movsd  xmm0,QWORD PTR [rdx+rax*1]
 389:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 38c:	83 e8 01             	sub    eax,0x1
 38f:	8b 55 f0             	mov    edx,DWORD PTR [rbp-0x10]
 392:	48 63 ca             	movsxd rcx,edx
 395:	48 63 d0             	movsxd rdx,eax
 398:	48 89 d0             	mov    rax,rdx
 39b:	48 01 c0             	add    rax,rax
 39e:	48 01 d0             	add    rax,rdx
 3a1:	48 c1 e0 02          	shl    rax,0x2
 3a5:	48 01 d0             	add    rax,rdx
 3a8:	48 01 c8             	add    rax,rcx
 3ab:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 3b2:	00 
 3b3:	48 8d 05 00 00 00 00 	lea    rax,[rip+0x0]        # 3ba <main+0x126>
 3ba:	f2 0f 10 0c 02       	movsd  xmm1,QWORD PTR [rdx+rax*1]
 3bf:	f2 0f 5c c1          	subsd  xmm0,xmm1
 3c3:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 3c6:	83 e8 01             	sub    eax,0x1
 3c9:	f2 0f 58 c0          	addsd  xmm0,xmm0
 3cd:	8b 55 f0             	mov    edx,DWORD PTR [rbp-0x10]
 3d0:	48 63 ca             	movsxd rcx,edx
 3d3:	48 63 d0             	movsxd rdx,eax
 3d6:	48 89 d0             	mov    rax,rdx
 3d9:	48 01 c0             	add    rax,rax
 3dc:	48 01 d0             	add    rax,rdx
 3df:	48 c1 e0 02          	shl    rax,0x2
 3e3:	48 01 d0             	add    rax,rdx
 3e6:	48 01 c8             	add    rax,rcx
 3e9:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 3f0:	00 
 3f1:	48 8d 05 60 05 00 00 	lea    rax,[rip+0x560]        # 958 <_GLOBAL__sub_I_a+0x30c>
 3f8:	f2 0f 11 04 02       	movsd  QWORD PTR [rdx+rax*1],xmm0
			f[i-1][n+1]+=(a[i][j]*a[i][j]-a[i-1][j]*a[i-1][j]);
 3fd:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 400:	83 e8 01             	sub    eax,0x1
 403:	8b 15 a8 0a 00 00    	mov    edx,DWORD PTR [rip+0xaa8]        # eb1 <_ZStL8__ioinit+0x405>
 409:	83 c2 01             	add    edx,0x1
 40c:	48 63 ca             	movsxd rcx,edx
 40f:	48 63 d0             	movsxd rdx,eax
 412:	48 89 d0             	mov    rax,rdx
 415:	48 01 c0             	add    rax,rax
 418:	48 01 d0             	add    rax,rdx
 41b:	48 c1 e0 02          	shl    rax,0x2
 41f:	48 01 d0             	add    rax,rdx
 422:	48 01 c8             	add    rax,rcx
 425:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 42c:	00 
 42d:	48 8d 05 60 05 00 00 	lea    rax,[rip+0x560]        # 994 <_GLOBAL__sub_I_a+0x348>
 434:	f2 0f 10 0c 02       	movsd  xmm1,QWORD PTR [rdx+rax*1]
 439:	8b 45 f0             	mov    eax,DWORD PTR [rbp-0x10]
 43c:	48 63 c8             	movsxd rcx,eax
 43f:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 442:	48 63 d0             	movsxd rdx,eax
 445:	48 89 d0             	mov    rax,rdx
 448:	48 01 c0             	add    rax,rax
 44b:	48 01 d0             	add    rax,rdx
 44e:	48 c1 e0 02          	shl    rax,0x2
 452:	48 01 d0             	add    rax,rdx
 455:	48 01 c8             	add    rax,rcx
 458:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 45f:	00 
 460:	48 8d 05 00 00 00 00 	lea    rax,[rip+0x0]        # 467 <main+0x1d3>
 467:	f2 0f 10 14 02       	movsd  xmm2,QWORD PTR [rdx+rax*1]
 46c:	8b 45 f0             	mov    eax,DWORD PTR [rbp-0x10]
 46f:	48 63 c8             	movsxd rcx,eax
 472:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 475:	48 63 d0             	movsxd rdx,eax
 478:	48 89 d0             	mov    rax,rdx
 47b:	48 01 c0             	add    rax,rax
 47e:	48 01 d0             	add    rax,rdx
 481:	48 c1 e0 02          	shl    rax,0x2
 485:	48 01 d0             	add    rax,rdx
 488:	48 01 c8             	add    rax,rcx
 48b:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 492:	00 
 493:	48 8d 05 00 00 00 00 	lea    rax,[rip+0x0]        # 49a <main+0x206>
 49a:	f2 0f 10 04 02       	movsd  xmm0,QWORD PTR [rdx+rax*1]
 49f:	f2 0f 59 c2          	mulsd  xmm0,xmm2
 4a3:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 4a6:	83 e8 01             	sub    eax,0x1
 4a9:	8b 55 f0             	mov    edx,DWORD PTR [rbp-0x10]
 4ac:	48 63 ca             	movsxd rcx,edx
 4af:	48 63 d0             	movsxd rdx,eax
 4b2:	48 89 d0             	mov    rax,rdx
 4b5:	48 01 c0             	add    rax,rax
 4b8:	48 01 d0             	add    rax,rdx
 4bb:	48 c1 e0 02          	shl    rax,0x2
 4bf:	48 01 d0             	add    rax,rdx
 4c2:	48 01 c8             	add    rax,rcx
 4c5:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 4cc:	00 
 4cd:	48 8d 05 00 00 00 00 	lea    rax,[rip+0x0]        # 4d4 <main+0x240>
 4d4:	f2 0f 10 1c 02       	movsd  xmm3,QWORD PTR [rdx+rax*1]
 4d9:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 4dc:	83 e8 01             	sub    eax,0x1
 4df:	8b 55 f0             	mov    edx,DWORD PTR [rbp-0x10]
 4e2:	48 63 ca             	movsxd rcx,edx
 4e5:	48 63 d0             	movsxd rdx,eax
 4e8:	48 89 d0             	mov    rax,rdx
 4eb:	48 01 c0             	add    rax,rax
 4ee:	48 01 d0             	add    rax,rdx
 4f1:	48 c1 e0 02          	shl    rax,0x2
 4f5:	48 01 d0             	add    rax,rdx
 4f8:	48 01 c8             	add    rax,rcx
 4fb:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 502:	00 
 503:	48 8d 05 00 00 00 00 	lea    rax,[rip+0x0]        # 50a <main+0x276>
 50a:	f2 0f 10 14 02       	movsd  xmm2,QWORD PTR [rdx+rax*1]
 50f:	f2 0f 59 d3          	mulsd  xmm2,xmm3
 513:	f2 0f 5c c2          	subsd  xmm0,xmm2
 517:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
 51a:	83 e8 01             	sub    eax,0x1
 51d:	8b 15 a8 0a 00 00    	mov    edx,DWORD PTR [rip+0xaa8]        # fcb <_ZStL8__ioinit+0x51f>
 523:	83 c2 01             	add    edx,0x1
 526:	f2 0f 58 c1          	addsd  xmm0,xmm1
 52a:	48 63 ca             	movsxd rcx,edx
 52d:	48 63 d0             	movsxd rdx,eax
 530:	48 89 d0             	mov    rax,rdx
 533:	48 01 c0             	add    rax,rax
 536:	48 01 d0             	add    rax,rdx
 539:	48 c1 e0 02          	shl    rax,0x2
 53d:	48 01 d0             	add    rax,rdx
 540:	48 01 c8             	add    rax,rcx
 543:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 54a:	00 
 54b:	48 8d 05 60 05 00 00 	lea    rax,[rip+0x560]        # ab2 <_ZStL8__ioinit+0x6>
 552:	f2 0f 11 04 02       	movsd  QWORD PTR [rdx+rax*1],xmm0
		for (int j=1;j<=n;j++)
 557:	83 45 f0 01          	add    DWORD PTR [rbp-0x10],0x1
 55b:	e9 e7 fd ff ff       	jmp    347 <main+0xb3>
	for (int i=2;i<=n+1;i++)
 560:	83 45 f4 01          	add    DWORD PTR [rbp-0xc],0x1
 564:	e9 c5 fd ff ff       	jmp    32e <main+0x9a>
		}
	Gauss(f,n);
 569:	8b 05 a8 0a 00 00    	mov    eax,DWORD PTR [rip+0xaa8]        # 1017 <_ZStL8__ioinit+0x56b>
 56f:	89 c2                	mov    edx,eax
 571:	48 8d 0d 60 05 00 00 	lea    rcx,[rip+0x560]        # ad8 <_ZStL8__ioinit+0x2c>
 578:	e8 83 fa ff ff       	call   0 <_Z5GaussPA13_di>
	for (int i=1;i<=n;i++)
 57d:	c7 45 ec 01 00 00 00 	mov    DWORD PTR [rbp-0x14],0x1
 584:	8b 05 a8 0a 00 00    	mov    eax,DWORD PTR [rip+0xaa8]        # 1032 <_ZStL8__ioinit+0x586>
 58a:	39 45 ec             	cmp    DWORD PTR [rbp-0x14],eax
 58d:	7f 5b                	jg     5ea <main+0x356>
		printf("%.3lf ",f[i][n+1]);
 58f:	8b 05 a8 0a 00 00    	mov    eax,DWORD PTR [rip+0xaa8]        # 103d <_ZStL8__ioinit+0x591>
 595:	83 c0 01             	add    eax,0x1
 598:	48 63 c8             	movsxd rcx,eax
 59b:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
 59e:	48 63 d0             	movsxd rdx,eax
 5a1:	48 89 d0             	mov    rax,rdx
 5a4:	48 01 c0             	add    rax,rax
 5a7:	48 01 d0             	add    rax,rdx
 5aa:	48 c1 e0 02          	shl    rax,0x2
 5ae:	48 01 d0             	add    rax,rdx
 5b1:	48 01 c8             	add    rax,rcx
 5b4:	48 8d 14 c5 00 00 00 	lea    rdx,[rax*8+0x0]
 5bb:	00 
 5bc:	48 8d 05 60 05 00 00 	lea    rax,[rip+0x560]        # b23 <_ZStL8__ioinit+0x77>
 5c3:	f2 0f 10 04 02       	movsd  xmm0,QWORD PTR [rdx+rax*1]
 5c8:	66 48 0f 7e c0       	movq   rax,xmm0
 5cd:	48 89 c2             	mov    rdx,rax
 5d0:	66 48 0f 6e ca       	movq   xmm1,rdx
 5d5:	48 89 c2             	mov    rdx,rax
 5d8:	48 8d 0d b7 00 00 00 	lea    rcx,[rip+0xb7]        # 696 <_GLOBAL__sub_I_a+0x4a>
 5df:	e8 00 00 00 00       	call   5e4 <main+0x350>
	for (int i=1;i<=n;i++)
 5e4:	83 45 ec 01          	add    DWORD PTR [rbp-0x14],0x1
 5e8:	eb 9a                	jmp    584 <main+0x2f0>
	return 0;
 5ea:	b8 00 00 00 00       	mov    eax,0x0
 5ef:	48 83 c4 40          	add    rsp,0x40
 5f3:	5d                   	pop    rbp
 5f4:	c3                   	ret    

00000000000005f5 <__tcf_0>:
  extern wostream wclog;	/// Linked to standard error (buffered)
#endif
  //@}

  // For construction of filebuffers for cout, cin, cerr, clog et. al.
  static ios_base::Init __ioinit;
 5f5:	55                   	push   rbp
 5f6:	48 89 e5             	mov    rbp,rsp
 5f9:	48 83 ec 20          	sub    rsp,0x20
 5fd:	48 8d 0d ac 0a 00 00 	lea    rcx,[rip+0xaac]        # 10b0 <_ZStL8__ioinit+0x604>
 604:	e8 00 00 00 00       	call   609 <__tcf_0+0x14>
 609:	90                   	nop
 60a:	48 83 c4 20          	add    rsp,0x20
 60e:	5d                   	pop    rbp
 60f:	c3                   	ret    

0000000000000610 <_Z41__static_initialization_and_destruction_0ii>:
 610:	55                   	push   rbp
 611:	48 89 e5             	mov    rbp,rsp
 614:	48 83 ec 20          	sub    rsp,0x20
 618:	89 4d 10             	mov    DWORD PTR [rbp+0x10],ecx
 61b:	89 55 18             	mov    DWORD PTR [rbp+0x18],edx
 61e:	83 7d 10 01          	cmp    DWORD PTR [rbp+0x10],0x1
 622:	75 21                	jne    645 <_Z41__static_initialization_and_destruction_0ii+0x35>
 624:	81 7d 18 ff ff 00 00 	cmp    DWORD PTR [rbp+0x18],0xffff
 62b:	75 18                	jne    645 <_Z41__static_initialization_and_destruction_0ii+0x35>
 62d:	48 8d 0d ac 0a 00 00 	lea    rcx,[rip+0xaac]        # 10e0 <_ZStL8__ioinit+0x634>
 634:	e8 00 00 00 00       	call   639 <_Z41__static_initialization_and_destruction_0ii+0x29>
 639:	48 8d 0d b5 ff ff ff 	lea    rcx,[rip+0xffffffffffffffb5]        # 5f5 <__tcf_0>
 640:	e8 00 00 00 00       	call   645 <_Z41__static_initialization_and_destruction_0ii+0x35>
 645:	90                   	nop
 646:	48 83 c4 20          	add    rsp,0x20
 64a:	5d                   	pop    rbp
 64b:	c3                   	ret    

000000000000064c <_GLOBAL__sub_I_a>:
 64c:	55                   	push   rbp
 64d:	48 89 e5             	mov    rbp,rsp
 650:	48 83 ec 20          	sub    rsp,0x20
 654:	ba ff ff 00 00       	mov    edx,0xffff
 659:	b9 01 00 00 00       	mov    ecx,0x1
 65e:	e8 ad ff ff ff       	call   610 <_Z41__static_initialization_and_destruction_0ii>
 663:	90                   	nop
 664:	48 83 c4 20          	add    rsp,0x20
 668:	5d                   	pop    rbp
 669:	c3                   	ret    
 66a:	90                   	nop
 66b:	90                   	nop
 66c:	90                   	nop
 66d:	90                   	nop
 66e:	90                   	nop
 66f:	90                   	nop

Disassembly of section .text$_Z5scanfPKcz:

0000000000000000 <_Z5scanfPKcz>:
}

__mingw_ovr
__attribute__((__format__ (gnu_scanf, 1, 2))) __MINGW_ATTRIB_NONNULL(1)
int scanf(const char *__format, ...)
{
   0:	55                   	push   rbp
   1:	53                   	push   rbx
   2:	48 83 ec 38          	sub    rsp,0x38
   6:	48 8d ac 24 80 00 00 	lea    rbp,[rsp+0x80]
   d:	00 
   e:	48 89 4d d0          	mov    QWORD PTR [rbp-0x30],rcx
  12:	48 89 55 d8          	mov    QWORD PTR [rbp-0x28],rdx
  16:	4c 89 45 e0          	mov    QWORD PTR [rbp-0x20],r8
  1a:	4c 89 4d e8          	mov    QWORD PTR [rbp-0x18],r9
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  1e:	48 8d 45 d8          	lea    rax,[rbp-0x28]
  22:	48 89 45 a0          	mov    QWORD PTR [rbp-0x60],rax
  __retval = __mingw_vfscanf( stdin, __format, __local_argv );
  26:	48 8b 5d a0          	mov    rbx,QWORD PTR [rbp-0x60]
  2a:	b9 00 00 00 00       	mov    ecx,0x0
  2f:	48 8b 05 00 00 00 00 	mov    rax,QWORD PTR [rip+0x0]        # 36 <_Z5scanfPKcz+0x36>
  36:	ff d0                	call   rax
  38:	49 89 d8             	mov    r8,rbx
  3b:	48 8b 55 d0          	mov    rdx,QWORD PTR [rbp-0x30]
  3f:	48 89 c1             	mov    rcx,rax
  42:	e8 00 00 00 00       	call   47 <_Z5scanfPKcz+0x47>
  47:	89 45 ac             	mov    DWORD PTR [rbp-0x54],eax
  __builtin_va_end( __local_argv );
  return __retval;
  4a:	8b 45 ac             	mov    eax,DWORD PTR [rbp-0x54]
}
  4d:	48 83 c4 38          	add    rsp,0x38
  51:	5b                   	pop    rbx
  52:	5d                   	pop    rbp
  53:	c3                   	ret    
  54:	90                   	nop
  55:	90                   	nop
  56:	90                   	nop
  57:	90                   	nop
  58:	90                   	nop
  59:	90                   	nop
  5a:	90                   	nop
  5b:	90                   	nop
  5c:	90                   	nop
  5d:	90                   	nop
  5e:	90                   	nop
  5f:	90                   	nop

Disassembly of section .text$_Z6printfPKcz:

0000000000000000 <_Z6printfPKcz>:
}

__mingw_ovr
__attribute__((__format__ (gnu_printf, 1, 2))) __MINGW_ATTRIB_NONNULL(1)
int printf (const char *__format, ...)
{
   0:	55                   	push   rbp
   1:	53                   	push   rbx
   2:	48 83 ec 38          	sub    rsp,0x38
   6:	48 8d ac 24 80 00 00 	lea    rbp,[rsp+0x80]
   d:	00 
   e:	48 89 4d d0          	mov    QWORD PTR [rbp-0x30],rcx
  12:	48 89 55 d8          	mov    QWORD PTR [rbp-0x28],rdx
  16:	4c 89 45 e0          	mov    QWORD PTR [rbp-0x20],r8
  1a:	4c 89 4d e8          	mov    QWORD PTR [rbp-0x18],r9
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  1e:	48 8d 45 d8          	lea    rax,[rbp-0x28]
  22:	48 89 45 a0          	mov    QWORD PTR [rbp-0x60],rax
  __retval = __mingw_vfprintf( stdout, __format, __local_argv );
  26:	48 8b 5d a0          	mov    rbx,QWORD PTR [rbp-0x60]
  2a:	b9 01 00 00 00       	mov    ecx,0x1
  2f:	48 8b 05 00 00 00 00 	mov    rax,QWORD PTR [rip+0x0]        # 36 <_Z6printfPKcz+0x36>
  36:	ff d0                	call   rax
  38:	49 89 d8             	mov    r8,rbx
  3b:	48 8b 55 d0          	mov    rdx,QWORD PTR [rbp-0x30]
  3f:	48 89 c1             	mov    rcx,rax
  42:	e8 00 00 00 00       	call   47 <_Z6printfPKcz+0x47>
  47:	89 45 ac             	mov    DWORD PTR [rbp-0x54],eax
  __builtin_va_end( __local_argv );
  return __retval;
  4a:	8b 45 ac             	mov    eax,DWORD PTR [rbp-0x54]
}
  4d:	48 83 c4 38          	add    rsp,0x38
  51:	5b                   	pop    rbx
  52:	5d                   	pop    rbp
  53:	c3                   	ret    
  54:	90                   	nop
  55:	90                   	nop
  56:	90                   	nop
  57:	90                   	nop
  58:	90                   	nop
  59:	90                   	nop
  5a:	90                   	nop
  5b:	90                   	nop
  5c:	90                   	nop
  5d:	90                   	nop
  5e:	90                   	nop
  5f:	90                   	nop

Disassembly of section .text$_ZSt4moveIRdEONSt16remove_referenceIT_E4typeEOS2_:

0000000000000000 <_ZSt4moveIRdEONSt16remove_referenceIT_E4typeEOS2_>:
   *  @param  __t  A thing of arbitrary type.
   *  @return The parameter cast to an rvalue-reference to allow moving it.
  */
  template<typename _Tp>
    constexpr typename std::remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	48 89 4d 10          	mov    QWORD PTR [rbp+0x10],rcx
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
   8:	48 8b 45 10          	mov    rax,QWORD PTR [rbp+0x10]
   c:	5d                   	pop    rbp
   d:	c3                   	ret    
   e:	90                   	nop
   f:	90                   	nop

Disassembly of section .text$_ZSt4swapIdENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_:

0000000000000000 <_ZSt4swapIdENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_>:
    inline
#if __cplusplus >= 201103L
    typename enable_if<__and_<__not_<__is_tuple_like<_Tp>>,
			      is_move_constructible<_Tp>,
			      is_move_assignable<_Tp>>::value>::type
    swap(_Tp& __a, _Tp& __b)
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	48 83 ec 30          	sub    rsp,0x30
   8:	48 89 4d 10          	mov    QWORD PTR [rbp+0x10],rcx
   c:	48 89 55 18          	mov    QWORD PTR [rbp+0x18],rdx
#endif
    {
      // concept requirements
      __glibcxx_function_requires(_SGIAssignableConcept<_Tp>)

      _Tp __tmp = _GLIBCXX_MOVE(__a);
  10:	48 8b 4d 10          	mov    rcx,QWORD PTR [rbp+0x10]
  14:	e8 00 00 00 00       	call   19 <_ZSt4swapIdENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_+0x19>
  19:	f2 0f 10 00          	movsd  xmm0,QWORD PTR [rax]
  1d:	f2 0f 11 45 f8       	movsd  QWORD PTR [rbp-0x8],xmm0
      __a = _GLIBCXX_MOVE(__b);
  22:	48 8b 45 18          	mov    rax,QWORD PTR [rbp+0x18]
  26:	48 89 c1             	mov    rcx,rax
  29:	e8 00 00 00 00       	call   2e <_ZSt4swapIdENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_+0x2e>
  2e:	f2 0f 10 00          	movsd  xmm0,QWORD PTR [rax]
  32:	48 8b 45 10          	mov    rax,QWORD PTR [rbp+0x10]
  36:	f2 0f 11 00          	movsd  QWORD PTR [rax],xmm0
      __b = _GLIBCXX_MOVE(__tmp);
  3a:	48 8d 45 f8          	lea    rax,[rbp-0x8]
  3e:	48 89 c1             	mov    rcx,rax
  41:	e8 00 00 00 00       	call   46 <_ZSt4swapIdENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_+0x46>
  46:	f2 0f 10 00          	movsd  xmm0,QWORD PTR [rax]
  4a:	48 8b 45 18          	mov    rax,QWORD PTR [rbp+0x18]
  4e:	f2 0f 11 00          	movsd  QWORD PTR [rax],xmm0
    }
  52:	90                   	nop
  53:	48 83 c4 30          	add    rsp,0x30
  57:	5d                   	pop    rbp
  58:	c3                   	ret    
  59:	90                   	nop
  5a:	90                   	nop
  5b:	90                   	nop
  5c:	90                   	nop
  5d:	90                   	nop
  5e:	90                   	nop
  5f:	90                   	nop
