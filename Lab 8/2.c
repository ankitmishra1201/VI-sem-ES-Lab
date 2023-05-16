#include <lpc17xx.h>
#define RS_CTRL 0x08000000
#define EN_CTRL 0x10000000
#define DT_CTRL 0x07800000

unsigned long int flag1 = 0, flag2 = 0, i, flag = 0, row, col, x;
unsigned long int init_command[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x06, 0x01, 0x80};
unsigned char temp0 = 0, temp1 = 0;
unsigned char keyboard[4][4] = {{'0', '1', '2', '3'}, {'4', '5', '6', '7'}, {'8', '9', '+', '-'}, {'*', '/', 'C', 'R'}};

void delay_lcd(unsigned int y){
	unsigned int x;
	for(x = 0; x<y; x++);
	return;
}

void port_write(){
	LPC_GPIO0->FIOPIN = temp1;
	if(flag1 == 0) LPC_GPIO0->FIOCLR = RS_CTRL;
	else LPC_GPIO0->FIOSET = RS_CTRL;
	LPC_GPIO0->FIOSET = EN_CTRL;   	
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;
	delay_lcd(300000);
	return;
}

void lcd_write(){
	flag2 = (flag1==1)?0:((temp0==0x30)||(temp0==0x20))?1:0;
	temp1 = (temp0&0xF0)<<19;
	port_write();
	if(flag2==0){
		temp1 = temp0&0x0F;
		temp1 = temp1<<23;
		port_write();
	}
}

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_GPIO0->FIODIR = DT_CTRL | RS_CTRL | EN_CTRL;
	LPC_GPIO2->FIODIR = 0xF<<10;
	flag1 = 0;
	for(i = 0; i<9; i++){
		temp0 = init_command[i];
		lcd_write();
	}
	while(1){
		for(i = 0; i<4; i++){
			LPC_GPIO2->FIOPIN = 1<<(10+i);
			row = i;
			x = LPC_GPIO1->FIOPIN&(0xF<<23);
			switch(x){
				case 1<<23:
					flag = 1;
					col = 0;
					break;
				case 1<<24:
					flag = 1;
					col = 1;
					break;
				case 1<<25:
					flag = 1;
					col = 2;
					break;
				case 1<<26:
					flag = 1;
					col = 3;
					break;
			}
			if(flag==1){
				flag = 0;
				temp0 = keyboard[row][col];
				flag1 = 1;
				lcd_write();
				break;
			}
		}
	}
}