/*********************************************************************************************************
*                                           IoT_RTOS 
* Filename      : rtos_main.cpp
* Version       : V1.01
* Programmer(s) : RBM
*********************************************************************************************************/
/*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************/

#include <app_cfg.h>
#include <os.h>
#include <stdio.h>
#include <lib_mem.h>
#include <lib_math.h>
#include <time.h>
#include <stdio.h>

/*******************************************************************************************************
*                                            LOCAL DEFINES
********************************************************************************************************/
/********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************/
static  OS_TCB        App_TaskStartTCB;
static  CPU_STK_SIZE  App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];
static  OS_TCB        App_TaskSendDataTCB;
static  CPU_STK_SIZE  App_TaskSendDataStk[APP_CFG_TASK_START_STK_SIZE];
static  OS_TCB        App_TaskAQSenseTCB;
static  CPU_STK_SIZE  App_TaskAQSenseStk[APP_CFG_TASK_START_STK_SIZE];
/*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************/

static void App_TaskStart(void *p_arg);
static void App_TaskSendData(void *p_arg);
static void App_TaskAQSense(void *p_arg);
static char * gettime(char * msg);

/*********************************************************************************************************
*                                                main()
* Description :
* Argument(s) : none
* Return(s)   : none
* Caller(s)   : This the main standard entry point
* Note(s)     : none.
*********************************************************************************************************/

int  main (void)
{
	OS_ERR  err;
	
	OSInit(&err);  					//Initialize "uC/OS-III, The Real-Time Kernel"
	OSTaskCreate((OS_TCB     *)&App_TaskStartTCB,   //Create the start task                                
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR ) App_TaskStart,
                 (void       *) 0,
                 (OS_PRIO     ) APP_CFG_TASK_START_PRIO,
                 (CPU_STK    *)&App_TaskStartStk[0],
                 (CPU_STK     )(APP_CFG_TASK_START_STK_SIZE / 10u),
                 (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  ) 0,
                 (OS_TICK     ) 0,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
	
	OSTaskCreate((OS_TCB *)&App_TaskSendDataTCB,    //Create the send data task  
                 (CPU_CHAR *)"App Task Send",
                 (OS_TASK_PTR ) App_TaskSendData,
                 (void *) 0,
                 (OS_PRIO) APP_CFG_TASK_START_PRIO,
                 (CPU_STK *)&App_TaskSendDataStk[0],
                 (CPU_STK)(APP_CFG_TASK_START_STK_SIZE / 10u),
                 (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY) 0,
                 (OS_TICK) 0,
                 (void *) 0,
                 (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR *)&err);

	OSTaskCreate((OS_TCB *)&App_TaskAQSenseTCB,       //Create the send data task
                 (CPU_CHAR *)"App Task Send",
                 (OS_TASK_PTR ) App_TaskAQSense,
                 (void *) 0,
                 (OS_PRIO) APP_CFG_TASK_START_PRIO,
                 (CPU_STK *)&App_TaskAQSenseStk[0],
                 (CPU_STK)(APP_CFG_TASK_START_STK_SIZE / 10u),
                 (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY) 0,
                 (OS_TICK) 0,
                 (void *) 0,
                 (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR *)&err);
	
	OSStart(&err); // Start multitasking (i.e. give control to uC/OS-III)
	while(DEF_ON){ //Should Never Get Here
	};
}


/*********************************************************************************************************
*                                          App_TaskStart()
* Description :
* Argument(s) : p_arg   is the argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
* Return(s)   : none.
* Caller(s)   : This is a task.
* Notes       : 
*********************************************************************************************************
*/

static void App_TaskStart(void *p_arg)
{
	OS_ERR os_err;
	char strtime[81];
	char msg[81];
	
	(void)p_arg;                                                // See Note #1
	CPU_Init();
	Mem_Init();                                                 // Initialize the Memory Management Module
	Math_Init();                                                // Initialize the Mathematical Module       
	
	OS_CPU_SysTickInit();
	
	while (DEF_TRUE) {                                          // Task body, always written as an infinite loop
		OSTimeDlyHMSM(0u, 0u, 5u, 0u,OS_OPT_TIME_HMSM_STRICT,&os_err);
		gettime(strtime);
		sprintf(msg,"%s: Tarea Principal IoT_RTOS ...",strtime);
		printf("%s\n",msg);
	}
}

static void App_TaskAQSense(void *p_arg)
{
        OS_ERR os_err;
        char strtime[81];
        char msg[81];   

        (void)p_arg;                                                /* See Note #1                                          */

        CPU_Init();
        Mem_Init();                                                 /* Initialize the Memory Management Module              */
        Math_Init();                                                /* Initialize the Mathematical Module                   */

        OS_CPU_SysTickInit();

        while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
                //printf("Tarea principal AQ_RTOS\n");
                OSTimeDlyHMSM(0u, 0u, 5u, 0u,OS_OPT_TIME_HMSM_STRICT,&os_err);
                gettime(strtime);
                sprintf(msg,"%s: Tarea lectura sensor ...",strtime);
                printf("%s\n",msg);
        }
}

static void App_TaskSendData(void *p_arg)
{
	OS_ERR os_err;
	char strtime[81];
	char msg[81];
	
	(void)p_arg; // See Note #1 

	CPU_Init();
	Mem_Init();  // Initialize the Memory Management Module 
	Math_Init(); // Initialize the Mathematical Module  

	OS_CPU_SysTickInit();

	while (DEF_TRUE) {  // Task body, always written as an infinite loop
        	OSTimeDlyHMSM(0u, 0u, 10u, 0u,OS_OPT_TIME_HMSM_STRICT,&os_err);
		gettime(strtime);
		sprintf(msg,"%s: Tarea de publicacion de datos ...",strtime);
		printf("%s\n",msg);
    	}
}

static char * gettime(char * msg)
{
	struct tm * _fecha;
	char str_time[25];
	char str_date[25];
	time_t temp;
	
	temp=time(NULL);
	_fecha=localtime(&temp);
	
	sprintf(str_date,"%.2d/%.2d/%.4d",_fecha->tm_mday,_fecha->tm_mon,_fecha->tm_year+1900);
	sprintf(str_time,"%.2d:%.2d:%.2d",_fecha->tm_hour,_fecha->tm_min,_fecha->tm_sec);
	sprintf(msg,"%s - %s",str_date,str_time);
	
	return msg;
}
