#include<LPC17xx.h>

unsigned char seven_seg[10] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F};
unsigned int i, j;
unsigned long x, num = 0, n = 0, flag = 0, count;

void delay(){
	LPC_TIM0->TCR = 0x2;
	LPC_TIM0->MCR = 0x4;
	LPC_TIM0->CTCR = 0x0;
	LPC_TIM0->EMR = 0x20;
	LPC_TIM0->PR = 5;
	LPC_TIM0->MR0 = 1999999;
	LPC_TIM0->TCR = 0x1;
}

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 = 0x0;
	LPC_GPIO0->FIODIR = 0xFF0;
	LPC_PINCON->PINSEL3 = 0x0;
	LPC_GPIO1->FIODIR = 0xF<<23;
	while(1){
		x = LPC_GPIO0->FIOPIN & 1<<21;
		n = num;
		if(flag==1){
			LPC_GPIO0->FIOPIN = 0;
			delay(); 
			while((LPC_TIM0->EMR & 0x1)==0);
			flag = 0;
			if(x==0) num = (num-1)%10000;
			else num = (num+1)%10000;
		}
		for(i = 0; i<4; i++){
			LPC_GPIO1->FIOPIN = i<<23;
			LPC_GPIO0->FIOPIN = seven_seg[n%10]<<4;
			n /= 10;
			for(j = 0; j<1000; j++);
		}
		if(count==1000){
			flag = 1;
			count = 0;
		}
		else count++;
	}
}