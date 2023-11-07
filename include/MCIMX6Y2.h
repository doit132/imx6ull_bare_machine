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

#endif
