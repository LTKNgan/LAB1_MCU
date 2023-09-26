/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  #define RED1_GREEN2 0
  #define RED1_YELLOW2 1
  #define GREEN1_RED2 2
  #define YELLOW1_RED2 3
  // 1 for top and bottom leds, 2 for 2-side leds

  int led_status = RED1_GREEN2;
  int count = 3;

  int light = 5;

  while (1)
  {
	  if (count <= 0)
	  {
		  switch (led_status)
		  {
		  case RED1_GREEN2:
			  // turn off green led 2 and turn on yellow led 2
	  		  HAL_GPIO_TogglePin(GREEN_SIDE_GPIO_Port, GREEN_SIDE_Pin);
	  		  HAL_GPIO_TogglePin(YELLOW_SIDE_GPIO_Port, YELLOW_SIDE_Pin);
	  		  // LED 1 STILL IN RED
	  		  count = 2;				// set counter for yellow led 2
	  		  led_status = RED1_YELLOW2;
			  break;

		  case RED1_YELLOW2:
			  // turn off yellow led 2 and turn on red led 2
	  		  HAL_GPIO_TogglePin(YELLOW_SIDE_GPIO_Port, YELLOW_SIDE_Pin);
	  		  HAL_GPIO_TogglePin(RED_SIDE_GPIO_Port, RED_SIDE_Pin);
	  		  // turn off red led 1 and turn on green led 1
			  HAL_GPIO_TogglePin(RED_STR_GPIO_Port, RED_STR_Pin);
			  HAL_GPIO_TogglePin(GREEN_STR_GPIO_Port, GREEN_STR_Pin);
			  count = 3;				// set counter for green led 1
			  light = 3;
			  led_status = GREEN1_RED2;
			  break;

		  case GREEN1_RED2:
			  //turn off green led 1 and turn on yellow led 1
			  HAL_GPIO_TogglePin(GREEN_STR_GPIO_Port, GREEN_STR_Pin);
			  HAL_GPIO_TogglePin(YELLOW_STR_GPIO_Port, YELLOW_STR_Pin);
			  // LED 2 STILL IN RED
			  count = 2;				// set counter for yellow led 1
			  light = 2;
			  led_status = YELLOW1_RED2;
			  break;

		  case YELLOW1_RED2:
			  // turn off yellow led 1 and turn on green led 1
			  HAL_GPIO_TogglePin(YELLOW_STR_GPIO_Port, YELLOW_STR_Pin);
			  HAL_GPIO_TogglePin(RED_STR_GPIO_Port, RED_STR_Pin);
			  // turn off red led 2 and turn on green led 2
	  		  HAL_GPIO_TogglePin(RED_SIDE_GPIO_Port, RED_SIDE_Pin);
	  		  HAL_GPIO_TogglePin(GREEN_SIDE_GPIO_Port, GREEN_SIDE_Pin);
	  		  count = 3;				// set counter for green led 2
	  		  light = 5;
	  		  led_status = RED1_GREEN2;
	  		  break;

		  default:
			  break;
		  }
	  }
	  count--;
	  display7SEG(light);
	  light--;

	  HAL_Delay(1000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_STR_Pin|GREEN_SIDE_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, YELLOW_STR_Pin|GREEN_STR_Pin|RED_SIDE_Pin
                            |YELLOW_SIDE_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, sm1_a_Pin|sm1_b_Pin|sm1_c_Pin|sm1_d_Pin
                          |sm1_e_Pin|sm1_f_Pin|sm1_g_Pin, GPIO_PIN_SET);


  /*Configure GPIO pins : RED_STR_Pin YELLOW_STR_Pin GREEN_STR_Pin RED_SIDE_Pin
                           YELLOW_SIDE_Pin GREEN_SIDE_Pin */
  GPIO_InitStruct.Pin = RED_STR_Pin|YELLOW_STR_Pin|GREEN_STR_Pin|RED_SIDE_Pin
                          |YELLOW_SIDE_Pin|GREEN_SIDE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : sm1_a_Pin sm1_b_Pin sm1_c_Pin sm1_d_Pin
                           sm1_e_Pin sm1_f_Pin sm1_g_Pin */
  GPIO_InitStruct.Pin = sm1_a_Pin|sm1_b_Pin|sm1_c_Pin|sm1_d_Pin
                          |sm1_e_Pin|sm1_f_Pin|sm1_g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7SEG(int count)
{
	switch (count)
	{
	case 0:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_SET);
		break;

	case 1:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_SET);
		break;

	case 2:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_RESET);
		break;

	case 3:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_RESET);
		break;

	case 4:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_RESET);
		break;

	case 5:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_RESET);
		break;

	case 6:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_RESET);
		break;

	case 7:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_SET);
		break;

	case 8:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_RESET);
		break;

	case 9:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_RESET);
		break;

	default:
		HAL_GPIO_WritePin(sm1_a_GPIO_Port, sm1_a_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_b_GPIO_Port, sm1_b_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_c_GPIO_Port, sm1_c_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_d_GPIO_Port, sm1_d_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_e_GPIO_Port, sm1_e_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_f_GPIO_Port, sm1_f_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sm1_g_GPIO_Port, sm1_g_Pin, GPIO_PIN_SET);
		break;
	}
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
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
