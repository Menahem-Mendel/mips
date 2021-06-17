.data
	tru: .asciiz "\ntrue"
	fal: .asciiz "\nfalse"
	space: .asciiz " "
	arr: .byte 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
	base: .space 6
	lenBase: .word 6
	lenArr: .word 32
.text
.globl main
main:
	li $t0, 0
	while:
		bgt $t0, 5, endWhile
		
		li $v0, 5
		syscall
		sb $v0, base($t0) 
		
		addi $t0, $t0, 1
		j while
	endWhile:
	
	la $a0, arr
	lw $t7, lenArr
	whileOuter:
		ble $t7, $t6 false
		
		la $a1, base
		lw $t6, lenBase
		whileInner:
			blez $t6, true
			
			lb $t0, ($a1)
			lb $t1, ($a0)
			
			bne $t0, $t1, continue
			
			subi $t6, $t6, 1
			addi $a0, $a0, 1
			addi $a1, $a1, 1
			j whileInner
		endWhileInner:
		
		continue:
		subi $t7, $t7, 1
		addi $a0, $a0, 1
		j whileOuter

		true: 
			li $v0, 4
			la $a0, tru
			syscall
			j endwhileOuter

		false:
			li $v0, 4
			la $a0, fal
			syscall
			j endwhileOuter
	endwhileOuter:
	
	li $v0, 11
	li $a0, 10
	syscall
		
	li $t0, 0
	print:
		bgt $t0, 5, endPrint
		
		li $v0, 1
		lb $a0, base($t0)
		syscall
		
		li $v0, 11
		li $a0, 32
		syscall
		
		addi $t0, $t0, 1
		j print
	endPrint:
	
# end program
li $v0, 10
syscall
	
