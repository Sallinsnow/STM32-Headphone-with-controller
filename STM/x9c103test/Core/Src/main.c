/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define LONG_PRESS_THRESHOLD 2000   // long
#define COUNT_INTERVAL 500	// interval
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//GPIO_PIN_RESET 0 GPIO_PIN_SET 1
//PA0=KEY0  up
//PA1=KEY1  down
//PA2=KEY2  Silence=sc
//PA3=KEY3  micmode=mic
//PA4******
//PA5=inc HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//PA6=UD 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
//PA7=CS	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
//PA8=v1
//PA9=v2
//PA10=v3
//PB1*****
//PB2*****
//PB3
//PB4
//PB5=E2 4066 silence2
//PB6=E0 4066 silence1
//PB7=E1 4066 micmode
//PB8--PB15 a,b,c,d,e,f,g,h


int buttonPressStartTime = 0;
int count=0;
int buttonPressDuration=0;
int flagup=0,flagdown=0,flagsc=0,flagmic=0;
int flag=0;
int volume=3;
int volume_C=0;
int v1=1,v2=1,v3=1;
int inc=0,dec=0,sc=0;
//void contorl(){
//	//				v1 v2 v3
//	//stay		1  1  1
//	//silence	0  0  0
//	//++			0  1  0
//	//--			0  1  1

//	switch (v1 | v2 | v3) {
//        case 0b000://silence
//					
//            break;
//        case 0b010://++
//					
//            break;
//        case 0b011://--
//					
//            break;
//        default:
//					
//            break;
//    }

//}

//void silence(){
//				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
//				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
//				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);//light
//}

//void increase(){


//	
//}

//void decrease(){



//}

void x9c103_set(int number){
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); //	inc=1;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);	//	cs=0;
	HAL_Delay(10); 
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);	//	ud=0;
	HAL_Delay(10); 
	HAL_Delay(10);
	for(int i=0;i<100;i++){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);					//	inc=1;
		HAL_Delay(10); 
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);		//		inc=0;
		HAL_Delay(10); 
	}
	
		
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);		//	ud=1;
		HAL_Delay(10); 

	for(int i=0;i<number;i++){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);			//		inc=1;
		HAL_Delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);		//		inc=0;
		HAL_Delay(10);
	}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
		HAL_Delay(10);
		HAL_Delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);	  //	cs=1;
		HAL_Delay(10);
		HAL_Delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);	  //	ud=0;
		HAL_Delay(10);
		HAL_Delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
}

void x9c103_inc(int number){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);	//	cs=0;
	HAL_Delay(10); 
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);	  //	ud=1;
	HAL_Delay(10);
	HAL_Delay(10);


	for(int i=0;i<number;i++){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
		HAL_Delay(10); 
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);	//	inc=0;
		HAL_Delay(10); 
	} 

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);	  //	cs=1;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);	  //	ud=1;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
} 


void x9c103_dec(int number){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);	//	cs=0;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);	//	ud=0;
	HAL_Delay(10);
	HAL_Delay(10);
	
	for(int i=0;i<number;i++){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
		HAL_Delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);	//	inc=0;
		HAL_Delay(10); 
	}
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);	  //	cs=1;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);	  //	ud=0;
	HAL_Delay(10);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);		//	inc=1;

} 

void LED_C(){
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
} 
	
void LED(){
	 if(volume_C !=volume)
	 {
    volume_C=volume;
    switch(volume)
		{
	   case 0:
	  //13 12 10 9 8 14 
		 LED_C();
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_14, GPIO_PIN_SET);

		 break;
	   case 1:
		// 12  10
		 	 LED_C();
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_10, GPIO_PIN_SET);
		 
		 
		 break;
	   case 2:
		//13 12 15 8 9 
		 	 LED_C();
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);

		 
			
		 break;
	   case 3:
		//13 12 15 10 9
		 	 LED_C();
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_10|GPIO_PIN_9, GPIO_PIN_SET);

		 
		 break;
	   case 4:
		 //14 15 12 10	 
		 	 LED_C();
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_10, GPIO_PIN_SET);

		 
			
		 break;
	   case 5:
		 // 13 14 15 10 9 
		 	 LED_C();
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_10|GPIO_PIN_9, GPIO_PIN_SET);

		 
			
		 break;
	   case 6:
			//13 14 8 9 10 15 
		 	 LED_C();
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_15, GPIO_PIN_SET);

		 
			
		 break;
	   case 7:
			//13 12 10
		 	 LED_C();
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_10, GPIO_PIN_SET);
		 
			
		 break;
	 
		}
   }
}






