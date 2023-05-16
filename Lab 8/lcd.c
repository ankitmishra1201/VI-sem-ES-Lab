#include <lpc17xx.h>
#define RS_CTRL  0x08000000
#define EN_CTRL  0x10000000
#define DT_CTRL  0x07800000

unsigned long int temp1 = 0, temp2 = 0, i, j, k, flag, row, col;
unsigned char flag1 = 0, flag2 = 0;
unsigned char msg[] = {"MITn 01manipal"};

void delay_lcd(unsigned int r1){
	unsigned int r;
	for(r=0; r<r1; r++);
	return;
}

void port_write(void){
	LPC_GPIO0->FIOPIN = temp2;
	if(flag1 == 0) LPC_GPIO0->FIOCLR = RS_CTRL;
	else LPC_GPIO0->FIOSET = RS_CTRL;
	LPC_GPIO0->FIOSET = EN_CTRL;   	
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;
	delay_lcd(300000);
	return;
}

void lcd_write(void){
	flag2 =  (flag1 == 1)?0:((temp1 == 0x30)||(temp1 == 0x20))?1:0;
	temp2 = temp1 & 0xf0;
	temp2 = temp2 << 19;
	port_write();
	if(flag2==0){
		temp2 = temp1 & 0x0f;
		temp2 = temp2 << 23;
		port_write();
	}
}

unsigned long int init_command[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x06, 0x01, 0x80};

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_GPIO0->FIODIR = DT_CTRL | RS_CTRL | EN_CTRL;
	flag1 = 0;
	for(i=0; i<9;i++){
		temp1 = init_command[i];
		lcd_write();
	}
	flag1 = 1;
	i = 0;
	while(1){
		for(k = 0; k<4; k++){
			LPC_GPIO2->FIOPIN = 1<<(k+10);
			flag = 0;
			if(LPC_GPIO1->FIOPIN & 0xF<<23){
				flag = 1;
				switch(LPC_GPIO1->FIOPIN & 0xF<<23){
					case 1<<23:
						col = 0
						break;
					case 1<<24:
						col = 1;
						break;
					case 1<<25:
						col = 2;
						break;
					case 1<<26:
						col = 3;
						break;
					
				}
			}
	}
	while(msg[i] != '\0'){
		temp1 = msg[i];
		lcd_write();
		i+= 1;
		if(i==16){
			flag1 = 0;
			temp1 = 0xC0;
			lcd_write();
			flag1 = 1;
		}                 
	}
	while(1);
}