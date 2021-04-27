	####################################
	# Patrick Bunetic
	# 800441093
	# CS312, Fall 2015
	# Project 2: Tower of Hanoi
	####################################
	.data
moving:	.asciiz "\nMOVING "
disks:	.asciiz " DISKS ... \n\n"
from:		.asciiz "  Move: Tower "
to:			.asciiz " -> "
line:		.asciiz "\n"
final:	.asciiz "Move disk: Tower 1 to Tower 3\n"
done:		.asciiz "\nDONE!\n\n"
	.text
	.globl main
main:	
	li $t0, 4				# $t0 is the number of disks (argument1)
	##      ^   [Change this number for a different number of disks]
	
	# print: Moving n disks...
	li $v0, 4
	la $a0, moving
	syscall
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 4
	la $a0, disks
	syscall
	
	# rec_hanoi(n, orig, dest, inter)
	#		$aX registers are like the arguments
	#		passed to rec_hanoi function in C program
	#
	#		(note: I swapped arguments 3 and 4, so arg4 is destination)
	#
	li $a1, 1				# $a1 is tower 1 (argument2, origin)
	li $a2, 2				# $a2 is tower 2 (argument3, intermediate)
	li $a3, 3				# $a3 is tower 3 (argument4, destination)
	jal rec_hanoi

	# Exit
	li $v0, 4
	la $a0, done
	syscall
	li $v0, 10
	syscall

rec_hanoi:
	#	$s1 refers to tower 1,
	#	$s2 to tower 2,
	#	and $s3 to tower 3
	
	# Save to stack
	subu $sp, $sp, 20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	
	# while(n>0)
	beq $t0, 0, return

	# rec_hanoi(n-1, orig, dest, int) ---------------------
	# 	(includes storing/restoring $aX arguments on stack)
	subu $sp, $sp, 16
	sw $t0, ($sp)
	sw $a1, 4($sp)
	sw $a2, 8($sp)
	sw $a3, 12($sp)
	
	subu $t0, $t0, 1
	move $t1, $a3 # swap intermediate and destination
	move $a3, $a2
	move $a2, $t1
	jal rec_hanoi			# Recursive call

	lw $s0, ($sp)		# load $t0 to $s0
	lw $s1, 4($sp)	# load $a1 to $s1
	lw $s2, 8($sp)	# load $a2 to $s2
	lw $s3, 12($sp)	# load $a3 to $s3
	addu $sp, $sp, 16
	# ---------------------------------------------------
	
	# print() -------------------------------------------
	li $v0, 4
	la $a0, from
	syscall
	li $v0, 1
	move $a0, $s1
	syscall
	li $v0, 4
	la $a0, to
	syscall
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, line
	syscall
	# ----------------------------------------------------
	
	# rec_hanoi(n-1, int, dest, orig) --------------------
	# 	(unlike first time, does not include storing/restoring
	# 	 args since there are no other recursive calls after this)
	subu $t0, $s0, 1
	move $a1, $s2		# Swap origin and intermediate
	move $a2, $s1		# based on whats saved to the stack
	move $a3, $s3
	jal rec_hanoi
	# ----------------------------------------------------

return:
	# This function restores from the stack and then
	# returns to where 'rec_hanoi()' was called from
	lw $ra, ($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	addu $sp, $sp, 20
	jr $ra
