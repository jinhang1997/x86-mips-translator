	.file	"hellobmp.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$96, %esp
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	$640, -12(%ebp)
	movl	$480, -16(%ebp)
	movl	$1869771365, -52(%ebp)
	movl	$622862706, -48(%ebp)
	movl	$2660, -44(%ebp)
	movl	$0, -40(%ebp)
	movl	$0, -36(%ebp)
	movl	$1819043176, -72(%ebp)
	movl	$8559, -68(%ebp)
	movl	$0, -64(%ebp)
	movl	$0, -60(%ebp)
	movl	$0, -56(%ebp)
	movl	$1819043176, -92(%ebp)
	movl	$1835150959, -88(%ebp)
	movl	$112, -84(%ebp)
	movl	$0, -80(%ebp)
	movl	$0, -76(%ebp)
	movl	$25202, -102(%ebp)
	movl	$0, -98(%ebp)
	movw	$0, -94(%ebp)
	movl	$0, -20(%ebp)
	movl	$0, -24(%ebp)
	movl	$0, -28(%ebp)
	subl	$8, %esp
	pushl	$4
	pushl	-16(%ebp)
	pushl	-12(%ebp)
	pushl	$536805376
	pushl	$536805376
	leal	-72(%ebp), %eax
	pushl	%eax
	call	SDL_CreateWindow@PLT
	addl	$32, %esp
	movl	%eax, -20(%ebp)
	cmpl	$0, -20(%ebp)
	jne	.L2
	subl	$8, %esp
	pushl	$1
	leal	-52(%ebp), %eax
	pushl	%eax
	call	printf@PLT
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L7
.L2:
	subl	$4, %esp
	pushl	$0
	pushl	$-1
	pushl	-20(%ebp)
	call	SDL_CreateRenderer@PLT
	addl	$16, %esp
	movl	%eax, -24(%ebp)
	cmpl	$0, -24(%ebp)
	jne	.L4
	subl	$8, %esp
	pushl	$2
	leal	-52(%ebp), %eax
	pushl	%eax
	call	printf@PLT
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L7
.L4:
	movl	$0, -32(%ebp)
	subl	$12, %esp
	leal	-92(%ebp), %eax
	pushl	%eax
	call	puts@PLT
	addl	$16, %esp
	subl	$8, %esp
	leal	-102(%ebp), %eax
	pushl	%eax
	leal	-92(%ebp), %eax
	pushl	%eax
	call	SDL_RWFromFile@PLT
	addl	$16, %esp
	subl	$8, %esp
	pushl	$1
	pushl	%eax
	call	SDL_LoadBMP_RW@PLT
	addl	$16, %esp
	movl	%eax, -32(%ebp)
	cmpl	$0, -32(%ebp)
	jne	.L5
	subl	$8, %esp
	pushl	$3
	leal	-52(%ebp), %eax
	pushl	%eax
	call	printf@PLT
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L7
.L5:
	subl	$8, %esp
	pushl	-32(%ebp)
	pushl	-24(%ebp)
	call	SDL_CreateTextureFromSurface@PLT
	addl	$16, %esp
	movl	%eax, -28(%ebp)
	subl	$12, %esp
	pushl	-32(%ebp)
	call	SDL_FreeSurface@PLT
	addl	$16, %esp
	cmpl	$0, -28(%ebp)
	jne	.L6
	subl	$8, %esp
	pushl	$4
	leal	-52(%ebp), %eax
	pushl	%eax
	call	printf@PLT
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L7
.L6:
	pushl	$0
	pushl	$0
	pushl	-28(%ebp)
	pushl	-24(%ebp)
	call	SDL_RenderCopy@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	-24(%ebp)
	call	SDL_RenderPresent@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	$1000
	call	SDL_Delay@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	-20(%ebp)
	call	SDL_DestroyWindow@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	-24(%ebp)
	call	SDL_DestroyRenderer@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	-28(%ebp)
	call	SDL_DestroyTexture@PLT
	addl	$16, %esp
	call	SDL_Quit@PLT
	movl	$0, %eax
.L7:
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB12:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE12:
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
