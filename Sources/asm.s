.arm
.align(4);
.section .rodata

.global APT_Hook
.type APT_Hook, %function
APT_Hook:
	LDR		R0, =g_homeBtnWasPressed;
	MOV		R1, #1
	STR		R1, [R0]
	LDR		LR, =g_aptHookReturnAddress;
	LDR		PC, [LR]
