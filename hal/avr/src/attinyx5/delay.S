;;
; @file delay.S

.global junk_delay_cycles

.section .text

junk_delay_cycles:
        sbiw r24,0x10
        brcs end
start:  sbiw r24,0x04 ; Subtract one loops worth of instructions (two clock cycles)
        brcc start    ; Loop back if we haven't underflowed (two clock cycles on branch)
end:    ret

.end