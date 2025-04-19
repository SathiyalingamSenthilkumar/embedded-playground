#include "nrf.h"

/* LED 1 on nRF52840-DK is connected to P0.13 */
#define LED_1_PIN 13

void SysTick_Handler(void) {
    /* Toggle the LED */
    NRF_P0->OUT ^= 1 << LED_1_PIN;
}

int main(void) {
    /* Initialize the GPIO for LED */
    NRF_P0->DIR |= 1 << LED_1_PIN;
    NRF_P0->OUTCLR = 1 << LED_1_PIN;

    /* Initialize SysTick */
    SysTick->LOAD = 0x00FFFFFF; /* Set Max reload value */
    SysTick->VAL = 0;           /* Clear value, as it's not initialized by HW */
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; /* Use Processor clock */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   /* Enable SysTick exception */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;    /* Enable counter */

    while (1);

    return 0;
}
