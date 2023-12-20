.cpu cortex-m4
.syntax unified
.thumb
.section .text

.global _airos_switch_task
.extern pre_task
.extern cur_task

_airos_switch_task:
    cpsid I
    pop {r7}
    add sp, #0x4
    mrs r0, PSP
    cbz r0, _switch_to
    stmdb r0!, {r4-r11}
    vstmdb.32 r0!, {s0-s31}
    ldr r1, =pre_task
    ldr r1, [r1]
    str r0, [r1]
_switch_to:
    ldr r0, =cur_task
    ldr r0, [r0]
    ldr r1, [r0]
    vldmia.32 r1!, {s0-s31}
    ldmia r1!, {r4-r11}
    msr PSP, r1
    mov lr, 0xFFFFFFFD
    cpsie I
    bx lr
