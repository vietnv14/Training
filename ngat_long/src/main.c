#include "hw_stm32f051r8.h"

void led_on(int pin);
void led_off(int pin);
void delay(unsigned int timeout);
/*************************************************************************************************/
void Reserved_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void EXTI15_IRQHandler(void) /*ID interrupt 40*/
{
	unsigned int temp;
	/*Ngat cua PB15*/
	/*temp = read_reg (EXTI_PR, (1 << 15));
	if (1 == temp)
	{
		if (0 == led_state)
		{
			led_on(4);
			delay(50);
			led_state = 1;
		}
		else
		{
			led_off(4);
			delay(50);
			led_state = 0;
		}
		led_on(4);
		delay(50);
		led_off(4);
		delay(50);
	}*/
	int i;
	for(i = 0; i < 2; i++)
	{
		led_on(4);
		delay(50);
		led_off(4);
		delay(50);
	}
	/*xoa co ngat*/
	temp = (1 << 15);
	write_reg(EXTI_PR, temp);
	write_reg(NVIC_ICPR(40/32), (1 << (40%32)));
}

void EXTI9_5_IRQHandler(void) /*EXTI8 - PA8 */ /*ID interrupt 23*/
{
	unsigned int temp;	
	int i;
	for(i = 0; i < 4; i++)
	{
		led_on(6);
		delay(50);
		led_off(6);
		delay(50);
	}
	/*xoa co ngat*/
	temp = (1 << 8);
	write_reg(EXTI_PR, temp);
	write_reg(NVIC_ICPR(23/32), (1 << (23%32 )));
}
/*************************************************************************************************/
void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm("nop");
        }
    }
}

void enabled_clock(void)
{
	unsigned int tempreg;
	/* set mode PORTA */
	tempreg = read_reg(RCC_APB2ENR, ~(1 << 2));
	tempreg = tempreg | (1 << 2);
	write_reg(RCC_APB2ENR, tempreg);
	/* set mode PORTB */
	tempreg = read_reg(RCC_APB2ENR, ~(1 << 3));
	tempreg = tempreg | (1 << 3);
	write_reg(RCC_APB2ENR, tempreg);
	/* set mode AFIO */
	tempreg = read_reg(RCC_APB2ENR, ~(1 << 0));
	tempreg = tempreg | (1 << 0);
	write_reg(RCC_APB2ENR, tempreg);

}

void init_pin()
{
	/*PORT A - Led*/
	unsigned int i;
	unsigned int temp_reg;
	for(i = 4; i <= 6; i++)
	{
		/* xoa du lieu hien tai */
		temp_reg = read_reg(GPIO_CRL(PORTA), (~(0x3 << GPIO_CRL_MODE(i))));
		temp_reg |= (GPIO_MODER_OUTPUT_2Mhz << GPIO_CRL_MODE(i));
		/* ghi du lieu moi vao */
		temp_reg = write_reg(GPIO_CRL(PORTA), temp_reg);
		// xoa du lieu hien tai 
		temp_reg = read_reg(GPIO_CRL(PORTA), (~(0x3 << GPIO_CRL_CNF(i))));
		temp_reg |=  (GPIO_CNF_OUTPUT_PP<< GPIO_CRL_CNF(i));
		temp_reg = write_reg(GPIO_CRL(PORTA), temp_reg);
	} 	
	
	led_off(4);
	led_off(5);
	led_off(6);
}
void init_Button()

