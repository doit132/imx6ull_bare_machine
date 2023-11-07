#include "key.h"
#include "MCIMX6Y2.h"

__IO uint32_t *CCM_CCGR3 = (__IO uint32_t *)0x20C4074;
__IO uint32_t *IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B = (__IO uint32_t *)0x20E01B0;
__IO uint32_t *GPIO4_GDIR = (__IO uint32_t *)0x020A8004;
__IO uint32_t *GPIO4_DR = (__IO uint32_t *)0x020A8000;

void key_init(void)
{
	unsigned int val = 0;

	/* GPIO4_IO14 */
	/* a. 使能GPIO4
	 * set CCM to enable GPIO4
	 * CCM_CCGR3[CG15] 0x20C4074
	 * bit[13:12] = 0b11
	 */
	*CCM_CCGR3 |= (3 << 12);

	/* b. 设置 GPIO4_IO14 用于 GPIO
	 * set IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B
	 *      to configure GPIO4_IO14 as GPIO
	 * IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B  0x20E01B0
	 * bit[3:0] = 0b0101 alt5
	 */
	val &= ~(0xf);
	val |= (5);
	*IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B = val;

	/* c. 设置 GPIO4_IO14 作为 input 引脚
	 * set GPIO4_GDIR to configure GPIO4_IO14 as input
	 * GPIO4_GDIR  0x020A8000 + 0x0
	 * bit[3] = 0b1
	 */
	*GPIO4_GDIR &= ~(1 << 14);
}

uint8_t key_read()
{
	if (*GPIO4_DR & (1 << 14)) { // 释放
		return KEY_UP;
	} else {
		return KEY_DOWN;
	}
}
