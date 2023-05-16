#include<LPC17xx.h>

unsigned int i = 0;

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 = 0x0;
	LPC_GPIO0->FIODIR = 0xFF0;
	while(1){
		LPC_GPIO0->FIOSET = 0xFF0;
		for(i = 0; i<10000; i++);
		LPC_GPIO0->FIOCLR = 0xFF0;
		for(i = 0; i<10000; i++);
	}
}