{
	/*button*/
	unsigned int temp_reg;
	/* set mode button PB15*/
	temp_reg = read_reg(GPIO_CRH(PORTB), (~(0x3 << GPIO_CRL_MODE(7) )));
	temp_reg |= (GPIO_MODER_INPUT << GPIO_CRL_MODE(7));
	/* ghi du lieu moi vao */
	temp_reg = write_reg(GPIO_CRH(PORTB), temp_reg);
	/*set mode CNF - PB15*/
	temp_reg = read_reg(GPIO_CRH(PORTB), (~(0x3 << GPIO_CRL_CNF(7) )));
	temp_reg |= (GPIO_CNF_INTPUT_PP<< GPIO_CRL_CNF(7));
	temp_reg = write_reg(GPIO_CRH(PORTB), temp_reg);
	write_reg(GPIO_ODR(PORTB), 	1 << 15); //set pull up page 161 _ RM

	/* set mode button PA8*/
	temp_reg = read_reg(GPIO_CRH(PORTA), (~(0x3 << GPIO_CRL_MODE(0) )));
	temp_reg |= (GPIO_MODER_INPUT << GPIO_CRL_MODE(0));
	temp_reg = write_reg(GPIO_CRH(PORTA), temp_reg);	
	/*set mode CNF - PA8*/
	temp_reg = read_reg(GPIO_CRH(PORTA), (~(0x3 << GPIO_CRL_CNF(0) )));
	temp_reg |= (GPIO_CNF_INTPUT_PP<< GPIO_CRL_CNF(0));
	temp_reg = write_reg(GPIO_CRH(PORTA), temp_reg);
	write_reg(GPIO_ODR(PORTA), 	1 << 8); //set pull up page 161 _ RM

}

void init_interrupt()
{
	unsigned int tempreg;
	/*enable interrupt for EXTI15 - key3 - PB15*/
	tempreg = read_reg(EXTI_IMR, ~(1 << 15));
	tempreg = tempreg | (1 << 15);
	write_reg(EXTI_IMR, tempreg);

	tempreg = read_reg(EXTI_FTSR, ~(1 << 15));
	tempreg = tempreg | (1 << 15);
	write_reg(EXTI_FTSR, tempreg);

	/*enable interrupt for EXTI8 - key4 - PA8*/
	tempreg = read_reg(EXTI_IMR, ~(1 << 8));
	tempreg = tempreg | (1 << 8);
	write_reg(EXTI_IMR, tempreg);

	tempreg = read_reg(EXTI_FTSR, ~(1 << 8));
	tempreg = tempreg | (1 << 8);
	write_reg(EXTI_FTSR, tempreg);

	/*AFIO*/	
	/* set mode PB15*/
	tempreg = read_reg(AFIO_EXTICR4, ~(0x0F << 15));
	tempreg = tempreg | (0x01 << 12);
	write_reg(AFIO_EXTICR4, tempreg);	
	/* set mode PA8*/
	tempreg = read_reg(AFIO_EXTICR3, ~(0x0F << 0));
	tempreg = tempreg | (0x00 << 0);
	write_reg(AFIO_EXTICR3, tempreg);

	/* NVIC*/
		/* Enable NVIC */
		/* Enable NVIC for ID interrupt 40 - EXTI15_10*/
	tempreg = read_reg(NVIC_ISER(40/32), ~(1 << (40%32)));
	tempreg = tempreg | (1 << (40%32));
	write_reg(NVIC_ISER(40/32), tempreg);
		/* Enable NVIC for ID interrupt 23 - EXTI19_5*/
	tempreg = read_reg(NVIC_ISER(23/32), ~(1 << (23%32))); //
	tempreg = tempreg | (1 << (23%32));
	write_reg(NVIC_ISER(23/32), tempreg);
		/* Set priority*/
		/*button PB15 - EXTI15*/
	tempreg = read_reg_8(NVIC_IPR(40), 0xFF << 0); //set enabled_clock (page 133 Cortex_m3)
	tempreg = tempreg | (0x01 << 4); //set priority muc 1
	write_reg_8(NVIC_IPR(40), tempreg);
		/*button PA8 - EXTI8*/
	tempreg = read_reg_8(NVIC_IPR(23), 0xFF << 0); //set enabled_clock (page 133 Cortex_m3)
	tempreg = tempreg | (0x02 << 4); //set priority muc 2
	write_reg_8(NVIC_IPR(23), tempreg);

	/*Enable global interrupt*/
	asm("cpsie i");
}

void led_off(int pin)
{
	//Set pin again
	write_reg(GPIO_BSRR(PORTA), 1<<(pin));
}

void led_on(int pin)
{
	write_reg(GPIO_BSRR(PORTA), 1<<(pin + 16));
}

void main(void)
{
	enabled_clock();
	init_Button();
	init_pin();
	init_interrupt();
	while(1)
	{	
		led_off(5);
		delay(50);
		led_on(5);
		delay(50);
	}
}
