	.file	"rec100.c"
	.text
	.globl	get_sum
	.type	get_sum, @function
get_sum:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	jne	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	movl	8(%ebp), %eax
	subl	$1, %eax
	subl	$12, %esp
	pushl	%eax
	call	get_sum
	addl	$16, %esp
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
.L3:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	get_sum, .-get_sum
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	subl	$12, %esp
	pushl	$100
	call	get_sum
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	cmpl	$5050, -12(%ebp)
	je	.L5
	movl	$127, %eax
	jmp	.L6
.L5:
	movl	$63, %eax
.L6:
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.3.1-14ubuntu2) 5.3.1 20160413"
	.section	.note.GNU-stack,"",@progbits
