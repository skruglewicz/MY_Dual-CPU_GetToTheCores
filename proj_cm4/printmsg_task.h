/******************************************************************************
* File Name: printmsg_task.h
*
* Description: This file is the public interface of printmsg.c source file
*
*
* *******************************************************************************
/*******************************************************************************
 * Include guard
 ******************************************************************************/
/*
#ifndef SOURCE_LED_TASK_H_
#define SOURCE_LED_TASK_H_
*/

/*******************************************************************************
 * Header file includes
 ******************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "string.h"


/*******************************************************************************
* Global constants
*******************************************************************************/
///* Allowed TCPWM compare value for maximum brightness */
//#define LED_MAX_BRIGHTNESS  (100u)
//
///* Allowed TCPWM compare value for minimum brightness*/
//#define LED_MIN_BRIGHTNESS  (2u)


/*******************************************************************************
 * Data structure and enumeration
 ******************************************************************************/
/* Available print commands */
typedef enum
{
    PRINT1,
    PRINT2,
    PRINT_MESSAGE,
} print_command_t;

/* Structure used for storing LED data */
typedef struct
{
	print_command_t command;
    char message[25];
} print_command_data_t;

/*******************************************************************************
 * Global variable
 ******************************************************************************/
extern QueueHandle_t print_command_data_q;

/*******************************************************************************
 * Function prototype
 ******************************************************************************/
void task_printmsg(void* param);

//#endif /* SOURCE_LED_TASK_H_ */


/* [] END OF FILE  */
