.text
.global _start
_start:
    ldr sp, =(0x80000000+0x200000)
    bl main
