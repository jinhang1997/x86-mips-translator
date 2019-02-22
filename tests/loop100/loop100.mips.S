	.file	1 "loop100.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.gnu_attribute 4, 1
	.abicalls
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,24,$31		# vars= 8, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	sw	$0,12($fp)
	li	$2,1			# 0x1
	sw	$2,8($fp)
	.option	pic0
	j	$L2
	nop

	.option	pic2
$L3:
	lw	$3,12($fp)
	lw	$2,8($fp)
	addu	$2,$3,$2
	sw	$2,12($fp)
	lw	$2,8($fp)
	addiu	$2,$2,1
	sw	$2,8($fp)
$L2:
	lw	$2,8($fp)
	slt	$2,$2,101
	bne	$2,$0,$L3
	nop

	lw	$3,12($fp)
	li	$2,5050			# 0x13ba
	beq	$3,$2,$L4
	nop

	li	$2,1			# 0x1
	.option	pic0
	j	$L5
	nop

	.option	pic2
$L4:
	move	$2,$0
$L5:
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
