.syntax unified
.cpu cortex-m3
.thumb

.extern _sbss
.extern _ebss
.section .isrVector, "a", %progbits
    .word _stack_top
    .word _resetHandler
    .zero 0x10

.global _resetHandler
.type _resetHandler, %function
_resetHandler:
    ldr r0, =_sbss
    ldr r1, =_ebss
    b .
