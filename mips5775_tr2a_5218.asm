.data
	array: .byte 1,2,3,4,7,6,5,8,127
.text
	main:
		li $a1, 9 # array length
		
		li $t0, 0
		while:
			bgt $t0, $a1, endWhile # while i < a1
			
			lb $a0, array($t0) # a0 = array + i
			
			# if (v1 < a0)
			slt $t2, $v1, $a0
			beq $t2, $zero, endIf
			move $v1, $a0 # if true: v1 = a0
			endIf:
			
			addi $t0, $t0, 1 # i++
			j while
		endWhile:
		
		jal print # print the $t1 register value
		 
	# end program
	li $v0, 10
	syscall
	
	# func print byte as an integer	
	print:
		li $v0, 1 # print integer
		add $a0, $zero, $v1
		syscall
		
		jr $ra
		