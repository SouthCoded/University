
#
# ELECTRAN QUESTION 9.
#
# The first unsigned halfword gives the number of data values to add together.
# Then the data values follow this given as  unsigned 16-bit values.
# The final memory location allocated with a  'space  2' directive gives the
# memory location to put the result.
#
# No overflow exceptions should result (similar to C-code) when doing the
# addition - any  unsigned overflow should just be ignnored.

# Your key task is to write some MIPS assembly language to add together the
# data values given and put the answer into the  last memory location. 
# 
# You should write your assembly language below the comment line saying:
# "WRITE ASSEMBLY LANGUAGE SOLUTION BELOW".

.data

vals:

# Number of data values to add together as a unsigned halfword.
.half 3

# The actual data values themselves as "16-bit unsigned values".
.half 0x0010, 0x0010, 0x0010

# Memory address to put the sum into.  The result should be stored as a unsigned halfword.
# In this case the assembly language should put  0x00F0 onto this memory location.
# However the code should work in general for any given lists of data values.
.space 2


########## WRITE ASSEMBLY LANGUAGE SOLUTION BELOW ##########
   
.text
.globl main
main:
	la  $4, vals	# Load $4 with the address of label 'vals'.
	addu $8, $0, $0	# Zeroing sum
	addu $10, $0, $0 #Zeroing loop counter
	lhu $11, 0($4)   #iterations
	
loop:
    beq $10,$11,exit
	lhu  $9, 2($4)	# Get first number from memory
	addu $8, $8, $9  # Add to sum
	addu $4,$4,2
	addu $10,$10,1
	j loop
        
exit:
    sh  $8, 2($4)   # Save the result to memory.
	li $v0 10       # Exit program using system call 10.
	syscall         # syscall 10 (exit)
