	.data 
	.word
secCount:
	.text
	.word default
	.word option1
	.word option2
	.word option3
jt:	
	.global wdt_c_handler
wdt_c_handler:
	add #1, &secCount
	mov &playSong, r12
	cmp #3, r2
	jnc default
	add r12, r12
	mov jt(r12), r0

option3:
	mov &playSong, r12
	call #playSongOne
	jmp end

option1:
	mov &playSong, r12
	call #playSongTwo
	jmp end
	
option2:
	mov &playSong, r12
	call #playSongThree
	jmp end
	
default:
	mov #0, &playSong
end:
	pop r0
