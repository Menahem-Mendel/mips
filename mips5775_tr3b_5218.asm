.data
	arr: .byte 1,2,4,8,164
	len: .word 5
	
	ap: .asciiz "This is arithmetic progression\n"
	gp: .asciiz "This is geometric progression\n"
	eq: .asciiz "="
	non: .asciiz "this is not a progression\n"
.text
.globl main
	main:
		la $a0, arr # array first element address
		lw $a1, len # length of array
		addi $a1, $a1, -1 # len--
		
		jal checkAP
		beq $s0, $zero, IfAP
		jal checkGP
		beq $s0, $zero, IfGP
			# print non
			li $v0, 4
			la $a0, non 
			syscall
		
			j endIfP
		IfAP:
			jal printAP
			j print
		IfGP:
			jal printGP
			j print
		print:
			# print a=$arr[0]
			li $v0, 11
			li $a0, 'a'
			syscall
		
			li $v0, 4
			la $a0, eq
			syscall
		
			li $v0, 1
			lb $a0, arr
			syscall
		endIfP:
	
	# end program
	li $v0, 10
	syscall
	
	checkAP:
		li $s0, 0 # return true
		
		lb $t1, arr # t1 = array[0]
		lb $t2, arr+1 # t2 = array[1]
		sub $t3, $t2, $t1 # d = A(1)-A(0)
		move $t4, $t3 # t4 = d
			
		li $t0, 2 # i = 2
		while2:
			bgt $t0, $a1, endWhile2 # while (i < len(array)-1)
			
			lb $t1, arr+-1($t0) # t1 = array[i]
			lb $t2, arr($t0) # t2 = array[i+1]
			
			sub $t3, $t2, $t1 # d = A(n+1)-A(n)
			
			beq $t4, $t3, endIf2
				li $s0, 1 # return false
				j endWhile2
			endIf2:
			
			addi $t0, $t0, 1 # i++
			j while2
		endWhile2:
		
		jr $ra
		
	printAP:
		li $v0, 4
		la $a0, ap
		syscall
		
		li $v0, 11
		li $a0, 'd'
		syscall
		
		jr $ra
		
	checkGP:
		li $s0, 0 # return true
		
		lb $t1, arr # t1 = array[0]
		lb $t2, arr+1 # t2 = array[1]
		div $t3, $t2, $t1 # q = A(1)/A(0)
		move $t4, $t3 # t4 = q
			
		li $t0, 2 # i = 2
		while1:
			bgt $t0, $a1, endWhile1 # while (i < len(array)-1)
			
			lb $t1, arr+-1($t0) # t1 = array[i]
			lb $t2, arr($t0) # t2 = array[i+1]
			
			div $t3, $t2, $t1 # d = A(n+1)/A(n)
			
			beq $t4, $t3, endIf1
				li $s0, 1 # return false
				j endWhile1
			endIf1:
			
			addi $t0, $t0, 1 # i++
			j while1
		endWhile1:
		
		jr $ra
		
	printGP:
		li $v0, 4
		la $a0, gp
		syscall
		
		li $v0, 11
		li $a0, 'q'
		syscall
		
		li $v0, 4
		la $a0, eq
		syscall
		
		lb $t1, arr
		lb $t2, arr+1
		div $t3, $t2, $t1
		
		li $v0, 1
		la $a0, ($t3)
		syscall
		
		jr $ra
