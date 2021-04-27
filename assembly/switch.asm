	# #################################################
	# Patrick Bunetic        
	# ID: 800441093          
	# Switch Structure 
	# #################################################

	.data
question:	.asciiz "What are you going to do this weekend?\n"
opt1:	.asciiz "1: Drink beer\n"
opt2:	.asciiz "2: Nap all day long\n"
opt3:	.asciiz "3: Feed my cats\n"
opt4:	.asciiz "4: Write a paper on Einstein's Theory of Relativity\n\n"
c1:	.asciiz "Select and option (enter the option number): "
rep1:	.asciiz "\nThat's what I can do\n"
rep2:	.asciiz "\nI know I can't\n"
rep3:	.asciiz "\nI don't have a cat\n"
rep4:	.asciiz "\nI must have gone crazy\n"
error_prompt:	.asciiz "\nNot a valid option!\n\n"
	.text
	.globl main
main:
	li $v0, 4
	la $a0, question
	syscall
	
	li $v0, 4
	la $a0, opt1
	syscall
	li $v0, 4
	la $a0, opt2
	syscall
	li $v0, 4
	la $a0, opt3
	syscall
	li $v0, 4
	la $a0, opt4
	syscall
	li $v0, 4
	la $a0, c1
	syscall
	
	li $v0, 5
	syscall
	move $t0, $v0
	j switch

error:
	li $v0, 4
	la $a0, error_prompt
	syscall
	j main

switch:
	beq $t0, 1, reply1
	beq $t0, 2, reply2
	beq $t0, 3, reply3
	beq $t0, 4, reply4
	j error

reply1:
	li $v0, 4
	la $a0, rep1
	syscall
	j end
	
reply2:
	li $v0, 4
	la $a0, rep2
	syscall
	j end
		
reply3:	
	li $v0, 4
	la $a0, rep3
	syscall
	j end
	
reply4:	
	li $v0, 4
	la $a0, rep4
	syscall
	j end
	
end:
	jr $31
