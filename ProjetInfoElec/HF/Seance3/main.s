	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"but0: "
.LC1:
	.string	"%d"
.LC2:
	.string	"but1: "
.LC3:
	.string	"pot: "
.LC4:
	.string	"\te0\te1\te2\te3"
.LC5:
	.string	"Eold\t%d\t%d\t%d\t%d\n"
.LC6:
	.string	"Appel\t%d\t%d\t%d\t%d\n"
.LC7:
	.string	"Reponse\t%d\t%d\t%d\t%d\n"
.LC8:
	.string	"Ecur \t%d\t%d\t%d\t%d\n"
	.align 8
.LC9:
	.string	"---------------------------------"
	.text
	.globl	grafcet_interpreter
	.type	grafcet_interpreter, @function
grafcet_interpreter:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$368, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, -344(%rbp)
	movl	$0, -340(%rbp)
	movl	$0, -336(%rbp)
	movl	$0, -332(%rbp)
.L13:
	movl	$0, -296(%rbp)
	movl	$0, -292(%rbp)
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-368(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-364(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-360(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$0, -296(%rbp)
	jne	.L2
	movl	-368(%rbp), %eax
	cmpl	$1, %eax
	jne	.L2
	movl	$1, -356(%rbp)
	jmp	.L3
.L2:
	movl	$0, -356(%rbp)
.L3:
	cmpl	$0, -292(%rbp)
	jne	.L4
	movl	-364(%rbp), %eax
	cmpl	$1, %eax
	jne	.L4
	movl	$1, -352(%rbp)
	jmp	.L5
.L4:
	movl	$0, -352(%rbp)
.L5:
	movl	$0, -348(%rbp)
	jmp	.L6
.L12:
	movl	$0, -328(%rbp)
	movl	$0, -312(%rbp)
	movl	$0, -324(%rbp)
	movl	$0, -308(%rbp)
	movl	$0, -320(%rbp)
	movl	$0, -304(%rbp)
	movl	$0, -316(%rbp)
	movl	$0, -300(%rbp)
	movl	-344(%rbp), %eax
	movl	%eax, -288(%rbp)
	movl	-340(%rbp), %eax
	movl	%eax, -284(%rbp)
	movl	-336(%rbp), %eax
	movl	%eax, -280(%rbp)
	movl	-332(%rbp), %eax
	movl	%eax, -276(%rbp)
	cmpl	$1, -344(%rbp)
	jne	.L7
	cmpl	$1, -356(%rbp)
	jne	.L7
	movl	-360(%rbp), %eax
	cmpl	$127, %eax
	jg	.L7
	movl	$1, -324(%rbp)
	movl	$1, -312(%rbp)
.L7:
	cmpl	$1, -340(%rbp)
	jne	.L8
	cmpl	$1, -356(%rbp)
	jne	.L8
	movl	-360(%rbp), %eax
	cmpl	$128, %eax
	jle	.L8
	movl	$1, -320(%rbp)
	movl	$1, -308(%rbp)
.L8:
	cmpl	$1, -336(%rbp)
	jne	.L9
	cmpl	$1, -356(%rbp)
	jne	.L9
	movl	-360(%rbp), %eax
	cmpl	$127, %eax
	jg	.L9
	movl	$1, -316(%rbp)
	movl	$1, -304(%rbp)
.L9:
	cmpl	$1, -332(%rbp)
	jne	.L10
	cmpl	$1, -352(%rbp)
	jne	.L10
	movl	$1, -328(%rbp)
	movl	$1, -300(%rbp)
.L10:
	cmpl	$0, -312(%rbp)
	sete	%al
	movzbl	%al, %eax
	andl	-344(%rbp), %eax
	orl	-328(%rbp), %eax
	movl	%eax, -344(%rbp)
	cmpl	$0, -308(%rbp)
	sete	%al
	movzbl	%al, %eax
	andl	-340(%rbp), %eax
	orl	-324(%rbp), %eax
	movl	%eax, -340(%rbp)
	cmpl	$0, -304(%rbp)
	sete	%al
	movzbl	%al, %eax
	andl	-336(%rbp), %eax
	orl	-320(%rbp), %eax
	movl	%eax, -336(%rbp)
	cmpl	$0, -300(%rbp)
	sete	%al
	movzbl	%al, %eax
	andl	-332(%rbp), %eax
	orl	-316(%rbp), %eax
	movl	%eax, -332(%rbp)
	movl	-344(%rbp), %eax
	cmpl	-288(%rbp), %eax
	jne	.L11
	movl	-340(%rbp), %eax
	cmpl	-284(%rbp), %eax
	jne	.L11
	movl	-336(%rbp), %eax
	cmpl	-280(%rbp), %eax
	jne	.L11
	movl	-332(%rbp), %eax
	cmpl	-276(%rbp), %eax
	jne	.L11
	movl	$1, -348(%rbp)
.L11:
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	movl	-276(%rbp), %esi
	movl	-280(%rbp), %ecx
	movl	-284(%rbp), %edx
	movl	-288(%rbp), %eax
	movl	%esi, %r8d
	movl	%eax, %esi
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-316(%rbp), %esi
	movl	-320(%rbp), %ecx
	movl	-324(%rbp), %edx
	movl	-328(%rbp), %eax
	movl	%esi, %r8d
	movl	%eax, %esi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-300(%rbp), %esi
	movl	-304(%rbp), %ecx
	movl	-308(%rbp), %edx
	movl	-312(%rbp), %eax
	movl	%esi, %r8d
	movl	%eax, %esi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-332(%rbp), %esi
	movl	-336(%rbp), %ecx
	movl	-340(%rbp), %edx
	movl	-344(%rbp), %eax
	movl	%esi, %r8d
	movl	%eax, %esi
	leaq	.LC8(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC9(%rip), %rdi
	call	puts@PLT
.L6:
	cmpl	$0, -348(%rbp)
	je	.L12
	jmp	.L13
	.cfi_endproc
.LFE0:
	.size	grafcet_interpreter, .-grafcet_interpreter
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, %eax
	call	grafcet_interpreter
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 6.2.0-5ubuntu12) 6.2.0 20161005"
	.section	.note.GNU-stack,"",@progbits
