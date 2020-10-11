/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"



int main(void)
{
  /*
   *  DO NOT WRITE TO THE WHOLE REGISTER!!!
   *  Write to the bits, that are meant for change.
   */
   
  //Systick init
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(8000000);	

  /*
   * TASK - configure MCU peripherals so that button state can be read and LED will blink.
   * Button must be connected to the GPIO port A and its pin 3.
   * LED must be connected to the GPIO port A and its pin 4.
   *
   * In header file "assignment.h" define macros for MCU registers access and LED blink application.
   * Code in this file must use these macros for the peripherals setup.
   * Code of the LED blink application is already given so just the macros used in the application must be defined.
   */


  // =========== GPIO CONFIG ===========

  /* Enable clock for GPIO port A*/
  RCC_AHBENR_REG |= (uint32_t)(0x1 << 17);

  /* GPIOA pin 3 and 4 setup */
  //set pin 3 as input
  GPIOA_MODER_REG &= ~(uint32_t)(0x3 << 6);

  //set pin 4 as output
  GPIOA_MODER_REG &= ~(uint32_t)(0x3 << 8);
  GPIOA_MODER_REG |= (uint32_t)(0x1 << 8);

  //set push-pull output on pin 4
  GPIOA_OTYPER_REG &= ~(uint32_t)(0x1 << 4);

  //set low speed output on pin 4
  GPIOA_OSPEEDER_REG &= ~(uint32_t)(0x1 << 8);

  // set pull up for pin 3
  GPIOA_PUPDR_REG &= ~(uint32_t)(0x3 << 6);
  GPIOA_PUPDR_REG |= (uint32_t)(0x1 << 6);

  //set no pull for pin 4
  GPIOA_PUPDR_REG &= ~(uint32_t)(0x3 << 8);


  // =========== WHILE LOOP  ===========
  while (1)
  {
	  const uint8_t samples = 100;
	  if(edgeDetect(BUTTON_GET_STATE, samples) == FALL){
		  LED_TOGGLE;
	  }
  }// end of while

}//end  of main

/* USER CODE BEGIN 4 */

enum EDGE_TYPE edgeDetect(uint8_t pin_state, uint8_t samples){
	/* function will detect rising/falling edge
	* pin_state - GPIO_PIN VALUE
	* samples - size of input filter
	*
	* must be N samples of same value after GPIO_PIN change value,
	* to return RISE/FALL edge
	*/

	// static and global variables have default value 0 by C/C++ standard
	static uint8_t last_long_term_value;
	static uint8_t number_of_new_states;

	//OK
	if(pin_state != last_long_term_value)
		number_of_new_states++;
	else
		number_of_new_states = 0;

	//OK
	if(number_of_new_states >= samples){
		last_long_term_value = pin_state;
		number_of_new_states = 0;
		if(pin_state == 1){
			return RISE;
		}
		else if(pin_state == 0){
			return FALL;
		}
	}
	return NONE;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
