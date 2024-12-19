/* Where is the green LED connected?
*  User LD2: the green LED is a user LED connected to signal D13
*  corresponding to STM32 I/O PA5 (pin 21) or PB13 (pin 34) depending on the STM32 target
*  Port : A [GPIOA]
*  Pin  : 5 [MODER5]
*/

#define PIN5			(1UL<<5)
#define LED_PIN			PIN5

/* Memory map and register boundary addresses -
*  512-Mbyte, Block 2, Peripherals: 0x4000 0000 to 0x5FFF FFFF
*/
#define PERIPH_BASE		(0x40000000UL)
// AHB1: 0x4002 0000 to 0x4007 FFFF
#define AHB1PERIPH_OFFSET	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)

// STM32F446RE register boundary addresses - GPIOA: 0x4002 0000 to 0x4002 03FF
#define GPIOA_OFFSET		(0x00000000UL)
#define GPIOA_BASE		(AHB1PERIPH_BASE + GPIOA_OFFSET)

// STM32F446RE register boundary addresses - RCC: 0x4002 3800 to 0x4002 3BFF
#define RCC_OFFSET		(0x00003800UL)
#define RCC_BASE		(AHB1PERIPH_BASE + RCC_OFFSET)

// RCC AHB1 peripheral clock enable register - Address offset: 0x30
#define RCC_AHB1ENR_OFFSET	(0x00000030UL)
#define RCC_AHB1ENR		(*(volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))

// GPIOA port mode register - Address offset: 0x00
#define GPIOA_MODER_OFFSET	(0x00000000UL)
#define GPIOA_MODER		(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_MODER_OFFSET))

// GPIOA port output data register - Address offset: 0x14
#define GPIOA_ODR_OFFSET	(0x00000014UL)
#define GPIOA_ODR		(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_ODR_OFFSET))

/* RCC AHB1 peripheral clock enable register - GPIOA
*  Bit 0 GPIOAEN: IO port A clock enable
*    This bit is set and cleared by software.
*      0: IO port A clock disabled
*      1: IO port A clock enabled
*/
#define GPIOAEN			(0x00000001UL<<0)	// 0b 0000 0000 0000 0000 0000 0000 0000 0001

/* To set GPIOA_MODER[MODER5[1:0] to "General purpose output mode", use this logic:
* (1UL<<10)	// Set bit 10 to 1
* &= ~(1U<<11)	// Set bit 11 to 0
*/

int main(void)
{
	// 1. Enable clock access to GPIOA
	RCC_AHB1ENR |= GPIOAEN;
	// 2. Set PA5 as output pin
	GPIOA_MODER |= (1UL<<10);
	GPIOA_MODER &= ~(1UL<<11);

	// 3. Set PA5 high
	while(1)
	{
		GPIOA_ODR |= LED_PIN;
	}
}
