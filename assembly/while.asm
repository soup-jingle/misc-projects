	# #################################################
	# Patrick Bunetic        
	# ID: 800441093          
	# While Structure 
	# #################################################

	.data
initial_prompt:	.asciiz "Enter the number of Fibonacci numbers to display (2-15): "
colon:		.asciiz ":  "
newline:	.asciiz "\n"
invalid:	.asciiz "The entered number is not valid. Enter another.\n"
	.text
	.globl main
main:
	li $v0, 4
	la $a0, initial_prompt
	syscall

	li $v0, 5
	syscall

	move $s0, $v0

	ble $s0, 1, error
	bgt $s0, 15, error
	j fib

error:
	li $v0, 4
	la $a0, invalid
	syscall
	j main

fib:
	li $s1, 1	# Counter
	li $s2, 1	# fib(n-1)
	li $s3, 1	# fib(n)

	# Print first fibonacci number
	li $v0, 1
	move $a0, $s1
	syscall
	li $v0, 4
	la $a0, colon
	syscall
	li $v0, 1
	move $a0, $s2
	syscall
	li $v0, 4
	la $a0, newline
	syscall

	addu $s1, $s1, 1
	
	# Print second fibonacci number
	li $v0, 1
	move $a0, $s1
	syscall
	li $v0, 4
	la $a0, colon
	syscall
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	
	addu $s1, $s1, 1
loop:
	# Loop to print the rest of the fibonacci numbers
	# until counter is greater than user input
	bgt $s1, $s0, end

	# Next fibonacci number:
	addu $t0, $s2, $s3

	# Only hold onto two most previous fibonacci numbers
	move $s2, $s3
	move $s3, $t0

	# Print each fibonacci
	li $v0, 1
	move $a0, $s1
	syscall
	li $v0, 4
	la $a0, colon
	syscall
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall

	# Increment our counter
	addu $s1, $s1, 1
	j loop
	
end:	
	jr $31
