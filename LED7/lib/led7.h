#ifndef _LED_7
#define _LED_7

#include "stm32f1xx_hal.h"
/*
 LED : LED7_GPIO &type
 */
static uint8_t seg_code[10]={
		0x3F, //0
		0x06, //1
		0x5B, //2
		0x4F, //3
		0x66, //4
		0x6D, //5
		0x7D, //6
		0x07, //7
		0x7F, //8
		0x6F, //9
};
typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
}LED7_GPIO_t;

typedef enum{
	LED_ANODE,
	LED_CATHODE,
}LED7_Type_t;
typedef struct{
	LED7_GPIO_t seg[7];
	LED7_Type_t type;
}LED7_Handle_t;

void LED7_Init(LED7_Handle_t *hLed, LED7_Type_t type,
		 LED7_GPIO_t seg_a,
		 LED7_GPIO_t seg_b,
		 LED7_GPIO_t seg_c,
		 LED7_GPIO_t seg_d,
		 LED7_GPIO_t seg_e,
		 LED7_GPIO_t seg_f,
		 LED7_GPIO_t seg_g);

void LED7_Display(LED7_Handle_t *hLed, uint8_t num);



#endif

