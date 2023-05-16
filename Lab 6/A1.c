#include<LPC17xx.h>

int main(void){
	unsigned int i = 0;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 = 0x0;
	LPC_GPIO0->FIODIR = 0x10;
	while(1)
	LPC_GPIO0->FIOSET = 0x10;
}