	.file	"P2221.cpp"
	.text
	.section	.text$_Z6printfPKcz,"x"
	.linkonce discard
	.globl	_Z6printfPKcz
	.def	_Z6printfPKcz;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6printfPKcz
_Z6printfPKcz:
.LFB27:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%r8, -32(%rbp)
	movq	%r9, -24(%rbp)
	leaq	-40(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rbx
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rbx, %r8
	movq	-48(%rbp), %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	movl	%eax, -84(%rbp)
	movl	-84(%rbp), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
_ZStL19piecewise_construct:
	.space 1
_ZStL13allocator_arg:
	.space 1
_ZStL6ignore:
	.space 1
.lcomm _ZStL8__ioinit,1,1
	.align 4
_ZN9__gnu_cxxL21__default_lock_policyE:
	.long	2
_ZStL10defer_lock:
	.space 1
_ZStL11try_to_lock:
	.space 1
_ZStL10adopt_lock:
	.space 1
	.align 4
_ZNSt15regex_constantsL5icaseE:
	.long	1
	.align 4
_ZNSt15regex_constantsL6nosubsE:
	.long	2
	.align 4
_ZNSt15regex_constantsL8optimizeE:
	.long	4
	.align 4
_ZNSt15regex_constantsL7collateE:
	.long	8
	.align 4
_ZNSt15regex_constantsL10ECMAScriptE:
	.long	16
	.align 4
_ZNSt15regex_constantsL5basicE:
	.long	32
	.align 4
_ZNSt15regex_constantsL8extendedE:
	.long	64
	.align 4
_ZNSt15regex_constantsL3awkE:
	.long	128
	.align 4
_ZNSt15regex_constantsL4grepE:
	.long	256
	.align 4
_ZNSt15regex_constantsL5egrepE:
	.long	512
	.align 4
_ZNSt15regex_constantsL12__polynomialE:
	.long	1024
	.align 4
_ZNSt15regex_constantsL13match_defaultE:
	.space 4
	.align 4
_ZNSt15regex_constantsL13match_not_bolE:
	.long	1
	.align 4
_ZNSt15regex_constantsL13match_not_eolE:
	.long	2
	.align 4
_ZNSt15regex_constantsL13match_not_bowE:
	.long	4
	.align 4
_ZNSt15regex_constantsL13match_not_eowE:
	.long	8
	.align 4
_ZNSt15regex_constantsL9match_anyE:
	.long	16
	.align 4
_ZNSt15regex_constantsL14match_not_nullE:
	.long	32
	.align 4
_ZNSt15regex_constantsL16match_continuousE:
	.long	64
	.align 4
_ZNSt15regex_constantsL16match_prev_availE:
	.long	128
	.align 4
_ZNSt15regex_constantsL14format_defaultE:
	.space 4
	.align 4
_ZNSt15regex_constantsL10format_sedE:
	.long	256
	.align 4
_ZNSt15regex_constantsL14format_no_copyE:
	.long	512
	.align 4
_ZNSt15regex_constantsL17format_first_onlyE:
	.long	1024
	.align 4
_ZNSt15regex_constantsL13error_collateE:
	.space 4
	.align 4
_ZNSt15regex_constantsL11error_ctypeE:
	.long	1
	.align 4
_ZNSt15regex_constantsL12error_escapeE:
	.long	2
	.align 4
_ZNSt15regex_constantsL13error_backrefE:
	.long	3
	.align 4
_ZNSt15regex_constantsL11error_brackE:
	.long	4
	.align 4
_ZNSt15regex_constantsL11error_parenE:
	.long	5
	.align 4
_ZNSt15regex_constantsL11error_braceE:
	.long	6
	.align 4
_ZNSt15regex_constantsL14error_badbraceE:
	.long	7
	.align 4
_ZNSt15regex_constantsL11error_rangeE:
	.long	8
	.align 4
_ZNSt15regex_constantsL11error_spaceE:
	.long	9
	.align 4
_ZNSt15regex_constantsL15error_badrepeatE:
	.long	10
	.align 4
_ZNSt15regex_constantsL16error_complexityE:
	.long	11
	.align 4
_ZNSt15regex_constantsL11error_stackE:
	.long	12
	.align 4
_ZNSt8__detailL19_S_invalid_state_idE:
	.long	-1
	.align 4
_ZL4MAXN:
	.long	100009
	.section	.text$_ZN5TnodeC1Ev,"x"
	.linkonce discard
	.align 2
	.globl	_ZN5TnodeC1Ev
	.def	_ZN5TnodeC1Ev;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN5TnodeC1Ev
_ZN5TnodeC1Ev:
.LFB8812:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movl	$24, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	call	memset
	movq	16(%rbp), %rax
	movq	$0, 24(%rax)
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_ZN5TnodepLERKS_,"x"
	.linkonce discard
	.align 2
	.globl	_ZN5TnodepLERKS_
	.def	_ZN5TnodepLERKS_;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN5TnodepLERKS_
_ZN5TnodepLERKS_:
.LFB8813:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movl	$0, -4(%rbp)
.L6:
	cmpl	$2, -4(%rbp)
	jg	.L5
	movq	16(%rbp), %rdx
	movl	-4(%rbp), %eax
	cltq
	movq	(%rdx,%rax,8), %rcx
	movq	24(%rbp), %rdx
	movl	-4(%rbp), %eax
	cltq
	movq	(%rdx,%rax,8), %rax
	addq	%rax, %rcx
	movq	16(%rbp), %rdx
	movl	-4(%rbp), %eax
	cltq
	movq	%rcx, (%rdx,%rax,8)
	addl	$1, -4(%rbp)
	jmp	.L6
.L5:
	movq	16(%rbp), %rax
	movq	$0, 24(%rax)
	movq	16(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_Zpl5TnodeRKS_,"x"
	.linkonce discard
	.globl	_Zpl5TnodeRKS_
	.def	_Zpl5TnodeRKS_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Zpl5TnodeRKS_
_Zpl5TnodeRKS_:
.LFB8814:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -64(%rbp)
	movq	%rdx, %rbx
	movq	%r8, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdx
	movq	%rbx, %rcx
	call	_ZN5TnodepLERKS_
	movq	-64(%rbp), %rax
	movq	(%rbx), %rdx
	movq	%rdx, (%rax)
	movq	8(%rbx), %rdx
	movq	%rdx, 8(%rax)
	movq	16(%rbx), %rdx
	movq	%rdx, 16(%rax)
	movq	24(%rbx), %rdx
	movq	%rdx, 24(%rax)
	movq	-64(%rbp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.globl	t
	.bss
	.align 32
t:
	.space 12801152
	.globl	c
	.align 32
c:
	.space 2400216
	.globl	n
	.align 4
n:
	.space 4
	.globl	m
	.align 4
m:
	.space 4
	.section	.text$_Z4readv,"x"
	.linkonce discard
	.globl	_Z4readv
	.def	_Z4readv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z4readv
_Z4readv:
.LFB8815:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movb	$0, -1(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
.L12:
	movsbl	-1(%rbp), %eax
	subl	$48, %eax
	cmpl	$9, %eax
	jbe	.L11
	cmpb	$45, -1(%rbp)
	sete	%al
	movzbl	%al, %eax
	orl	%eax, -8(%rbp)
	call	getchar
	movb	%al, -1(%rbp)
	jmp	.L12
.L11:
	movsbl	-1(%rbp), %eax
	subl	$48, %eax
	cmpl	$9, %eax
	ja	.L13
	movl	$1, %eax
	jmp	.L14
.L13:
	movl	$0, %eax
.L14:
	testb	%al, %al
	je	.L15
	movl	-12(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %edx
	movsbl	-1(%rbp), %eax
	addl	%edx, %eax
	subl	$48, %eax
	movl	%eax, -12(%rbp)
	call	getchar
	movb	%al, -1(%rbp)
	jmp	.L11
.L15:
	cmpl	$0, -8(%rbp)
	je	.L16
	movl	-12(%rbp), %eax
	negl	%eax
	jmp	.L18
.L16:
	movl	-12(%rbp), %eax
.L18:
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_Z8_calcaddixii,"x"
	.linkonce discard
	.globl	_Z8_calcaddixii
	.def	_Z8_calcaddixii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8_calcaddixii
_Z8_calcaddixii:
.LFB8816:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movl	40(%rbp), %eax
	cltq
	movl	16(%rbp), %edx
	movslq	%edx, %rdx
	imulq	$100009, %rdx, %rdx
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	leaq	c(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	32(%rbp), %eax
	subl	$1, %eax
	cltq
	movl	16(%rbp), %edx
	movslq	%edx, %rdx
	imulq	$100009, %rdx, %rdx
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	leaq	c(%rip), %rax
	movq	(%rdx,%rax), %rax
	subq	%rax, %rcx
	movq	%rcx, %rax
	imulq	24(%rbp), %rax
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_Z3_upi,"x"
	.linkonce discard
	.globl	_Z3_upi
	.def	_Z3_upi;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z3_upi
_Z3_upi:
.LFB8817:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$96, %rsp
	.seh_stackalloc	96
	.seh_endprologue
	movl	%ecx, 32(%rbp)
	movl	32(%rbp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	t(%rip), %rax
	leaq	(%rdx,%rax), %r9
	movl	32(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	32(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rsi
	leaq	t(%rip), %rbx
	leaq	-32(%rbp), %rcx
	movslq	%edx, %rax
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	t(%rip), %rax
	movq	(%rdx,%rax), %r8
	movq	%r8, -64(%rbp)
	movq	8(%rdx,%rax), %r8
	movq	%r8, -56(%rbp)
	movq	16(%rdx,%rax), %r8
	movq	%r8, -48(%rbp)
	movq	24(%rdx,%rax), %rax
	movq	%rax, -40(%rbp)
	leaq	-64(%rbp), %rax
	movq	%r9, %r8
	movq	%rax, %rdx
	call	_Zpl5TnodeRKS_
	movq	-32(%rbp), %rax
	movq	%rax, (%rsi,%rbx)
	movq	-24(%rbp), %rax
	movq	%rax, 8(%rsi,%rbx)
	movq	-16(%rbp), %rax
	movq	%rax, 16(%rsi,%rbx)
	movq	-8(%rbp), %rax
	movq	%rax, 24(%rsi,%rbx)
	nop
	addq	$96, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rbp
	ret
	.seh_endproc
	.text
	.globl	_Z5_downiii
	.def	_Z5_downiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z5_downiii
_Z5_downiii:
.LFB8818:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	16(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	(%rdx,%rax), %rax
	testq	%rax, %rax
	je	.L27
	movl	24(%rbp), %edx
	movl	32(%rbp), %eax
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -8(%rbp)
	movl	16(%rbp), %eax
	addl	%eax, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	16(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	16(%rbp), %eax
	addl	%eax, %eax
	addq	%rdx, %rcx
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	16(%rbp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	16(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	16(%rbp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	addq	%rdx, %rcx
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	$0, -4(%rbp)
.L26:
	cmpl	$2, -4(%rbp)
	jg	.L25
	movl	16(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	-8(%rbp), %r8d
	movl	24(%rbp), %ecx
	movl	-4(%rbp), %eax
	movl	%r8d, %r9d
	movl	%ecx, %r8d
	movl	%eax, %ecx
	call	_Z8_calcaddixii
	movq	%rax, %rcx
	movl	16(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	leaq	t(%rip), %rax
	movq	(%rdx,%rax), %rax
	movl	16(%rbp), %edx
	addl	%edx, %edx
	addq	%rax, %rcx
	movl	-4(%rbp), %eax
	cltq
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	leaq	t(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	-8(%rbp), %eax
	leal	1(%rax), %ecx
	movl	16(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	32(%rbp), %r8d
	movl	-4(%rbp), %eax
	movl	%r8d, %r9d
	movl	%ecx, %r8d
	movl	%eax, %ecx
	call	_Z8_calcaddixii
	movq	%rax, %rcx
	movl	16(%rbp), %eax
	addl	%eax, %eax
	leal	1(%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	leaq	t(%rip), %rax
	movq	(%rdx,%rax), %rax
	movl	16(%rbp), %edx
	addl	%edx, %edx
	addl	$1, %edx
	addq	%rax, %rcx
	movl	-4(%rbp), %eax
	cltq
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	leaq	t(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	addl	$1, -4(%rbp)
	jmp	.L26
.L25:
	movl	16(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	$0, (%rdx,%rax)
	nop
	jmp	.L22
.L27:
	nop
.L22:
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z7_modifyiiiiii
	.def	_Z7_modifyiiiiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z7_modifyiiiiii
_Z7_modifyiiiiii:
.LFB8819:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movl	40(%rbp), %eax
	cmpl	24(%rbp), %eax
	jg	.L29
	movl	48(%rbp), %eax
	cmpl	32(%rbp), %eax
	jl	.L29
	movl	16(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	56(%rbp), %eax
	cltq
	leaq	(%rdx,%rax), %rcx
	movl	16(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+t(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	$0, -4(%rbp)
.L31:
	cmpl	$2, -4(%rbp)
	jg	.L35
	movl	56(%rbp), %eax
	cltq
	movl	32(%rbp), %r8d
	movl	24(%rbp), %edx
	movl	-4(%rbp), %ecx
	movl	%r8d, %r9d
	movl	%edx, %r8d
	movq	%rax, %rdx
	call	_Z8_calcaddixii
	movq	%rax, %rcx
	movl	-4(%rbp), %eax
	cltq
	movl	16(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	leaq	t(%rip), %rax
	movq	(%rdx,%rax), %rax
	addq	%rax, %rcx
	movl	-4(%rbp), %eax
	cltq
	movl	16(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	leaq	t(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	addl	$1, -4(%rbp)
	jmp	.L31
.L29:
	movl	32(%rbp), %edx
	movl	24(%rbp), %eax
	movl	%edx, %r8d
	movl	%eax, %edx
	movl	16(%rbp), %ecx
	call	_Z5_downiii
	movl	24(%rbp), %edx
	movl	32(%rbp), %eax
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -8(%rbp)
	movl	40(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jg	.L33
	movl	16(%rbp), %eax
	addl	%eax, %eax
	movl	40(%rbp), %r9d
	movl	-8(%rbp), %r8d
	movl	24(%rbp), %edx
	movl	56(%rbp), %ecx
	movl	%ecx, 40(%rsp)
	movl	48(%rbp), %ecx
	movl	%ecx, 32(%rsp)
	movl	%eax, %ecx
	call	_Z7_modifyiiiiii
.L33:
	movl	48(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	.L34
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	16(%rbp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	movl	40(%rbp), %r9d
	movl	32(%rbp), %r8d
	movl	56(%rbp), %ecx
	movl	%ecx, 40(%rsp)
	movl	48(%rbp), %ecx
	movl	%ecx, 32(%rsp)
	movl	%eax, %ecx
	call	_Z7_modifyiiiiii
.L34:
	movl	16(%rbp), %ecx
	call	_Z3_upi
	nop
	jmp	.L28
.L35:
	nop
.L28:
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z6_queryiiiii
	.def	_Z6_queryiiiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6_queryiiiii
_Z6_queryiiiii:
.LFB8820:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$160, %rsp
	.seh_stackalloc	160
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movl	48(%rbp), %eax
	cmpl	32(%rbp), %eax
	jg	.L37
	movl	56(%rbp), %eax
	cmpl	40(%rbp), %eax
	jl	.L37
	movq	16(%rbp), %rax
	movl	24(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rdx, %rcx
	salq	$5, %rcx
	leaq	t(%rip), %rdx
	movq	(%rcx,%rdx), %r8
	movq	%r8, (%rax)
	movq	8(%rcx,%rdx), %r8
	movq	%r8, 8(%rax)
	movq	16(%rcx,%rdx), %r8
	movq	%r8, 16(%rax)
	movq	24(%rcx,%rdx), %rdx
	movq	%rdx, 24(%rax)
	jmp	.L36
.L37:
	movl	40(%rbp), %ecx
	movl	32(%rbp), %edx
	movl	24(%rbp), %eax
	movl	%ecx, %r8d
	movl	%eax, %ecx
	call	_Z5_downiii
	movl	32(%rbp), %edx
	movl	40(%rbp), %eax
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -4(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN5TnodeC1Ev
	movl	48(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jg	.L39
	movl	24(%rbp), %eax
	leal	(%rax,%rax), %edx
	leaq	-80(%rbp), %rax
	movl	-4(%rbp), %r9d
	movl	32(%rbp), %r8d
	movl	56(%rbp), %ecx
	movl	%ecx, 40(%rsp)
	movl	48(%rbp), %ecx
	movl	%ecx, 32(%rsp)
	movq	%rax, %rcx
	call	_Z6_queryiiiii
	leaq	-80(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN5TnodepLERKS_
.L39:
	movl	56(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jle	.L40
	movl	-4(%rbp), %eax
	leal	1(%rax), %r8d
	movl	24(%rbp), %eax
	addl	%eax, %eax
	leal	1(%rax), %edx
	leaq	-48(%rbp), %rax
	movl	40(%rbp), %r9d
	movl	56(%rbp), %ecx
	movl	%ecx, 40(%rsp)
	movl	48(%rbp), %ecx
	movl	%ecx, 32(%rsp)
	movq	%rax, %rcx
	call	_Z6_queryiiiii
	leaq	-48(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN5TnodepLERKS_
.L40:
	movq	16(%rbp), %rax
	movq	-112(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-104(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-96(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-88(%rbp), %rdx
	movq	%rdx, 24(%rax)
.L36:
	movq	16(%rbp), %rax
	addq	$160, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_Z8_calcans5Tnodeii,"x"
	.linkonce discard
	.globl	_Z8_calcans5Tnodeii
	.def	_Z8_calcans5Tnodeii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8_calcans5Tnodeii
_Z8_calcans5Tnodeii:
.LFB8821:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, %rbx
	movl	%edx, 32(%rbp)
	movl	%r8d, 40(%rbp)
	movq	(%rbx), %rdx
	movl	40(%rbp), %eax
	addl	$1, %eax
	cltq
	imulq	%rax, %rdx
	movl	$1, %eax
	subl	32(%rbp), %eax
	cltq
	imulq	%rax, %rdx
	movq	8(%rbx), %rcx
	movl	40(%rbp), %r8d
	movl	32(%rbp), %eax
	addl	%r8d, %eax
	cltq
	imulq	%rcx, %rax
	addq	%rax, %rdx
	movq	16(%rbx), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "%lld/%lld\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB8822:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$160, %rsp
	.seh_stackalloc	160
	.seh_endprologue
	call	__main
	call	_Z4readv
	movl	%eax, n(%rip)
	call	_Z4readv
	movl	%eax, m(%rip)
	movq	$0, 1600144+c(%rip)
	movq	1600144+c(%rip), %rax
	movq	%rax, 800072+c(%rip)
	movq	800072+c(%rip), %rax
	movq	%rax, c(%rip)
	movl	$1, -4(%rbp)
.L46:
	movl	n(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jg	.L45
	movl	-4(%rbp), %eax
	subl	$1, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	c(%rip), %rax
	movq	(%rdx,%rax), %rax
	leaq	1(%rax), %rcx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	c(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	-4(%rbp), %eax
	subl	$1, %eax
	cltq
	addq	$100009, %rax
	leaq	0(,%rax,8), %rdx
	leaq	c(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	cltq
	addq	$100009, %rax
	leaq	0(,%rax,8), %rdx
	leaq	c(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	-4(%rbp), %eax
	subl	$1, %eax
	cltq
	addq	$200018, %rax
	leaq	0(,%rax,8), %rdx
	leaq	c(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	%rdx, %rax
	addq	%rax, %rcx
	movl	-4(%rbp), %eax
	cltq
	addq	$200018, %rax
	leaq	0(,%rax,8), %rdx
	leaq	c(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	addl	$1, -4(%rbp)
	jmp	.L46
.L45:
	movl	$0, -8(%rbp)
.L52:
	movl	m(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jge	.L47
.L49:
	call	getchar
	movb	%al, -9(%rbp)
	cmpb	$67, -9(%rbp)
	je	.L48
	cmpb	$81, -9(%rbp)
	je	.L48
	jmp	.L49
.L48:
	call	_Z4readv
	movl	%eax, -16(%rbp)
	call	_Z4readv
	subl	$1, %eax
	movl	%eax, -20(%rbp)
	cmpb	$67, -9(%rbp)
	jne	.L50
	call	_Z4readv
	movl	%eax, %r8d
	movl	n(%rip), %eax
	leal	-1(%rax), %edx
	movl	-16(%rbp), %ecx
	movl	%r8d, 40(%rsp)
	movl	-20(%rbp), %eax
	movl	%eax, 32(%rsp)
	movl	%ecx, %r9d
	movl	%edx, %r8d
	movl	$1, %edx
	movl	$1, %ecx
	call	_Z7_modifyiiiiii
	jmp	.L51
.L50:
	movl	n(%rip), %eax
	leal	-1(%rax), %ecx
	leaq	-80(%rbp), %rax
	movl	-20(%rbp), %edx
	movl	%edx, 40(%rsp)
	movl	-16(%rbp), %edx
	movl	%edx, 32(%rsp)
	movl	%ecx, %r9d
	movl	$1, %r8d
	movl	$1, %edx
	movq	%rax, %rcx
	call	_Z6_queryiiiii
	movq	-80(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -88(%rbp)
	movl	-20(%rbp), %ecx
	movl	-16(%rbp), %edx
	leaq	-112(%rbp), %rax
	movl	%ecx, %r8d
	movq	%rax, %rcx
	call	_Z8_calcans5Tnodeii
	movq	%rax, -32(%rbp)
	movl	-20(%rbp), %eax
	subl	-16(%rbp), %eax
	addl	$2, %eax
	movslq	%eax, %rdx
	movl	-20(%rbp), %eax
	subl	-16(%rbp), %eax
	addl	$1, %eax
	cltq
	imulq	%rdx, %rax
	movq	%rax, %rdx
	shrq	$63, %rdx
	addq	%rdx, %rax
	sarq	%rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rcx
	call	_ZSt5__gcdIxET_S0_S0_
	movq	%rax, -48(%rbp)
	movq	-40(%rbp), %rax
	cqto
	idivq	-48(%rbp)
	movq	%rax, %rcx
	movq	-32(%rbp), %rax
	cqto
	idivq	-48(%rbp)
	movq	%rcx, %r8
	movq	%rax, %rdx
	leaq	.LC0(%rip), %rcx
	call	_Z6printfPKcz
.L51:
	addl	$1, -8(%rbp)
	jmp	.L52
.L47:
	movl	$0, %eax
	addq	$160, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_ZSt5__gcdIxET_S0_S0_,"x"
	.linkonce discard
	.globl	_ZSt5__gcdIxET_S0_S0_
	.def	_ZSt5__gcdIxET_S0_S0_;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZSt5__gcdIxET_S0_S0_
_ZSt5__gcdIxET_S0_S0_:
.LFB9339:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
.L56:
	cmpq	$0, 24(%rbp)
	je	.L55
	movq	16(%rbp), %rax
	cqto
	idivq	24(%rbp)
	movq	%rdx, -8(%rbp)
	movq	24(%rbp), %rax
	movq	%rax, 16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, 24(%rbp)
	jmp	.L56
.L55:
	movq	16(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.text
	.def	__tcf_0;	.scl	3;	.type	32;	.endef
	.seh_proc	__tcf_0
__tcf_0:
.LFB10127:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	_ZStL8__ioinit(%rip), %rcx
	call	_ZNSt8ios_base4InitD1Ev
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	_Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
	.seh_proc	_Z41__static_initialization_and_destruction_0ii
_Z41__static_initialization_and_destruction_0ii:
.LFB10126:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 32(%rbp)
	movl	%edx, 40(%rbp)
	cmpl	$1, 32(%rbp)
	jne	.L63
	cmpl	$65535, 40(%rbp)
	jne	.L63
	leaq	_ZStL8__ioinit(%rip), %rcx
	call	_ZNSt8ios_base4InitC1Ev
	leaq	__tcf_0(%rip), %rcx
	call	atexit
	leaq	t(%rip), %rax
	movl	$400035, %ebx
	movq	%rax, %rsi
.L62:
	testq	%rbx, %rbx
	js	.L63
	movq	%rsi, %rcx
	call	_ZN5TnodeC1Ev
	addq	$32, %rsi
	subq	$1, %rbx
	jmp	.L62
.L63:
	nop
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rbp
	ret
	.seh_endproc
	.def	_GLOBAL__sub_I_t;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I_t
_GLOBAL__sub_I_t:
.LFB10150:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$65535, %edx
	movl	$1, %ecx
	call	_Z41__static_initialization_and_destruction_0ii
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I_t
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	memset;	.scl	2;	.type	32;	.endef
	.def	getchar;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	atexit;	.scl	2;	.type	32;	.endef
