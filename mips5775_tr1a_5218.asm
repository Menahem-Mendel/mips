.data
	src: .word 1, 2, 3, 0, 4, 5, 6, 0 # source
	dest: .space 32 # destination
	len: .word 8 # length of arrays
.text
	main:
		lw $t1, len # length of array
		la $a0, src # source address
		la $a1, dest # destination address
		li $t0, 1 # i = 0
		while:
 			bgt $t0, $t1, endWhile # while i < len
 			
 			lw $t2, ($a0) # load from source address in t2
 			beq $t2, $zero, endWhile # if (src[i] == 0) break
 			sw $t2, ($a1) # store t2 in destination address
 			
			addi, $t0, $t0, 1 # i++
			addi, $a0, $a0, 4 # source += i*4
			addi, $a1, $a1, 4 # destination += i*4
			j while
		endWhile:
	
		addi, $t0, $t0, 1 # i--
		
	la $v0, ($t0) # store counter in v0