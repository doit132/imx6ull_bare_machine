#include "uart.h"

void uart_init(void)
{
	volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA;
	volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA;
	volatile unsigned int *IOMUXC_UART1_RX_DATA_SELECT_INPUT;
	volatile unsigned int *CCM_CSCDR1;
	volatile unsigned int *CCM_CCGR5;
	struct UART_Type *uart1 = (struct UART_Type *)0x02020000;

	IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA = (volatile unsigned int *)(0x20E0084);
	IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA = (volatile unsigned int *)(0x20E0088);
	IOMUXC_UART1_RX_DATA_SELECT_INPUT = (volatile unsigned int *)(0x20E0624);
	CCM_CSCDR1 = (volatile unsigned int *)(0x020C4024);
	CCM_CCGR5 = (volatile unsigned int *)(0x020C407C);

	/*
	设置 uart 总时钟
	UART_CLK_ROOT = 80Mhz
	*/
	*CCM_CSCDR1 &= ~((1 << 6) | (0x3f));

	/*
	给 uart 提供时钟
	uart1_clk_enable
	*/
	*CCM_CCGR5 |= (3 << 24);

	/*配置引脚功能*/
	*IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA &= ~0xf;
	*IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA &= ~0xf;

	/* IMX6ULL 特殊的地方 */
	*IOMUXC_UART1_RX_DATA_SELECT_INPUT |= 3;

	/* 设置波特率
	 * 115200 = 80M/(16*(UBMR+1)/(UBIR+1))
	 * UBIR = 15
	 * 115200 = 80M/(UBMR+1)
	 * UBMR = 80, 000, 000/115200 = 694 - 1 = 693
	 * 真正的 baudrate = 80, 000, 000/694 = 115274
	 * 先设置 UBIR, 后设置 UBMR
	 */
	uart1->UFCR |= (5 << 7);
	uart1->UBIR = 15;
	uart1->UBMR = 693;

	/* 设置数据格式 */
	uart1->UCR2 |= (1 << 14) | (0 << 8) | (0 << 6) | (1 << 5) | (1 << 2) | (1 << 1);

	/* IMX6ULL 芯片要求必须设置 */
	uart1->UCR3 |= (1 << 2);

	/* 使能 UART */
	uart1->UCR1 |= (1 << 0);
}

int getchar(void)
{
	struct UART_Type *uart1 = (struct UART_Type *)0x02020000;

	while ((uart1->USR2 & (1 << 0)) == 0)
		;
	return uart1->URXD;
}

int putchar(char c)
{
	struct UART_Type *uart1 = (struct UART_Type *)0x02020000;

	while ((uart1->USR2 & (1 << 3)) == 0)
		;
	uart1->UTXD = c;
	return c;
}
