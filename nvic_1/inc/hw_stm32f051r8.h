
#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__


#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

#define write_reg_8(addr, value)    *((char *)(addr)) = value
#define read_reg_8(addr, mask)      *((char *)(addr)) & (mask)

/* RCC - clock */
#define BASE_ADDR_RCC		0x40021000u
#define RCC_APB2ENR			*((unsigned int *)(BASE_ADDR_RCC + 0x18u))
	/*ENABEL CLOCK*/
#define RCC_APB2ENR_ENABEL_CLOCK_PORTA	(RCC_APB2ENR |= 1<<2)
#define RCC_APB2ENR_ENABEL_CLOCK_PORTB	(RCC_APB2ENR |= 1<<3)
#define RCC_APB2ENR_ENABEL_CLOCK_PORTC	(RCC_APB2ENR |= 1<<4)
#define RCC_APB2ENR_ENABEL_CLOCK_PORTD	(RCC_APB2ENR |= 1<<5)
#define RCC_APB2ENR_ENABEL_CLOCK_PORTE	(RCC_APB2ENR |= 1<<6)
#define RCC_APB2ENR_ENABEL_CLOCK_PORTF	(RCC_APB2ENR |= 1<<7)
#define RCC_APB2ENR_ENABEL_CLOCK_PORTG	(RCC_APB2ENR |= 1<<8)
/* GPIO_CRH */

	/*GPIO_CRH_SET_CNF*/
		/*GPIO_CRH_SET_CNF_INPUT_MODE*/
#define GPIO_CNF_INPUT_ANALOG		0x00u
#define GPIO_CNF_INPUT				0x01u
#define GPIO_CNF_INTPUT_PP			0x02u
#define GPIO_CNF_RESERVER			0x03u

		/*GPIO_CRH_SET_CNF_OUTPUT_MODE*/
#define GPIO_CNF_OUTPUT_PP			0x00u
#define GPIO_CNF_OUTPUT_OD			0x01u
#define GPIO_CNF_ALT_OUTPUT_PP		0x02u
#define GPIO_CNF_ALT_OUTPUT_OD		0x03u

	/*GPIO_CRH_SET_MODE*/
#define GPIO_MODER_INPUT			0x00u
#define GPIO_MODER_OUTPUT_10Mhz		0x01u
#define GPIO_MODER_OUTPUT_2Mhz		0x02u
#define GPIO_MODER_OUTPUT_50Mhz		0x03u

#define GPIO_CRL_MODE(pin)	(4*(pin))
#define GPIO_CRL_CNF(pin)	((4*(pin))+2)

#define ADDR_GPIO					0x40010800u

#define GPIO_CRL(port)		*((unsigned int *)(ADDR_GPIO + (port)*0x400 + 0x00u))
#define GPIO_CRH(port)		*((unsigned int *)(ADDR_GPIO + (port)*0x400 + 0x04u))
#define GPIO_IDR(port)		*((unsigned int *)(ADDR_GPIO + (port)*0x400 + 0x08u))
#define GPIO_ODR(port)		*((unsigned int *)(ADDR_GPIO + (port)*0x400 + 0x0Cu))
#define GPIO_BSRR(port)		*((unsigned int *)(ADDR_GPIO + (port)*0x400 + 0x10u))

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

/*EXTI*/
#define BASE_ADDR_EXTI 				0x40010400u
#define EXTI_IMR					(BASE_ADDR_EXTI + 0x00u)
#define EXTI_RTSR					(BASE_ADDR_EXTI + 0x08u)
#define EXTI_PR						(BASE_ADDR_EXTI + 0x14u)

/*AFIO*/
#define BASE_ADDR_AFIO				0x40010000u
#define AFIO_EXTICR4				(BASE_ADDR_AFIO + 0x14u)

/* NVIC*/
#define NVIC_ISER(num)				(0xE000E100u + (num * 0x04u))
#define NVIC_ICER(num)				(0XE000E180u + (num * 0x04u))			
#define	NVIC_ISPR(num)				(0XE000E200u + (num * 0x04u))
#define NVIC_ICPR(num)				(0XE000E280u + (num * 0x04u))
#define NVIC_IABR(num)				(0xE000E300u + (num * 0x04u))
#define NVIC_IPR(num)				(0xE000E100u + (num)) 

/* end file */
#endif /* __HW_STM32F051R8_H__ */

