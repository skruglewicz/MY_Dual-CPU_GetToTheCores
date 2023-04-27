
/******************************************************************************
* File Name: main.c
*
* Description:
* This code uses the RTOS scheduler to run the 3 task
* cm4enpoint_task
* capsense_task
* printmsg_task
*
* the cm4enpoint_task -is the Pipe endpoint that runs on CM4 it sends message over a PIPE to CM0+
* the printmsg_task - Receive messages from the 2 task to print the message string to the terminal
* The Capsense task features two CapSense buttons. Button 0  Button 1
*
* This code example uses FreeRTOS. For documentation and API
* references of FreeRTOS, visit : https://www.freertos.org
*
*
*
*******************************************************************************

*******************************************************************************/

#include "cybsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "capsense_task.h"
//#include "led_task.h"
#include "printmsg_task.h"

/*******************************************************************************
 * Global constants
 ******************************************************************************/
/* Priorities of user tasks in this project. configMAX_PRIORITIES is defined in
 * the FreeRTOSConfig.h and higher priority numbers denote high priority tasks.
 */
#define TASK_CAPSENSE_PRIORITY (configMAX_PRIORITIES - 1)
#define TASK_PRINT_PRIORITY (configMAX_PRIORITIES - 2)

/* Stack sizes of user tasks in this project */
#define TASK_CAPSENSE_STACK_SIZE (256u)
#define TASK_PRINT_STACK_SIZE (configMINIMAL_STACK_SIZE)

/* Queue lengths of message queues used in this project */
#define SINGLE_ELEMENT_QUEUE (1u)


/*******************************************************************************
* Function Name: main()
********************************************************************************
* Summary:
*  System entrance point. This function sets up user tasks and then starts
*  the RTOS scheduler.
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Create the queues. See the respective data-types for details of queue
     * contents
     */
    print_command_data_q = xQueueCreate(SINGLE_ELEMENT_QUEUE,
                                      sizeof(print_command_data_t));
    capsense_command_q = xQueueCreate(SINGLE_ELEMENT_QUEUE,
                                      sizeof(capsense_command_t));

    /* Create the user tasks. See the respective task definition for more
     * details of these tasks.
     */
    xTaskCreate(task_capsense, "CapSense Task", TASK_CAPSENSE_STACK_SIZE,
                NULL, TASK_CAPSENSE_PRIORITY, NULL);
    xTaskCreate(task_printmsg, " PrintMsg Task", TASK_PRINT_STACK_SIZE,
                NULL, TASK_PRINT_PRIORITY, NULL);

    /* Start the RTOS scheduler. This function should never return */
    vTaskStartScheduler();

    /********************** Should never get here ***************************/
    /* RTOS scheduler exited */
    /* Halt the CPU if scheduler exits */
    CY_ASSERT(0);

    for (;;)
    {
    }

}


/* [] END OF FILE  */
