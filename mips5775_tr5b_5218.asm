.data
	hex: .space 24
	opcode: .space 8
	in: .asciiz "input: "
	out: .asciiz "output: "
	
	bittrue: .word 0x00000031
	bitfalse: .word 0x00000030
	bitnot: .word 0x00000048
	bitshift: .word 0x00000074
.text
.globl main
main:
	li $v0, 5
	syscall
	
	move $t0, $v0
	srl $t0, $t0, 24
	sw $t0, opcode
	
	sll $t0, $t0, 24
	sub $t0, $v0, $t0
	sw $t0, hex
	
	li $v0, 4
	la $a0, in
	syscall
	
	li $v0, 34
	lw $a0, hex
	syscall
	
	li $v0, 11
	li $a0, 10
	syscall
	
	
	
	lw $t2, hex
	lw $t0, opcode
	lw $t1, bittrue
	beq $t0, $t1, bitTrue
	lw $t1, bitfalse
	beq $t0, $t1, bitFalse
	lw $t1, bitnot
	beq $t0, $t1, bitNot
	lw $t1, bitshift
	beq $t0, $t1, bitShift
	
	
	bitTrue:
		ori $t2, $t2, 0x000000c3
		j endIf
	bitFalse:
		andi $t2, $t2, 0xffffffc3
		j endIf
	bitNot:
		sll $t1, $t2, 16
		srl $t1, $t1, 8
		not $t1, $t1
		andi $t1, $t1, 0x00ffff00
		andi $t2, $t2, 0x000000ff
		add $t2, $t2, $t1
		
		j endIf
	bitShift:
		srl $t1, $t2, 20
		sllv $t2, $t2, $t1
		
		
		j endIf
	endIf:
	
	sw $t2, hex
	
	li $v0, 4
	la $a0, out
	syscall
	
	li $v0, 34
	lw $a0, hex
	syscall
	
	
# end program
li $v0, 10
syscall
	

