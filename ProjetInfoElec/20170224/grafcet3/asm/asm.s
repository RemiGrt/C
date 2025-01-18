	.file	"asm.c"
	.comm	codeSegment,4000,32
	.comm	currentInst,4,4
	.comm	tabInstructionNames,3200,32
	.comm	currentInstructionName,4,4
	.comm	tabLabels,1600,32
	.comm	currentLabel,4,4
	.comm	tabReferences,1600,32
	.comm	currentRef,4,4
	.text
	.globl	addCode
	.type	addCode, @function
addCode:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	currentInst(%rip), %eax
	cmpl	$999, %eax
	jg	.L3
	movl	currentInst(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, currentInst(%rip)
	movl	-4(%rbp), %edx
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	codeSegment(%rip), %rax
	movl	%edx, (%rcx,%rax)
.L3:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	addCode, .-addCode
	.globl	addInstructionName
	.type	addInstructionName, @function
addInstructionName:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movq	%rcx, -40(%rbp)
	movl	%r8d, -44(%rbp)
	movl	currentInstructionName(%rip), %ebx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strdup@PLT
	movq	%rax, %rcx
	movslq	%ebx, %rax
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	tabInstructionNames(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	currentInstructionName(%rip), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rcx
	leaq	8+tabInstructionNames(%rip), %rax
	movl	-28(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	currentInstructionName(%rip), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rcx
	leaq	12+tabInstructionNames(%rip), %rax
	movl	-32(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	currentInstructionName(%rip), %ebx
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	strdup@PLT
	movq	%rax, %rcx
	movslq	%ebx, %rax
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+tabInstructionNames(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	currentInstructionName(%rip), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rcx
	leaq	24+tabInstructionNames(%rip), %rax
	movl	-44(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	currentInstructionName(%rip), %eax
	addl	$1, %eax
	movl	%eax, currentInstructionName(%rip)
	nop
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	addInstructionName, .-addInstructionName
	.globl	findLabel
	.type	findLabel, @function
findLabel:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L6
.L9:
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	tabLabels(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L7
	movl	-4(%rbp), %eax
	jmp	.L8
.L7:
	addl	$1, -4(%rbp)
.L6:
	movl	currentLabel(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L9
	movl	$-1, %eax
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	findLabel, .-findLabel
	.globl	addLabel
	.type	addLabel, @function
addLabel:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	currentLabel(%rip), %ebx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strdup@PLT
	movq	%rax, %rcx
	movslq	%ebx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	tabLabels(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	currentLabel(%rip), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rcx
	leaq	8+tabLabels(%rip), %rax
	movl	-28(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	currentLabel(%rip), %eax
	addl	$1, %eax
	movl	%eax, currentLabel(%rip)
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	addLabel, .-addLabel
	.globl	addReference
	.type	addReference, @function
addReference:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	currentRef(%rip), %ebx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strdup@PLT
	movq	%rax, %rcx
	movslq	%ebx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	tabReferences(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	movl	currentRef(%rip), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rcx
	leaq	8+tabReferences(%rip), %rax
	movl	-28(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	currentRef(%rip), %eax
	addl	$1, %eax
	movl	%eax, currentRef(%rip)
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	addReference, .-addReference
	.globl	resolveReferences
	.type	resolveReferences, @function
resolveReferences:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -8(%rbp)
	jmp	.L13
.L14:
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	tabReferences(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rax, %rdi
	call	findLabel
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	8+tabReferences(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rcx
	leaq	8+tabLabels(%rip), %rax
	movl	(%rcx,%rax), %eax
	movl	%eax, %ecx
	movslq	%edx, %rax
	leaq	0(,%rax,4), %rdx
	leaq	codeSegment(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	addl	$1, -8(%rbp)
.L13:
	movl	currentRef(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L14
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	resolveReferences, .-resolveReferences
	.section	.rodata
.LC0:
	.string	"Syntax error with line %s"
	.text
	.globl	decodeInstruction
	.type	decodeInstruction, @function
decodeInstruction:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$384, %rsp
	movq	%rdi, -376(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -348(%rbp)
	movl	$0, -352(%rbp)
	movl	$0, -356(%rbp)
	jmp	.L16
.L17:
	addl	$1, -352(%rbp)
.L16:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	-352(%rbp), %edx
	movslq	%edx, %rcx
	movq	-376(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rdx), %edx
	movsbq	%dl, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	je	.L17
	jmp	.L18
.L19:
	movl	-356(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -356(%rbp)
	movl	-352(%rbp), %edx
	leal	1(%rdx), %ecx
	movl	%ecx, -352(%rbp)
	movslq	%edx, %rcx
	movq	-376(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rdx), %edx
	cltq
	movb	%dl, -272(%rbp,%rax)
.L18:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	-352(%rbp), %edx
	movslq	%edx, %rcx
	movq	-376(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rdx), %edx
	movsbq	%dl, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	jne	.L19
	movl	-356(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -356(%rbp)
	cltq
	movb	$0, -272(%rbp,%rax)
	movl	$0, -360(%rbp)
	jmp	.L20
.L27:
	movl	-360(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	tabInstructionNames(%rip), %rax
	movq	(%rdx,%rax), %rdx
	leaq	-272(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	movl	%eax, -344(%rbp)
	cmpl	$0, -344(%rbp)
	jne	.L21
	movl	-360(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	12+tabInstructionNames(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$1, %eax
	je	.L22
	cmpl	$3, %eax
	je	.L23
	testl	%eax, %eax
	jne	.L21
	movl	$1, -348(%rbp)
	movl	-360(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	8+tabInstructionNames(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %edi
	call	addCode
	jmp	.L21
.L22:
	movl	$1, -348(%rbp)
	movl	-360(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+tabInstructionNames(%rip), %rax
	movq	(%rdx,%rax), %rsi
	leaq	-364(%rbp), %rcx
	leaq	-336(%rbp), %rdx
	movq	-376(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf@PLT
	movl	-360(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	8+tabInstructionNames(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %edi
	call	addCode
	movl	-364(%rbp), %eax
	movl	%eax, %edi
	call	addCode
	jmp	.L21
.L23:
	movl	$1, -348(%rbp)
	movl	-360(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+tabInstructionNames(%rip), %rax
	movq	(%rdx,%rax), %rsi
	leaq	-304(%rbp), %rcx
	leaq	-336(%rbp), %rdx
	movq	-376(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf@PLT
	movl	-360(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	8+tabInstructionNames(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %edi
	call	addCode
	leaq	-304(%rbp), %rax
	movq	%rax, %rdi
	call	findLabel
	movl	%eax, -340(%rbp)
	cmpl	$-1, -340(%rbp)
	je	.L25
	movl	-340(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	8+tabLabels(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %edi
	call	addCode
	jmp	.L30
.L25:
	movl	currentInst(%rip), %edx
	leaq	-304(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	addReference
	movl	$-1, %edi
	call	addCode
.L30:
	nop
.L21:
	addl	$1, -360(%rbp)
.L20:
	movl	currentInstructionName(%rip), %eax
	cmpl	%eax, -360(%rbp)
	jl	.L27
	movl	currentInstructionName(%rip), %eax
	cmpl	%eax, -360(%rbp)
	jne	.L31
	cmpl	$0, -348(%rbp)
	jne	.L31
	movq	-376(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %edi
	call	exit@PLT
.L31:
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L29
	call	__stack_chk_fail@PLT
.L29:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	decodeInstruction, .-decodeInstruction
	.section	.rodata
.LC1:
	.string	"%s"
.LC2:
	.string	"end"
	.text
	.globl	parseAsm
	.type	parseAsm, @function
parseAsm:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movq	%rdi, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-136(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movl	$100, %esi
	movq	%rax, %rdi
	call	fgets@PLT
	jmp	.L33
.L36:
	leaq	-112(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	-112(%rbp), %eax
	cmpb	$35, %al
	je	.L34
	leaq	-112(%rbp), %rax
	movl	$58, %esi
	movq	%rax, %rdi
	call	strchr@PLT
	movq	%rax, -120(%rbp)
	cmpq	$0, -120(%rbp)
	je	.L35
	movq	-120(%rbp), %rax
	movb	$0, (%rax)
	movl	currentInst(%rip), %edx
	leaq	-112(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	addLabel
	jmp	.L34
.L35:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	decodeInstruction
.L34:
	movq	-136(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movl	$100, %esi
	movq	%rax, %rdi
	call	fgets@PLT
.L33:
	leaq	-112(%rbp), %rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	strstr@PLT
	testq	%rax, %rax
	je	.L36
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L38
	call	__stack_chk_fail@PLT
.L38:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	parseAsm, .-parseAsm
	.section	.rodata
.LC3:
	.string	"%5.5d : %s\n"
	.text
	.globl	printLabels
	.type	printLabels, @function
printLabels:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	jmp	.L40
.L41:
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	tabLabels(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rcx
	leaq	8+tabLabels(%rip), %rax
	movl	(%rcx,%rax), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L40:
	movl	currentLabel(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L41
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	printLabels, .-printLabels
	.section	.rodata
.LC4:
	.string	"%5.5d: "
.LC5:
	.string	"add"
.LC6:
	.string	"sub"
.LC7:
	.string	"mult"
.LC8:
	.string	"div"
.LC9:
	.string	"neg"
.LC10:
	.string	"and"
.LC11:
	.string	"or"
.LC12:
	.string	"not"
.LC13:
	.string	"eq"
.LC14:
	.string	"ls"
.LC15:
	.string	"gt"
.LC16:
	.string	"push %d\n"
.LC17:
	.string	"pop %d\n"
.LC18:
	.string	"pushi %d\n"
.LC19:
	.string	"jp %d\n"
.LC20:
	.string	"jf %d\n"
.LC21:
	.string	"halt"
.LC22:
	.string	"Instruction inconnue :("
	.text
	.globl	dumpBinaryCode
	.type	dumpBinaryCode, @function
dumpBinaryCode:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	jmp	.L43
.L67:
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	codeSegment(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$11, %eax
	je	.L45
	cmpl	$11, %eax
	ja	.L46
	cmpl	$4, %eax
	je	.L47
	cmpl	$4, %eax
	ja	.L48
	cmpl	$2, %eax
	je	.L49
	cmpl	$2, %eax
	ja	.L50
	cmpl	$1, %eax
	je	.L51
	jmp	.L44
.L48:
	cmpl	$8, %eax
	je	.L52
	cmpl	$8, %eax
	ja	.L53
	cmpl	$7, %eax
	je	.L54
	jmp	.L44
.L53:
	cmpl	$9, %eax
	je	.L55
	cmpl	$10, %eax
	je	.L56
	jmp	.L44
.L46:
	cmpl	$101, %eax
	je	.L57
	cmpl	$101, %eax
	ja	.L58
	cmpl	$13, %eax
	je	.L59
	cmpl	$13, %eax
	jb	.L60
	cmpl	$100, %eax
	je	.L61
	jmp	.L44
.L58:
	cmpl	$200, %eax
	je	.L62
	cmpl	$200, %eax
	ja	.L63
	cmpl	$102, %eax
	je	.L64
	jmp	.L44
.L63:
	cmpl	$201, %eax
	je	.L65
	cmpl	$403, %eax
	je	.L66
	jmp	.L44
.L51:
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L49:
	leaq	.LC6(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L50:
	leaq	.LC7(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L47:
	leaq	.LC8(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L54:
	leaq	.LC9(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L52:
	leaq	.LC10(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L55:
	leaq	.LC11(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L56:
	leaq	.LC12(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L45:
	leaq	.LC13(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L60:
	leaq	.LC14(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L59:
	leaq	.LC15(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L61:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	codeSegment(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %esi
	leaq	.LC16(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$2, -4(%rbp)
	jmp	.L43
.L64:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	codeSegment(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %esi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$2, -4(%rbp)
	jmp	.L43
.L57:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	codeSegment(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %esi
	leaq	.LC18(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$2, -4(%rbp)
	jmp	.L43
.L62:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	codeSegment(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %esi
	leaq	.LC19(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$2, -4(%rbp)
	jmp	.L43
.L65:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	codeSegment(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %esi
	leaq	.LC20(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$2, -4(%rbp)
	jmp	.L43
.L66:
	leaq	.LC21(%rip), %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
	jmp	.L43
.L44:
	leaq	.LC22(%rip), %rdi
	call	puts@PLT
	movl	$1, %edi
	call	exit@PLT
.L43:
	movl	currentInst(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jne	.L67
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	dumpBinaryCode, .-dumpBinaryCode
	.section	.rodata
.LC23:
	.string	"%d\n"
.LC24:
	.string	"%d:%d\n"
	.text
	.globl	generateBinary
	.type	generateBinary, @function
generateBinary:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	currentInst(%rip), %edx
	movq	-24(%rbp), %rax
	leaq	.LC23(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$0, -4(%rbp)
	jmp	.L69
.L70:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	codeSegment(%rip), %rax
	movl	(%rdx,%rax), %ecx
	movl	-4(%rbp), %edx
	movq	-24(%rbp), %rax
	leaq	.LC24(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addl	$1, -4(%rbp)
.L69:
	movl	currentInst(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L70
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	generateBinary, .-generateBinary
	.section	.rodata
	.align 8
.LC25:
	.string	"Usage : asm infile.asm outfile.bin"
.LC26:
	.string	"r"
.LC27:
	.string	"Error opening read file %s\n"
.LC28:
	.string	""
.LC29:
	.string	"%s %d"
.LC30:
	.string	"push"
.LC31:
	.string	"pushi"
.LC32:
	.string	"pop"
.LC33:
	.string	"%s %s"
.LC34:
	.string	"jp"
.LC35:
	.string	"jf"
	.align 8
.LC36:
	.string	"First assembly phase (analyze and decode instructions).."
.LC37:
	.string	"no errors"
	.align 8
.LC38:
	.string	"Second assembly phase (resolve undefined references).."
	.align 8
.LC39:
	.string	"Dumping generated binary code (please verify)"
.LC40:
	.string	"w"
.LC41:
	.string	"Error opening write file %s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$3, -20(%rbp)
	je	.L72
	leaq	.LC25(%rip), %rdi
	call	puts@PLT
.L72:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	leaq	.LC26(%rip), %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L73
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC27(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L73:
	movl	$0, currentInstructionName(%rip)
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$1, %esi
	leaq	.LC5(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$2, %esi
	leaq	.LC6(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$3, %esi
	leaq	.LC7(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$4, %esi
	leaq	.LC8(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$7, %esi
	leaq	.LC9(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$8, %esi
	leaq	.LC10(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$9, %esi
	leaq	.LC11(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$10, %esi
	leaq	.LC12(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$11, %esi
	leaq	.LC13(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$12, %esi
	leaq	.LC14(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$13, %esi
	leaq	.LC15(%rip), %rdi
	call	addInstructionName
	movl	$1, %r8d
	leaq	.LC29(%rip), %rcx
	movl	$1, %edx
	movl	$100, %esi
	leaq	.LC30(%rip), %rdi
	call	addInstructionName
	movl	$1, %r8d
	leaq	.LC29(%rip), %rcx
	movl	$1, %edx
	movl	$101, %esi
	leaq	.LC31(%rip), %rdi
	call	addInstructionName
	movl	$1, %r8d
	leaq	.LC29(%rip), %rcx
	movl	$1, %edx
	movl	$102, %esi
	leaq	.LC32(%rip), %rdi
	call	addInstructionName
	movl	$1, %r8d
	leaq	.LC33(%rip), %rcx
	movl	$3, %edx
	movl	$200, %esi
	leaq	.LC34(%rip), %rdi
	call	addInstructionName
	movl	$1, %r8d
	leaq	.LC33(%rip), %rcx
	movl	$3, %edx
	movl	$201, %esi
	leaq	.LC35(%rip), %rdi
	call	addInstructionName
	movl	$0, %r8d
	leaq	.LC28(%rip), %rcx
	movl	$0, %edx
	movl	$403, %esi
	leaq	.LC21(%rip), %rdi
	call	addInstructionName
	movl	$0, currentLabel(%rip)
	movl	$0, currentInst(%rip)
	leaq	.LC36(%rip), %rdi
	call	puts@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	parseAsm
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	leaq	.LC37(%rip), %rdi
	call	puts@PLT
	leaq	.LC38(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	resolveReferences
	leaq	.LC37(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	printLabels
	leaq	.LC39(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	dumpBinaryCode
	leaq	.LC37(%rip), %rdi
	call	puts@PLT
	movq	-32(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	leaq	.LC40(%rip), %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L74
	movq	-32(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC41(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L74:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	generateBinary
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 6.2.0-5ubuntu12) 6.2.0 20161005"
	.section	.note.GNU-stack,"",@progbits
