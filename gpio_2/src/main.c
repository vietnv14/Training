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
          asm("nop");
        }
    }
}

void enabled_clock_button()
{
	//Enabel clock for port A (PA4,5,6 = led1,2,3)
	RCC_APB2ENR_ENABEL_CLOCK_PORTA;

	//Enabel clock for button PB13,14,15 = button1,2,3
	RCC_APB2ENR_ENABEL_CLOCK_PORTB;
}

void Set_Mode_Pin_A()

{
	/*led PA*/
	unsigned int i;
	unsigned int tempreg;
	for(i = 4; i <= 6; i++)
	{
		/* set mode CRL */
		tempreg = read_reg(GPIO_CRL(PORTA), (~(0x3 << GPIO_CRL_MODE(i))));
		tempreg = write_reg(GPIO_CRL(PORTA), GPIO_MODER_OUTPUT_2Mhz << GPIO_CRL_MODE(i));
		/*set CRL_CNF*/ /*cho led*/
		tempreg = read_reg(GPIO_CRL(PORTA), (~(0x3 << GPIO_CRL_CNF(i))));
		tempreg = write_reg(GPIO_CRL(PORTA),  GPIO_CNF_OUTPUT_PP<< GPIO_CRL_CNF(i));
	} 	
}
void Set_Mode_Pin_B()

{
	/*button*/
	unsigned int i;
	unsigned int j = 3;
	unsigned int tempreg;
	for(i = 5; i <= 7; i++)
	{
		/* set mode CRH */
		tempreg = read_reg(GPIO_CRH(PORTB), (~(0x3 << GPIO_CRL_MODE(i))));
		tempreg = write_reg(GPIO_CRH(PORTB), GPIO_MODER_INPUT << GPIO_CRL_MODE(i));
		/*set CRL_CNF*/ /*cho button*/
		tempreg = read_reg(GPIO_CRH(PORTB), (~(0x3 << GPIO_CRL_CNF(i))));
		tempreg = write_reg(GPIO_CRH(PORTB),  GPIO_MODER_INPUT<< GPIO_CRL_CNF(i));
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
	unsigned int state_idr_red;
	unsigned int led_state = 0;
	enabled_clock_button();
	init_pin();
	//Init_Button();
	while(1)
	{

		/*polling*/
		state_idr_red = read_reg(GPIO_IDR(PORTB), 1 << 13);
		if ( 0 == state_idr_red) // neu khong chay thi thay 0 = 1 
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
		state_idr_red = read_reg(GPIO_IDR(PORTB), 1 << 14);
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
		}
		
		/*led_off();
		delay(50);
		led_on();
		delay(50);*/
	}
}
