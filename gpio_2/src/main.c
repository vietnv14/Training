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
/*void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm("nop");
        }
    }
}*/

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
	unsigned int state_idr_red;
	unsigned int led_state = 0;
	enabled_clock();
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
				//delay(50);
				led_state = 1;
			}
			else
			{
				led_off(4);
				//delay(50);
				led_state = 0;
			}
		}
		state_idr_red = read_reg(GPIO_IDR(PORTB), 1 << 14);
		if ( 0 == state_idr_red)
		{
			if (0 == led_state)
			{
				led_on(5);
				//delay(50);
				led_state = 1;
			}
			else
			{
				led_off(5);
				//delay(50);
				led_state = 0;
			}
		}
		state_idr_red = read_reg(GPIO_IDR(PORTB), 1 << 15);
		if ( 0 == state_idr_red)
		{
			if (0 == led_state)
			{
				led_on(6);
				//delay(50);
				led_state = 1;
			}
			else
			{
				led_off(6);
				//delay(50);
				led_state = 0;
			}
		}
		
		/*led_off();
		delay(50);
		led_on();
		delay(50);*/
	}
}
