	# #################################################
	# Patrick Bunetic        
	# ID: 800441093          
	# If-Then-Else Structure 
	# #################################################

	.data
enter:	.asciiz "Enter your new PIN (0 - 999): "
reenter:	.asciiz "Re-Enter your PIN (0 - 999): "
error:	.asciiz "You entered an invalid PIN.\n"
error2:	.asciiz "The two PINS you entered did not match. Try entering your PIN.\n"
success_message:	.asciiz "You successfully entered your PIN.\n"
	.text
	.globl main
main:
initial_ask:	
	li $v0, 4
	la $a0, enter
	syscall

	li $v0, 5
	syscall

	move $t0, $v0

	bge $t0, 1000, error_1
	blt $t0, 0, error_1
	j reenter_ask

error_1:
	li $v0, 4
	la $a0, error
	syscall
	j initial_ask

reenter_ask:
 	li $v0, 4
	la $a0, reenter
	syscall
	
	li $v0, 5
	syscall

	move $t1, $v0

	bge $t1, 1000, error_2
	blt $t1, 0, error_2
	bne $t1, $t0, error_3
	j success

error_2:
	li $v0, 4
	la $a0, error
	syscall
	j initial_ask

error_3:	
	li $v0, 4
	la $a0, error2
	syscall
	j reenter_ask

success:
	li $v0, 4
	la $a0, success_message
	syscall

	jr $31