void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	
	
	
	
	
	
	
	
	
	
/* ----------------------------------------------------------------*///control
	
//PA8=v1 mic 
//PA9=v2 low prefernce
//PA10=v3  high preference
//				v1 v2 v3
//stay		1  1  1
//silence	0  0  0
//++			0  1  0
//--			0  1  1
if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET){
//	HAL_Delay(10);
//		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET){
				if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET){
					if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET){
							//011 --
							dec=1;
					}
					else{
							//010 ++
						inc=1;
					}
				}
					else{
						//000 silence
						sc=1;
						}
//		}
	}
	/* ----------------------------------------------------------------*///key+++++
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET||inc == 1) //record start time
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET||inc == 1) 
		{	
			flag = 1;
			buttonPressStartTime = HAL_GetTick();
			if(inc == 1){
				inc = 0;
				return;
			} 
		}
	}
	
	
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET&&flag == 1)//calculate end time && flagup = 1
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) 
		{
			flag = 0;
			flagup = 1;
			buttonPressDuration = HAL_GetTick() - buttonPressStartTime;
		}
	}
/* ----------------------------------------------------------------*/////key------
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET||dec == 1) //record start time
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET||dec == 1) 
		{	
			flag = 2;
			buttonPressStartTime = HAL_GetTick();
			if(dec == 1){
				dec = 0;
				return;
			} 
		}
	}
	
	
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET&&flag == 2)//calculate end time 
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET) 
		{
			flag = 0;
			flagdown = 1;
			buttonPressDuration = HAL_GetTick() - buttonPressStartTime;
		}
	}
	
/* ----------------------------------------------------------------*////silence
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET||sc == 1) //record start time
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET||sc == 1) 
		{	
			flag = 3;
			buttonPressStartTime = HAL_GetTick();
			if(sc == 1){
				sc = 0;
				return;
			} 
		}
	}
	
	
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET&&flag == 3)//calculate end time 
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET) 
		{
			flag = 0;
			flagsc = 1;
			buttonPressDuration = HAL_GetTick() - buttonPressStartTime;
		}
	}
	
/* ----------------------------------------------------------------*///mic
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET) //record start time
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET) 
		{	
			flag = 4;
			buttonPressStartTime = HAL_GetTick();
		}
	}
	
	
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET&&flag == 4)//calculate end time
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET) 
		{
			flag = 0;
			flagmic = 1;
			buttonPressDuration = HAL_GetTick() - buttonPressStartTime;
		}
	}
	
}

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
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_Delay(500);
	x9c103_set(30);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);//keep light
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		LED();
		if(flagup == 1)
			{	
				flagup = 0;
				count = buttonPressDuration/1000;
				if(buttonPressDuration >= LONG_PRESS_THRESHOLD)//changan >= 2s
					{
						for(int i=0;i<count;i++)
						{
							
							if(volume<7){
								
								x9c103_inc(10);
								volume++;
							
							}
						}
					}
	
				else//duanan < 2s
					{
						
						if(volume<7){
							
							x9c103_inc(10);
							volume++;
						
						}
						
					}
//				if(volume>0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET){
//						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
//						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
//					}
				count=0;
			}
/*--------------------------------------------------------*/
			if(flagdown == 1)
			{	
				flagdown = 0;
				count = buttonPressDuration/1000;				
				if(buttonPressDuration >= LONG_PRESS_THRESHOLD)//changan >= 2s
					{
						for(int i=0;i<count;i++)
						{
							if(volume>0){
							
								x9c103_dec(10);
								volume--;
							
							}
						}
					}
	
				else//duanan < 2s
					{
						if(volume>0){
						
						x9c103_dec(10);
						volume--;
						
						}
						
					}
//				if(volume==0&&HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET){
//						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
//						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
//					}
				count=0;
			}
/*--------------------------------------------------------*/
			if(flagsc == 1)
			{	
				flagsc = 0;
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
				if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET){
					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);//light
				}
			
			}
/*--------------------------------------------------------*/
			if(flagmic == 1)
			{	
				flagmic = 0;
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			}
			
			
			
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
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB3 PB4 PB5
                           PB6 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
