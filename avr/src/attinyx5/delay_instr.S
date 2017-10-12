;;
; @file delay_instr.S

.global emb_delay_instr

.section .text

emb_delay_instr:
start:  sbiw r24,0x04 ; Subtract one loops worth of instructions (two clock cycles)
        brvc start    ; Loop back if we haven't underflowed (two clock cycles on branch)
        ret

.end