#include <stdint.h>

#define RCC_BASE  0x40021000UL
#define GPIOA_BASE 0x40010800UL

#define RCC_APB2ENR (*((volatile uint32_t *)(RCC_BASE + 0x18)))
#define GPIOA_CRL (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))
#define GPIOA_IDR (*((volatile uint32_t *)(GPIOA_BASE + 0x08)))

int main(void) {
	int led_state = 0;
	int last_btn_state = 1;
	int current_state;
	/*Bat clock GPIOA*/
	RCC_APB2ENR |= (1 << 2);

	/*PA0 = output LED*/
	GPIOA_CRL &= ~ (0xF <<0);
	GPIOA_CRL |= (0x2 << 0);

	/*PA1 = input pull up (NUT BAM)*/
	GPIOA_CRL &= ~(0xF <<4);
	GPIOA_CRL |= (0x8 <<4);
	GPIOA_ODR |= (1 <<1);

	while(1) {

		if (GPIOA_IDR & (1 <<1)) {
			current_state = 1; /* chân đang mức high*/
			} else {
				current_state = 0; /* chan dang muc 0*/
			}

		if (current_state == 0 && last_btn_state == 1) {
			led_state = 1 - led_state; // đảo trạng thái

			for(int i = 0; i < 50000; i++);
		}
		last_btn_state = current_state;

		if (led_state == 1) {
			GPIOA_ODR |= (1 << 0);
		} else {
			GPIOA_ODR &= ~(1 <<0);
		}
	}
	}
