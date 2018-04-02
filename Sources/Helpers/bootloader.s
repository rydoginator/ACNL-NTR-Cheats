.arm
.align(4);
.section .text
.global _start
_start:
stmfd   sp!, {r0-r12, lr}
mrs     r0, cpsr
stmfd   sp!, {r0}

ldr     r6, =_start
adr     r5, _start
sub     r5, r5, r6      /* r5 = realAddress - baseAddress */
ldr     r6, = __rel_dyn_start
ldr     r7, = __rel_dyn_end
add     r6, r6, r5
add     r7, r7, r5
relocNotFinished:
ldmia   r6!, {r3, r4}
cmp     r4, #0x17
bne     notRelativeEntry
add     r3, r3, r5
ldr     r4, [r3]
add     r4, r4, r5
str     r4, [r3]
notRelativeEntry:
cmp     r6, r7
bcc     relocNotFinished
ldr     r0, =0xffff8001
adr     r1, _start
ldr     r2, =__rel_dyn_end
sub     r2, r2, r1      /* r2 = codesize */
svc     0x54            /* flush instruction cache */
nop
nop

skip:
@ Clear the BSS section
ldr     r0, = __c_bss_start
ldr     r1, = __c_bss_end
sub     r1, r1, r0
bl      ClearMem

bl      LaunchMainThread

ldmfd	sp!, {r0}
msr		cpsr, r0
ldmfd	sp!, {r0-r12, pc}
bx      lr

@---------------------------------------------------------------------------------
@ Clear memory to 0x00 if length != 0
@  r0 = Start Address
@  r1 = Length
@---------------------------------------------------------------------------------
ClearMem:
@---------------------------------------------------------------------------------
    mov  r2, #3     @ Round down to nearest word boundary
    add  r1, r1, r2 @ Shouldnt be needed
    bics r1, r1, r2 @ Clear 2 LSB (and set Z)
    bxeq lr         @ Quit if copy size is 0

    mov r2, #0
ClrLoop:
    stmia r0!, {r2}
    subs  r1, r1, #4
    bne   ClrLoop
    bx lr

.section .__rel_dyn_start
__rel_dyn_start:

.section .__rel_dyn_end
__rel_dyn_end:

.section .__bss_start
.global __c_bss_start
__c_bss_start:

.section .__bss_end
.global __c_bss_end
__c_bss_end:
