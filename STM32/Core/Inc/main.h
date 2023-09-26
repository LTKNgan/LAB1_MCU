/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define clk1_Pin GPIO_PIN_4
#define clk1_GPIO_Port GPIOA
#define clk2_Pin GPIO_PIN_5
#define clk2_GPIO_Port GPIOA
#define clk3_Pin GPIO_PIN_6
#define clk3_GPIO_Port GPIOA
#define clk4_Pin GPIO_PIN_7
#define clk4_GPIO_Port GPIOA
#define clk5_Pin GPIO_PIN_8
#define clk5_GPIO_Port GPIOA
#define clk6_Pin GPIO_PIN_9
#define clk6_GPIO_Port GPIOA
#define clk7_Pin GPIO_PIN_10
#define clk7_GPIO_Port GPIOA
#define clk8_Pin GPIO_PIN_11
#define clk8_GPIO_Port GPIOA
#define clk9_Pin GPIO_PIN_12
#define clk9_GPIO_Port GPIOA
#define clk10_Pin GPIO_PIN_13
#define clk10_GPIO_Port GPIOA
#define clk11_Pin GPIO_PIN_14
#define clk11_GPIO_Port GPIOA
#define clk0_Pin GPIO_PIN_15
#define clk0_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
