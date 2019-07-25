/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

//extern int Init_Thread(void);

/*
 * main: initialize and start the system
 */
 
 osThreadId main_id;
 osThreadId Thread1_id;
 osThreadId Thread2_id;
 osThreadId Thread3_id;
 
 
 void Thread1(void const *argument)
 {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
   
    GPIO_InitTypeDef   led13;
    led13.GPIO_Mode=GPIO_Mode_OUT;
    led13.GPIO_OType=GPIO_OType_PP;
    led13.GPIO_Pin=GPIO_Pin_13;
    led13.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&led13);
   while(1)
   {
     GPIO_SetBits(GPIOD,GPIO_Pin_13);
     osDelay(100);
     GPIO_ResetBits(GPIOD,GPIO_Pin_13);
     osDelay(100);
   }
    
 }
 void Thread2(void const *argument)
 {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
   
    GPIO_InitTypeDef   led14;
    led14.GPIO_Mode=GPIO_Mode_OUT;
    led14.GPIO_OType=GPIO_OType_PP;
    led14.GPIO_Pin=GPIO_Pin_14;
    led14.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&led14);
   while(1)
   {
     GPIO_SetBits(GPIOD,GPIO_Pin_14);
     osDelay(500);
     GPIO_ResetBits(GPIOD,GPIO_Pin_14);
     osDelay(500);
   }
    
 }
  void Thread3(void const *argument)
 {

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
   
    GPIO_InitTypeDef   led12;
    led12.GPIO_Mode=GPIO_Mode_OUT;
    led12.GPIO_OType=GPIO_OType_PP;
    led12.GPIO_Pin=GPIO_Pin_12;
    led12.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&led12);
   
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
    
    GPIO_InitTypeDef buton;
   	buton.GPIO_Pin  = GPIO_Pin_0;
    buton.GPIO_Mode = GPIO_Mode_IN;
    buton.GPIO_Speed = GPIO_Speed_100MHz;
    buton.GPIO_OType = GPIO_OType_PP;
    buton.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOA, &buton);
   
    uint8_t buton_okunan ;
   
   while(1)
   {
      buton_okunan = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
     if(buton_okunan == 1)
     {
       GPIO_SetBits(GPIOD,GPIO_Pin_12);
     }
     else if(buton_okunan== 0 )
     {
      GPIO_ResetBits(GPIOD,GPIO_Pin_12);
     }
   }
    
 }
 osThreadDef(Thread1,osPriorityNormal,1,0);
 osThreadDef(Thread2,osPriorityNormal,1,0);
 osThreadDef(Thread3,osPriorityNormal,1,0);
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
   
    GPIO_InitTypeDef   led15;
    led15.GPIO_Mode=GPIO_Mode_OUT;
    led15.GPIO_OType=GPIO_OType_PP;
    led15.GPIO_Pin=GPIO_Pin_15;
    led15.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&led15);
    GPIO_SetBits(GPIOD,GPIO_Pin_15);
  // initialize peripherals here
//Init_Thread();
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);

  Thread1_id = osThreadCreate(osThread(Thread1), NULL);
  Thread2_id = osThreadCreate(osThread(Thread2), NULL);
  Thread3_id = osThreadCreate(osThread(Thread3), NULL);
  
  
  osKernelStart ();                         // start thread execution 
  
  
    while(1)
   {
     GPIO_SetBits(GPIOD,GPIO_Pin_15);
     osDelay(1000);
     GPIO_ResetBits(GPIOD,GPIO_Pin_15);
     osDelay(1000);
   }
  
}
