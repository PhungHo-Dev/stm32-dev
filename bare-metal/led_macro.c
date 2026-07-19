#include <stdint.h>

#define SET_BIT(reg, bit)   ((reg)  |= (1UL << (bit)))
#define CLEAR_BIT(reg, bit)   ((reg)  &= ~(1UL << (bit)))
#define TOGGLE_BIT(reg, bit)   ((reg)  ^= (1UL << (bit)))
#define READ_BIT(reg, bit)   ((reg)  & (1UL << (bit)))


#define RCC_BASE     0x40021000UL
#define GPIOA_BASE   0x40010800UL
#define RCC_APB2ENR  (*((volatile uint32_t *)(RCC_BASE   + 0x18)))
#define GPIOA_CRL    (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR    (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))

int main(void) {
    /* Bat clock GPIOA */
    SET_BIT(RCC_APB2ENR, 2);
	/*RCC_APB2ENR |= (1 << 2);*/

    /* Cau hinh PA0 la output 2MHz push-pull */
    CLEAR_BIT(GPIOA_CRL, 0);
    CLEAR_BIT(GPIOA_CRL, 1);
    CLEAR_BIT(GPIOA_CRL, 2);
    CLEAR_BIT(GPIOA_CRL, 3);
    /* GPIOA_CRL &= ~(0xF << 0);*/
    SET_BIT(GPIOA_CRL, 1);
    /*GPIOA_CRL |=  (0x2 << 0);*/

    for (;;) {
        int i = 0;
        SET_BIT(GPIOA_ODR, 0);
        /*GPIOA_ODR |=  (1 << 0);  /* bat LED */
        for (i = 0; i < 100000; i++) {}

        CLEAR_BIT(GPIOA_ODR, 0);
        /*GPIOA_ODR &= ~(1 << 0);  /* tat LED */
        for (i = 0; i < 100000; i++) {}
    }
}
