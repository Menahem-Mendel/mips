.data
	value: .asciiz "\nEnter value:\n"
	opcode: .asciiz "Enter opcode:\n"
	result: .asciiz "\nResult:\n"
	enter: .asciiz "\n"
	
	opcodes: .asciiz "+-*@"
	
.text
	main:
		lb $t0, opcodes # +
		lb $t1, opcodes+1 # -
		lb $t2, opcodes+2 # *
		lb $t3, opcodes+3 # @
		
		# ask to write value
		la $a0, value
		jal printStr
		
		# get integer
		la $v0, 5
		syscall
			
		move $t5, $v0 # res = input
		
		while:
			# ask to write opcode
			la $a0, opcode
			jal printStr
			
			# read value         		
         	li $v0, 12
			syscall
			
			move $t4, $v0 # store opcode in t4
			
			bne $t4, $t3, else # if (opcode != '@')
				j endWhile
			else:
				# ask to write value
				la $a0, value
				jal printStr
				
				# get integer
				la $v0, 5
				syscall

				beq $t4, $t0, elseIfAdd # if (opcode == '+')
				beq $t4, $t1, elseIfSub # if (opcode == '-')
				beq $t4, $t2, elseIfMul # if (opcode == '*')
					j endIf
				elseIfAdd:
					add $t5, $t5, $v0 # res += input
					j endIf
				elseIfSub:
					sub $t5, $t5, $v0 # res -= input
					j endIf
				elseIfMul:
					mul $t5, $t5, $v0 # res *= input
					j endIf
			endIf:
			
			j while
		endWhile:
		
		# ask to write opcode
         	la $a0, result
         	jal printStr
         	
         	la $a0, ($t5) # arg = res
         	jal printInt
	
	# end program
	li $v0, 10
	syscall
	
	printInt:
		li $v0, 1
		syscall
		
		jr $ra
	
	printStr:
		li $v0, 4
		syscall
		
		jr $ra
