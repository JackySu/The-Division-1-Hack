extern aimbotFunc:PROC
extern lpRemain:QWORD

.code 
hkFunction proc

	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push rbp

	;create new stack frame
	mov rbp, rsp
	mov rdi, rsp

	;allocate address for local variables
	;sub rsp, 20h

	call aimbotFunc

	;restore the old stack frame
	mov rsp, rdi
	pop rbp

	;restore the registers
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax

	;stolen bytes
	;movss xmm0, dword ptr[r12+0000316Ch]

	;return
	jmp lpRemain
hkFunction endp

end