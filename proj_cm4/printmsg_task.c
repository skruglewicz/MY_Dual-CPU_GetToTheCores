/******************************************************************************
* File Name: printmsg_task.c
*
* Description: This file contains the task that handles print message to the terminal.
*
*
*******************************************************************************


/*******************************************************************************
 * Header file includes
 ******************************************************************************/
#include "printmsg_task.h"
#include "cybsp.h"
#include "cyhal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "cycfg.h"
#include "cy_retarget_io.h"


/*******************************************************************************
* Global constants
*******************************************************************************/

/*******************************************************************************
 * Global variable
 ******************************************************************************/
/* Queue handle used for LED data */
QueueHandle_t print_command_data_q;


/*******************************************************************************
* Function Name: task_printmsg
********************************************************************************
* Summary:
*  Task that prints a message to the terminal
*
* Parameters:
*  string *param : Task parameter defined during task creation (unused)
*
* Uses a queue to receive messages.
*  message string is sent in the command
*
*
*******************************************************************************/
void task_printmsg(void* param)
{
   // cyhal_pwm_t pwm_led;
   // bool led_on = true;
    BaseType_t rtos_api_result;
    print_command_data_t print_cmd_data;
    cy_rslt_t result;

    /* Suppress warning for unused parameter */
    (void)param;

    /* Initialize the debug uart */
        result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                         CY_RETARGET_IO_BAUDRATE);

        /* Print opening message */
        /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
        printf("\x1b[2J\x1b[;H");
        printf("---------------------------------------------------------------------------\r\n");
        printf("Print Task has been Initialized. Waiting for message.\r\n");
        printf("---------------------------------------------------------------------------\r\n\n");


    /* Repeatedly running part of the task */
    for(;;)
    {
        /* Block until a command has been received over queue */
        rtos_api_result = xQueueReceive(print_command_data_q, &print_cmd_data,
                            portMAX_DELAY);

        /* Command has been received from queue */
        if(rtos_api_result == pdTRUE)
        {
            switch(print_cmd_data.command)
            {
                /* PRINT1 */
                case PRINT1:
                {
                	//NOT IMPLEMENTED
                    break;
                }
                /*PRINT2 */
                case PRINT2:
                {
                	//NOT IMPLEMENTED
                    break;
                }
                /*  PRINT_MESSAGE */
                case  PRINT_MESSAGE:
                {
                	//print message
                    printf("Message received: %s\r\n", print_cmd_data.message);

                    break;
                }
                /* Invalid command */
                default:
                {
                    /* Handle invalid command here */
                    break;
                }
            }
        }

        /* Task has timed out and received no data during an interval of
         * portMAXDELAY ticks.
         */
		else
		{
			/* Handle timeout here */
		}
    }
}


/* END OF FILE [] */
