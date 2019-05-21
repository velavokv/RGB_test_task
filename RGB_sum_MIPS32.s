.data
msg1: .asciiz "Input RGB1: "
msg2: .asciiz "Input RGB2: "
msg3: .asciiz "Output saturated sum RGB1 + RGB2: "

#RGB_in1     $t0
#RGB_in2     $t1
#or7b		     $t2
#and7b	     $t3
#RGB_sum     $t4
#mask_satrtd $t5
#sum_satrtd  $t6
#temp				 $t7
#0x007f7f7f  $a1
#0x08080808  $a2
#0xff        $a3

#temp2       $t8


.text 
.globl main

main:

li $a1, 0x007f7f7f
li $a2, 0x00808080
li $a3, 0x000000ff

#RGB_in1
li $v0, 4
la $a0, msg1
syscall
li $v0, 5
syscall
move $t0, $v0   #RGB_in1

#RGB_in2
li $v0, 4
la $a0, msg2
syscall
li $v0, 5
syscall
move $t1, $v0   #RGB_in2

#saturated sum
or  $t7,$t0,$t1  
and $t2,$t7,$a2 #or7b

and $t7,$t0,$t1 
and $t3,$t7,$a2 #and7b

and $t0,$t0,$a1 
and $t1,$t1,$a1 

addu $t4,$t0,$t1 #RGB_sum

and $t5,$t4,$a2
and $t5,$t5,$t2
or  $t5,$t5,$t3
srl $t5,$t5, 7   #mask_satrtd

mul $t6,$t5,$a3  #sum_satrtd

or  $t7,$t6,$t4
or  $t7,$t7,$t2  #RGB_out

#print 
li $v0, 4
la $a0, msg3
syscall

li $v0, 1
move $a0, $t7
syscall

li $v0, 10
syscall

