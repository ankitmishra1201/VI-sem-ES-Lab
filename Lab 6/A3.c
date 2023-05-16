#include<LPC17xx.h>

unsigned int i = 0;
unsigned int j = 0;

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 = 0x0;
	LPC_GPIO0->FIODIR = 0xFF;
	while(1){
		for(i = 0; i<8; i++){
			LPC_GPIO0->FIOCLR = 0xFF;
			LPC_GPIO0->FIOSET = 0x1<<i;
			for(j = 0; j<10000; j++);
		}
	}
}