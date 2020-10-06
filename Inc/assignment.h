/*
 * assignment.h
 *
 *  Created on: 27. 9. 2020
 *      Author: Stancoj
 */

#ifndef ASSIGNMENT_H_
#define ASSIGNMENT_H_

/**
 * 		This header file provides macros to the MCU's registers required for this assignment.
 * 		Your task is to provide their actual implementation so you can use them in application in "main.c"
 * 		and make your "LED blink" application code readable and great again!
 */

/* General purpose input output port A macros */
//GPIOA peripheral base address
#define	GPIOA_BASE_ADDR			((uint32_t)(0x48000000))
//MODER register
#define	GPIOA_MODER_REG			*((volatile uint32_t *)(GPIOA_BASE_ADDR))
//OTYPER register
#define	GPIOA_OTYPER_REG		*((volatile uint32_t *)(GPIOA_BASE_ADDR + 0x04U))
//OSPEEDER register
#define GPIOA_OSPEEDER_REG		*((volatile uint32_t *)(GPIOA_BASE_ADDR + 0x08U))
//PUPDR register
#define GPIOA_PUPDR_REG			*((volatile uint32_t *)(GPIOA_BASE_ADDR + 0x0CU))
//IDR register
#define GPIOA_IDR_REG			*((volatile uint32_t *)(GPIOA_BASE_ADDR + 0x10U))
//ODR register
#define GPIOA_ODR_REG			*((volatile uint32_t *)(GPIOA_BASE_ADDR + 0x14U))
//BSRR register
#define GPIOA_BSRR_REG			*((volatile uint32_t *)(GPIOA_BASE_ADDR + 0x18U))
//BRR register
#define GPIOA_BRR_REG			*((volatile uint32_t *)(GPIOA_BASE_ADDR + 0x28U))

/*Reset clock control register macros */
//RCC base address
#define	RCC_BASE_ADDR			((uint32_t)(0x40021000))
//AHBEN register
#define	RCC_AHBENR_REG			*((volatile uint32_t *)(RCC_BASE_ADDR + 0x14U))

/* button and LED macros */
#define BUTTON_GET_STATE		((GPIOA_IDR_REG & (uint32_t)(0x1 << 3)) >> 3)

#define LED_ON					(GPIOA_ODR_REG |= (uint32_t)(1 << 4))
#define LED_OFF					(GPIOA_ODR_REG &= ~(uint32_t)(1 << 4))
#define LED_SWITCH				(GPIOA_IDR_REG & (uint32_t)(0x1 << 4)) ? LED_OFF : LED_ON

/*
#define LED_ON					(GPIOA_BSRR_REG |= (uint32_t)(1 << 4))
#define LED_OFF					(GPIOA_BRR_REG |= (uint32_t)(1 << 4))
*/

enum EDGE_TYPE {NONE,RISE,FALL};

enum EDGE_TYPE edgeDetect(uint8_t pin_state, uint8_t samples);

#endif /* ASSIGNMENT_H_ */
