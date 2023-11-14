.text
.global _start
_start:
    // 之所以要设置栈, 是因为要用到C函数
    ldr sp, =(0x80000000+0x200000)

    adr r0, _start
	bl SystemInit

    /* 调用main函数 */
	bl main
