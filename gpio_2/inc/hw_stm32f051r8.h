
#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__


#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

/* RCC - clock */
#define BASE_ADDR_RCC		0x40021000u
#define RCC_APB2ENR			((BASE_ADDR_RCC + 0x18u))	
/* GPIO_CRH */

	/*GPIO_CRH_SET_CNF*/
		/*GPIO_CRH_SET_CNF_INPUT_MODE*/
#define GPIO_CNF_INPUT_ANALOG		0x00u
#define GPIO_CNF_INPUT				0x01u
#define GPIO_CNF_INTPUT_PP			0x02u
#define GPIO_CNF_RESERVER			0x03u

		/*GPIO_CRH_SET_CNF_OUTPUT_MODE*/
#define GPIO_CNF_OUTPUT_PP		0x00u
#define GPIO_CNF_OUTPUT_OD		0x01u
#define GPIO_CNF_ALT_OUTPUT_PP	0x02u
#define GPIO_CNF_ALT_OUTPUT_OD	0x03u

	/*GPIO_CRH_SET_MODE*/
#define GPIO_MODER_INPUT		0x00u
#define GPIO_MODER_OUTPUT_10Mhz	0x01u
#define GPIO_MODER_OUTPUT_2Mhz	0x02u
#define GPIO_MODER_OUTPUT_50Mhz	0x03u

#define GPIO_CRL_MODE(pin)	(4*(pin))
#define GPIO_CRL_CNF(pin)	((4*(pin))+2)

#define ADDR_GPIO			0x40010800u

#define GPIO_CRL(port)		((ADDR_GPIO + (port)*0x400 + 0x00u))
#define GPIO_CRH(port)		((ADDR_GPIO + (port)*0x400 + 0x04u))
#define GPIO_IDR(port)		((ADDR_GPIO + (port)*0x400 + 0x08u))
#define GPIO_ODR(port)		((ADDR_GPIO + (port)*0x400 + 0x0Cu))
#define GPIO_BSRR(port)		((ADDR_GPIO + (port)*0x400 + 0x10u))

#define PORTA				0x00u
#define PORTB				0x01u
#define PORTC				0x02u
#define PORTD				0x03u
#define PORTE				0x04u

/*led 1,2,3 PA 4,5,6*/

#define led_1		4 
#define led_2		5 
#define led_3		6 

/*user button PB13,14,15*/
#define button_1		13 
#define button_2		14 
#define button_3		14 

/* end file */
#endif /* __HW_STM32F051R8_H__ */

