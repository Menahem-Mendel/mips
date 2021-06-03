.data
	askArr: .asciiz "Please enter sequence of 32 elemnts\n"
	askBase: .asciiz "Please enter base sequence with 6 elements\n"
	
	base: .byte 0:2
	arr: .byte 0:6
	len: .word 5
	
	subseq: .byte 0
.text
.globl main
	main:
		# ask array sequence
		li $v0, 4
		la $a0, askArr
		syscall
		
		lw $a1, len # the length of array
		li $t0, 0 # i = 0
		while1:
			bgt $t0, $a1, endWhile1 # while i < len(array)
			
			# read input integer
			li $v0, 5
			syscall
			sb $v0, arr($t0) # arr[i] = input
			
			addi $t0, $t0, 1 # i++
			j while1
		endWhile1:
		
		# ask base sequence
		li $v0, 4
		la $a0, askBase
		syscall
		
		li $t0, 0 # i = 0
		while2:
			bgt $t0, 1, endWhile2 # while i < len(array)
			
			# read input integer
			li $v0, 5
			syscall
			sb $v0, base($t0) # base[i] = input
			
			addi $t0, $t0, 1 # i++
			j while2
		endWhile2:
		
		lw $a0, len # the length of array
		li $a1, 5 # the lenght of base
		jal isSubseq
		sw $v0, subseq
	
	# end program
	li $v0, 10
	syscall

.globl isSubseq
	isSubseq:
		subu $sp, $sp, 12
		sw $ra, ($sp)
		sw $s0, 4($sp)
		sw $s1, 8($sp)
		
		move $s0, $a0
		move $s1, $a1
		
		# base case
		seq $s3, $zero, $s0
		beq $s0, $zero, endSubseq
		seq $s3, $zero, $s1
		beq $s1, $zero, endSubseq
		
		lb $t0, arr($s0)
		lb $t1, base($s1)
		
		bne $t0, $t1, else
			# isSubseq(lenArr - 1, lenBase - 1)
			sub $a0, $a0, 1
			sub $s1, $s1, 1
			jal isSubseq
			j endIf
		else:
			# isSubseq(lenArr, lenBase - 1)
			move $s0, $a0
			move $s1, $a1
			sub $s0, $s0, 1
			sub $s1, $s1, 1
			jal isSubseq
		endIf:
		
		
		
		endSubseq:
			lw $ra, ($sp)
			lb $s0, 4($sp)
			addu $sp, $sp, 12
			
			jr $ra
		
		
	
		#li $t0, 0 # i = 0
		#outer:
		#	bgt $t0, $a1, endOuter # while i < len(array)
		#	li $t1, 0
		#	inner:
		#		bgt $t0, 1, endInner # while i < len(array)
		#		
		#		lb $t3, arr($t0)
		#		lb $t4, base($t1)
		#		bne $t3, $t4, outer
		#			addi $t0, $t0, 1
		#			addi $t1, $t1, 1
		#		j inner
		#	endInner:
		#	
		#	addi $t0, $t0, 1
		#	j outer
		#endOuter:
		#
		#jr $ra