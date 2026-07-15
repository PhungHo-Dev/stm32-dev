#include "led7.h"
void LED7_Init(LED7_Handle_t *hLed, LED7_Type_t type,
		 LED7_GPIO_t seg_a,
		 LED7_GPIO_t seg_b,
		 LED7_GPIO_t seg_c,
		 LED7_GPIO_t seg_d,
		 LED7_GPIO_t seg_e,
		 LED7_GPIO_t seg_f,
		 LED7_GPIO_t seg_g){
	hLed-> type =type;
	hLed->seg[0]=seg_a;
	hLed->seg[1]=seg_b;
	hLed->seg[2]=seg_c;
	hLed->seg[3]=seg_d;
	hLed->seg[4]=seg_e;
	hLed->seg[5]=seg_f;
	hLed->seg[6]=seg_g;
}

void LED7_Display(LED7_Handle_t *hLed, uint8_t num){
	if(num>9){
		return ;
	}
	uint8_t data = seg_code[num];

	GPIO_PinState state;
	for (int i=0; i<7; i++){
		uint8_t bit = (data>>i)&(0x01);
		if(hLed->type == LED_ANODE){
			state = bit ? 0 : 1;
		}else {
			state = bit ? 1 : 0;
		}
		HAL_GPIO_WritePin(hLed->seg[i].port, hLed->seg[i].pin, state);
	}
}
