#include "stm32f4xx.h"                  // Device header
//USART2 connected to  (PD5/PD6)
// USART2 APB1 bit 17
// CR1 register to enable and disable Tx(bit 3)  and RX (bit 2)
// CR1 register to enable USART (bit 13 )
// configure PIN (PD5 and PD6) as USART pins GPIOD_AFRL=AF7


#define GPIOD_EN_CLK (1<<3)
#define USART2_CLK_EN (1<<17)
#define USART_TX_EN (1<<3)
#define USART_TX_DI (0<<3)
#define USART_RX_EN (1<<2)
#define USART_RX_DI (0<<2)
#define USART_EN (1<<13)
#define USART_PIN1 (1<<5)
#define USART_PIN2 (1<<6)
#define GPIO_D_MODE_5 (1<<11)
#define GPIO_D_MODE_6 (1<<13)

int USART2_INIT(void) ;
void USART_Write(char ch);
char USART_Read(void);

int main (void) 
{
  char c;
	USART2_INIT();
	while (1)
		
	{
	 
		c=USART_Read();
		USART_Write(c);
		USART_Write('\n');
		USART_Write('\r');
		
	}
	
}

int USART2_INIT(void) 
{
	RCC->AHB1ENR |= GPIOD_EN_CLK; // because USART is connected to PIN PD5 and PD6
	RCC->APB1ENR |= USART2_CLK_EN  ;
	GPIOD->AFR[0] |= 0x07700000;  // USART connected to PD5 and PD6
	GPIOD->MODER |=GPIO_D_MODE_5; // PIN PD5 alternate function mode
	GPIOD->MODER |=GPIO_D_MODE_6; // PIN PD6 alternate function mode
	USART2->CR1 |=USART_EN ;
	USART2->CR1 ^=USART_TX_EN;
	USART2->CR1 ^=USART_RX_EN;
	USART2->BRR = 0x0683; //9600
	
}

void USART_Write(char ch) // int
	
{ // wait while TX buffer is empty
	while(!(USART2->SR & 0x80)) {}
	USART2->DR = (ch & 0xFF);
}


char USART_Read(void)
	
{ 
	while(!(USART2->SR & 0x20)) {}  // wait while RX buffer is empty
	
  
	return USART2->DR ;
}
	
	

