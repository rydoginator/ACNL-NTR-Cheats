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

FUNCTION FixSaveFurn
    STMFD   SP!, {R0-R12,LR}   		@Store All Registers
    LDR   	R0, =g_FixSaveFurnAddr	@Set game address
    MOV		LR, PC					@Set return address (PC = (current instruction + 8) apparently)
    LDR     PC, [R0]				@Set PC to the game function. It stores LR so it will return to here+4
    LDMFD   SP!, {R0-R12,PC}   		@Restore All Registers