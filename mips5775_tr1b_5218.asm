.text
	main:
		li $t1, 0 # i = 0
		while:
			# get integer
			li $v0, 5
			syscall
			
			beq $v0, $zero, endWhile  # if (input == 0) break
			bgt $v0, 99, continue # if (input > 99) continue
			blt $v0, -99, continue  # if (input < -99) continue
			add $t1, $t1, $v0 # i++
			continue:
			j while
		endWhile:

	
	