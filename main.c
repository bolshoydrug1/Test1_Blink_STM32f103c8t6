#include "stm32f10x.h"
#define SYSCLOCK 72000000U 
#define LED_C13_ON() GPIOC->BSRR |= GPIO_BSRR_BR13; 
#define LED_C13_OFF() GPIOC->BSRR |= GPIO_BSRR_BS13; 
//-----------------------
void PORTC_13_INIT(void);
void SysTick_Handler(void);
void SysTick_Init(void);
void delay_mS(uint32_t mS);
//-----------------------
__IO uint32_t SysTick_CNT = 0; 
//-----------------------
int main(void)
{
	PORTC_13_INIT();
	SysTick_Init();
	while(1)
	{
		
		LED_C13_ON() //low logic level on PC13 
		//for(int i = 0; i < 10000000; i++){}
		delay_mS(800);
		LED_C13_OFF() //high logic level on PC13
		//for(int i = 0; i < 10000000; i++){}
		delay_mS(200);
	}
}

void PORTC_13_INIT(void) //setting up the pin PC13
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; //setting up the pin timing
	
	GPIOC->CRH &=~ GPIO_CRH_MODE13;
	GPIOC->CRH |= GPIO_CRH_MODE13_1; //setting up the pin operation at a frequency of 2MHz
	GPIOC->CRH &=~ GPIO_CRH_CNF13; //setting up the pin operation in the mode push-pull
}

void SysTick_Init(void)
{
  SysTick->LOAD &= ~SysTick_LOAD_RELOAD_Msk; 
  SysTick->LOAD = SYSCLOCK/1000 - 1; 
  SysTick->VAL &= ~SysTick_VAL_CURRENT_Msk; 
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
  if(SysTick_CNT > 0)  SysTick_CNT--;
}

void delay_mS(uint32_t mS)
{
  SysTick->VAL &= ~SysTick_VAL_CURRENT_Msk;
  SysTick->VAL = SYSCLOCK / 1000 - 1; 
  SysTick_CNT = mS;
  while(SysTick_CNT) {}
}


