.arm
.fpu vfp
.syntax unified
.align(4);

.macro FUNCTION name
    .section .text.\name
    .global \name
    .type \name, %function
    .align 4
\name:
.endm
FUNCTION LoadBottomUI
	STMFD   SP!, {R4,LR}
	CMP     R0, #6
	LDREQ   R4, =g_bottomUI
	LDREQ   R4, [R4]
	MOVNE   R4, R0
	LDR     R0, =g_bottomReturn
	LDR     PC, [R0]
