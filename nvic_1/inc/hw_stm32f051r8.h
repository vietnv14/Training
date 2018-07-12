#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__


#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

/* RCC - clock */
#define BASE_ADDR_RCC		0x40021000u
#define RCC_APB2ENR			(BASE_ADDR_RCC + 0x18u)


/* GPIO */
	/*PORT*/
#define PORTA				0
#define PORTB				1
#define PORTC				2
#define PORTD				3
#define PORTE				4
#define PORTF				5
#define PORTG				6
/*GPIO REGISTER*/
#define BASE_ADDR_GPIO		0x40010800u

#define GPIO_MODER(PORT)	(BASE_ADDR_GPIO + PORT*0x400u + 0x00u)
#define GPIO_IDR(PORT)		(BASE_ADDR_GPIO + PORT*0x400u + 0x08u)
#define GPIO_MODER_INPUT	0x00u
#define GPIO_MODER_OUTPUT	0x01u
#define GPIO_MODER_ALT		0x02u

#define GPIOA_PUPDR(PORT)	(BASE_ADDR_GPIO + PORT*0x400u + 0x0Cu)
#define GPIO_BSRR(PORT)		(BASE_ADDR_GPIO + PORT*0x400u + 0x18u)

#define GPIO_CRL(PORT) 		(BASE_ADDR_GPIO + PORT*0x400u + 0x00u) //Port configuration register low (GPIOx_CRL) (2;5;10MHz)
#define GPIO_CRH(PORT)		(BASE_ADDR_GPIO + PORT*0x400u + 0x04u)
#define GPIO_ODR(PORT)		(BASE_ADDR_GPIO + PORT*0x400u + 0x0Cu)
/* Led LD3 - PA5 */
#define LD3_PIN				15

/* user button (B1) - PB11 */
#define USER_BUTTON			11

/* EXTI */
#define BASE_ADDR_EXTI		0x40010400u
#define EXTI_IMR			(BASE_ADDR_EXTI + 0x00u)
#define EXTI_RTSR			(BASE_ADDR_EXTI + 0x08u)
#define EXTI_PR				(BASE_ADDR_EXTI + 0x14u)

/* AFIO */
#define BASE_ADDR_AFIO		0x40010000u
#define AFIO_EXTICR1		(BASE_ADDR_AFIO + 0x08u)

/* NVIC */
#define NVIC_ISER			0xE000E100u
#define NVIC_ICER			0xE000E180u
#define NVIC_ISPR			0xE000E200u
#define NVIC_ICPR			0xE000E280u
#define NVIC_PRI1			0xE000E404u

/* end file */
#endif /* __HW_STM32F051R8_H__ */

