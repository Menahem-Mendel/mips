.data 
	arr: .word 6,6,5,4,3,2,1,5
	len: .word 8
.text
.globl main
	main:
		lw $t7, len # length of array
		li $t0, 0 # i = 0
		outer:
 			bgt $t0, $t7, endOuter # while i < len
 			
			la $a0, arr # load array address
			# len - i - 1
 			sub $t6, $t7, $t0 
 			sub $t6, $t6, 1 

 			li $t1, 0 # j = 0
			inner:
				bgt $t1, $t6, endInner # while j < len - i - 1
				
				add $a1, $a0, 4 # a1 = &(arr[j+1])
				lw $s0, ($a0) # s0 = arr[j]
				lw $s1, ($a1) # s1 = arr[j+1]
				slt $t3, $s1, $s0 # if (arr[j+1] < arr[j])
				beq $t3, $zero, endIf
					jal swap # if true: swap(arr[j], arr[j+1])
				endIf:
				
				addi $t1, $t1, 1 # j++
				add $a0, $a0, 4 # arr++
				j inner
			endInner:
 			
			addi, $t0, $t0, 1 # i++
			j outer
		endOuter:
		
	# end program
	li $v0, 10
	syscall
	
	swap:		
		la $s2, ($a0) # tmp = &arr[i]
		sw $s0, ($a1) # arr[i] = arr[i+1]
		sw $s1, ($s2) # arr[i+1] = *tmp
		
		jr $ra
