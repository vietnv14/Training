#include "hw_stm32f051r8.h"

unsigned int led_state = 0;
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

void EXTI15_IRQHandler(void)
{
	unsigned int temp;
	/*Ngat cua PB15*/
	temp = read_reg (EXTI_PR, (1 << 15));
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
	}
	/*xoa co ngat*/
	temp = (1 << 15);
	write_reg(EXTI_PR, temp);
	write_reg(NVIC_ICPR(1), (1 << 40));
/*	state_idr_red = read_reg(GPIO_IDR(PORTB), 1 << 14);
	if ( 0 == state_idr_red)
	{
		if (0 == led_state)
		{
			led_on(5);
			delay(50);
			led_state = 1;
		}
		else
		{
			led_off(5);
			delay(50);
			led_state = 0;
		}
	}
	state_idr_red = read_reg(GPIO_IDR(PORTB), 1 << 15);
	if ( 0 == state_idr_red)
	{
		if (0 == led_state)
		{
			led_on(6);
			delay(50);
			led_state = 1;
		}
		else
		{
			led_off(6);
			delay(50);
			led_state = 0;
		}
	}*/	
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
}
void Set_Mode_Pin_A()

{
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
}
void Set_Mode_Pin_B()

{
	/*button*/
	unsigned int i;
	unsigned int j = 3;
	unsigned int temp_reg;
	for(i = 5; i <= 7; i++)
	{
		/* xoa du lieu hien tai */
		temp_reg = read_reg(GPIO_CRH(PORTB), (~(0x3 << GPIO_CRL_MODE(i))));
		temp_reg |= (GPIO_MODER_INPUT << GPIO_CRL_MODE(i));
		/* ghi du lieu moi vao */
		temp_reg = write_reg(GPIO_CRH(PORTB), temp_reg);
		// xoa du lieu hien tai 
		temp_reg = read_reg(GPIO_CRH(PORTB), (~(0x3 << GPIO_CRL_CNF(i))));
		temp_reg |= (GPIO_MODER_INPUT<< GPIO_CRL_CNF(i));
		temp_reg = write_reg(GPIO_CRH(PORTB), temp_reg);
		write_reg(GPIO_ODR(PORTB), 	1 << (i*2 + j)); //set pull up page 161 _ RM
		--j;
	} 	
}
void init_pin()
{	
	//set Mode for pin PA4, PA5, PA6
	Set_Mode_Pin_A();
	
	//Set bit for pin PA4, PA5, PA6
	//GPIO_BSRR(PORTA) |= 1<<4 | 1<<5 | 1<<6;
}
void init_interrupt()

{
	unsigned int tempreg;
	/*enable interrupt for EXTI15 - key3*/
	tempreg = read_reg(EXTI_IMR, ~(1 << 15));
	tempreg = tempreg | (1 << 15);
	write_reg(EXTI_IMR, tempreg);

	tempreg = read_reg(EXTI_RTSR, ~(1 << 15));
	tempreg = tempreg | (1 << 15);
	write_reg(EXTI_RTSR, tempreg);

	/*enable interrupt for EXTI14 - key2*/
	tempreg = read_reg(EXTI_IMR, ~(1 << 14));
	tempreg = tempreg | (1 << 14);
	write_reg(EXTI_IMR, tempreg);

	tempreg = read_reg(EXTI_RTSR, ~(1 << 14));
	tempreg = tempreg | (1 << 14);
	write_reg(EXTI_RTSR, tempreg);

	/*AFIO*/	
	tempreg = read_reg(AFIO_EXTICR4, ~(0x0F << 15));
	tempreg = tempreg | (0x01 << 12);
	write_reg(AFIO_EXTICR4, tempreg);

	/* NVIC*/
	tempreg = read_reg_8(NVIC_IPR(40), ~(0xFF << 0)); //set enabled_clock (page 133 Cortex_m3)
	tempreg = tempreg | (0x01 << 4);
	write_reg_8(NVIC_IPR(40), tempreg);

	tempreg = read_reg(NVIC_ISER(40/32), ~(1 << (40%32))); //
	tempreg = tempreg | (1 << 9);
	write_reg(NVIC_ISER(40/32), tempreg);
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

/*void Blink_led()
{
	//Reset pin
	//GPIO_BSRR(PORTA) |= 1<<20 | 1<<21 | 1<<22;
	unsigned short i, j;
	for(i = 20, j = 4; i <= 22; ++i)
	{
		if(!(GPIO_IDR(PORTB) & (1<<15)))
		{
			led_off();
			break;
		}
		//led on
		GPIO_BSRR(PORTA) |= 1<<i;
		delay(100);
		//led off
		GPIO_BSRR(PORTA) |= 1<<(j++);
		if(i == 22)
		{
			i = 19;
			j = 4;
		}
	}
}*/



void main(void)
{
	enabled_clock();
	init_pin();
	init_interrupt();
	//Init_Button();
	while(1)
	{	
		led_off();
		delay(50);
		led_on();
		delay(50);
	}
}
