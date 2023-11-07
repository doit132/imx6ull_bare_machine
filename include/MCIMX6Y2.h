#ifndef _MCIMX6Y2_H_
#define _MCIMX6Y2_H_

#include "core_ca7.h"
#include "cc.h"

/** GPIO - Register Layout Typedef */
struct GPIO_Type {
	/**< GPIO data register, offset: 0x0 */
	__IO uint32_t DR;
	/**< GPIO direction register, offset: 0x4 */
	__IO uint32_t GDIR;
	/**< GPIO pad status register, offset: 0x8 */
	__I uint32_t PSR;
	/**< GPIO interrupt configuration register1, offset: 0xC */
	__IO uint32_t ICR1;
	/**< GPIO interrupt configuration register2, offset: 0x10 */
	__IO uint32_t ICR2;
	/**< GPIO interrupt mask register, offset: 0x14 */
	__IO uint32_t IMR;
	/**< GPIO interrupt status register, offset: 0x18 */
	__IO uint32_t ISR;
	/**< GPIO edge select register, offset: 0x1C */
	__IO uint32_t EDGE_SEL;
};

/*根据 IMX6ULL 芯片手册<<55.15 UART Memory Map/Register Definition>>的 3608 页, 定义 UART 的结构体*/
struct UART_Type {
	/**< UART Receiver Register, offset: 0x0 串口接收寄存器, 偏移地址 0x0 */
	volatile unsigned int URXD;
	unsigned char RESERVED_0[60];
	/**< UART Transmitter Register, offset: 0x40 串口发送寄存器, 偏移地址 0x40*/
	volatile unsigned int UTXD;
	unsigned char RESERVED_1[60];
	/**< UART Control Register 1, offset: 0x80 串口控制寄存器 1, 偏移地址 0x80*/
	volatile unsigned int UCR1;
	/**< UART Control Register 2, offset: 0x84 串口控制寄存器 2, 偏移地址 0x84*/
	volatile unsigned int UCR2;
	/**< UART Control Register 3, offset: 0x88 串口控制寄存器 3, 偏移地址 0x88*/
	volatile unsigned int UCR3;
	/**< UART Control Register 4, offset: 0x8C 串口控制寄存器 4, 偏移地址 0x8C*/
	volatile unsigned int UCR4;
	/**< UART FIFO Control Register, offset: 0x90 串口 FIFO 控制寄存器, 偏移地址 0x90*/
	volatile unsigned int UFCR;
	/**< UART Status Register 1, offset: 0x94 串口状态寄存器 1, 偏移地址 0x94*/
	volatile unsigned int USR1;
	/**< UART Status Register 2, offset: 0x98 串口状态寄存器 2, 偏移地址 0x98*/
	volatile unsigned int USR2;
	/**< UART Escape Character Register, offset: 0x9C 串口转义字符寄存器, 偏移地址 0x9C*/
	volatile unsigned int UESC;
	/**< UART Escape Timer Register, offset: 0xA0 串口转义定时器寄存器 偏移地址 0xA0*/
	volatile unsigned int UTIM;
	/**< UART BRM Incremental Register, offset: 0xA4 串口二进制倍率增加寄存器 偏移地址 0xA4*/
	volatile unsigned int UBIR;
	/**< UART BRM Modulator Register, offset: 0xA8 串口二进制倍率调节寄存器 偏移地址 0xA8*/
	volatile unsigned int UBMR;
	/**< UART Baud Rate Count Register, offset: 0xAC 串口波特率计数寄存器 偏移地址 0xAC*/
	volatile unsigned int UBRC;
	/**< UART One Millisecond Register, offset: 0xB0 串口一毫秒寄存器 偏移地址 0xB0*/
	volatile unsigned int ONEMS;
	/**< UART Test Register, offset: 0xB4 串口测试寄存器偏移地址 0xB4*/
	volatile unsigned int UTS;
	/**< UART RS-485 Mode Control Register, offset: 0xB8 串口 485 模式控制寄存器 偏移地址 0xB8*/
	volatile unsigned int UMCR;
};

#endif
