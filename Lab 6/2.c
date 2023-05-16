#include<LPC17xx.h>

unsigned int i = 0;
unsigned int j = 0;
unsigned long k = 0;

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 = 0x0;
	LPC_GPIO0->FIODIR = 0xFF;
	LPC_PINCON->PINSEL4 = 0x0;
	LPC_GPIO2->FIODIR = 0x0;
	LPC_GPIO2->FIOPIN = 0x0;
	while(1){
		k = LPC_GPIO2->FIOPIN;
		k = k>>12;
		//k = 0;
		if(k==3){
			for(i = 0; i<256; i++){
				k = LPC_GPIO2->FIOPIN;
				k = k>>12;
				if(k!=3) break;
				LPC_GPIO0->FIOCLR = 0xFF;
				LPC_GPIO0->FIOSET = i;
				for(j = 0; j<10000; j++);
			}
		}
		else if(k==2){
			for(i = 255; i>=0; i--){
				k = LPC_GPIO2->FIOPIN;
				k = k>>12;
				if(k==3) break;
				LPC_GPIO0->FIOCLR = 0xFF;
				LPC_GPIO0->FIOSET = i;
				for(j = 0; j<10000; j++);
			}
		}
	}
}