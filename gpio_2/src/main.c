#include "hw_stm32f051r8.h"
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

/*************************************************************************************************/
void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm(" nop");
        }
    }
}

void enabled_clock_button()
{
	//enable clock portA
	read_reg(RCC_APB2ENR, ~(1<<2));
	write_reg(RCC_APB2ENR, (1<<2));
}

void Set_Mode_Pin_A()
{
	unsigned int i;
	unsigned int temp_reg;
	for(i = 4; i <= 6; i++)
	{
		/* xoa du lieu hien tai */
		read_reg(GPIO_CRL(PORTA), ~(0x3 << 20)); //read_reg(GPIO_CRL(PORTA), ~(0x3 << GPIO_CRL_MODE(i)));
		/* ghi du lieu moi vao */
		write_reg(GPIO_CRL(PORTA), (1) << 21);
		// xoa du lieu hien tai 
		read_reg(GPIO_CRL(PORTA), ~(0x3 << 22)); //read_reg(GPIO_CRL(PORTA), ~(0x3 << GPIO_CRL_CNF(i)));
		write_reg(GPIO_CRL(PORTA), 1<< 23); //write_reg(GPIO_CRL(PORTA), (GPIO_CNF_OUTPUT_PP)<< GPIO_CRL_CNF(i));
	} 	
}

void init_pin()
{	
	//set Mode for pin PA4, PA5, PA6
	Set_Mode_Pin_A();
	
	//Set bit for pin PA4, PA5, PA6
	//GPIO_BSRR(PORTA) |= 1<<4 | 1<<5 | 1<<6;
}
void led_on()
{
	//Set pin again
	
	write_reg(GPIO_BSRR(PORTA), 1<<21); // Turn on led 3 = PA5
}
void led_off()
{
	//Set pin again
	write_reg(GPIO_BSRR(PORTA), 1<<5); // Turn off led 3 = PA5
}

void Blink_led()
{
	//Reset pin
	//GPIO_BSRR(PORTA) |= 1<<20 | 1<<21 | 1<<22;
	unsigned short i, j;
	for(i = 20, j = 4; i <= 22; ++i)
	{
		if(!(read_reg(GPIO_IDR(PORTB), (1<<15))))
		{
			led_off();
			break;
		}
		//led on
		write_reg(GPIO_BSRR(PORTA), 1<<i);
		delay(100);
		//led off
		write_reg(GPIO_BSRR(PORTA), 1<<(j++));
		if(i == 22)
		{
			i = 19;
			j = 4;
		}
	}
}

void Init_Button()
{
	//clear bit 28-31
	read_reg(GPIO_CRH(PORTB), (~(0x3 << 28 | 0x3 << 30 ))); //read_reg(GPIO_CRH(PORTB), (~(0x3 << GPIO_CRL_MODE(7) | 0x3 << GPIO_CRL_CNF(7) )));
	//set 1 bit 31 
	write_reg(GPIO_CRH(PORTB), 1<<31); //write_reg(GPIO_CRH(PORTB), GPIO_CNF_INTPUT_PP<<GPIO_CRL_CNF(7));
	write_reg(GPIO_ODR(PORTB), 1<<15);
}

void main(void)
{
	unsigned int tt;
	enabled_clock_button();
	init_pin();
	Init_Button();
	while(1)
	{
		tt = read_reg(GPIO_IDR(PORTB), 1<<15);
		if(tt)
		{
			Blink_led();
			//delay(200);
		}
	}
}
