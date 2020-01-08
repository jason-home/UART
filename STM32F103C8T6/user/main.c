#include "stm32f10x.h"
#include <stdio.h>

int i;
volatile unsigned char TXT;
volatile unsigned char usart_flag=0;
/*int fputc(int ch,FILE *f)
{
		while(1)
	 {
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	
	for(i=0; i<5002; i++)
	{
		if(i==5000)
		{	
			USART_SendData(USART1,(uint8_t) ch);
		}
  }
	
	USART_SendData(USART1,(uint8_t) ch);
	return ch;
	
		}
}
void USART(void);

int main(void)
{
	  USART();
		printf("hello world");
		while(1)
		{}
		
}
*/

void NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //TIM2 IRQ Channel
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//Preemption Priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //Sub Priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

int main(void)
{
    /******** ?? USART?GPIO ??? ********/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /******** ?? GPIOA?USART1 ? RCC ?? ********/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);

    /******** ?? PA9 ? Tx ?? ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    GPIO_Init(GPIOA, &GPIO_InitStructure); // ??? PA9

    /******** ?? PA10 ? Rx ?? ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure); // ??? PA10

    /******** USART ?????? ********/
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure); // ??? UART1
		USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE); // ?? USART1
		
		
		NVIC_Config();
		
    while(1){ 
				if(usart_flag){
        for(i = 0; i<500000; i++); 
        USART_SendData(USART1,TXT);
				usart_flag=0;
				}			
    }
}
