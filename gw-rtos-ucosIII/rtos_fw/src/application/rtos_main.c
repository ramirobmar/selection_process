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


OS_MUTEX p_mutex_001;

OS_SEM p_sem_001;
OS_SEM p_sem_002;
OS_SEM p_sem_003;
OS_SEM p_sem_004;

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
	char strtime[25];
	char msg[81];
	
	OSInit(&err);  					//Initialize "uC/OS-III, The Real-Time Kernel"
	
	OSTaskCreate((OS_TCB     *)&App_TaskStartTCB,   //Create the start task                                
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR ) App_TaskStart,
                 (void       *) 0,
                 (OS_PRIO     ) APP_CFG_TASK_START_PRIO,
                 (CPU_STK    *) &App_TaskStartStk[0],
                 (CPU_STK     )(APP_CFG_TASK_START_STK_SIZE / 10u),
                 (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  ) 0,
                 (OS_TICK     ) 0,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *) &err);
	
	OSTaskCreate((OS_TCB *)&App_TaskSendDataTCB,    //Create the send data task  
                 (CPU_CHAR *)"App Task Send",
                 (OS_TASK_PTR) App_TaskSendData,
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

	OSSemCreate(&p_sem_001,"SEM_001",0,&err);	
	if(err != OS_ERR_NONE)
	{
		printf("Error creating SEM_001 \n");
		return -1;
	}
	
	OSSemCreate(&p_sem_002,"SEM_002",0,&err);
	if(err != OS_ERR_NONE)
	{
		printf("Error creating SEM_002 \n");
		return -1;
	}

	OSSemCreate(&p_sem_003,"SEM_003",0,&err);
        if(err != OS_ERR_NONE)
        {
                printf("Error creating SEM_003 \n");
                return -1;
        }


	OSSemCreate(&p_sem_004,"SEM_004",0,&err);
        if(err != OS_ERR_NONE)
        {
                printf("Error creating SEM_004 \n");
                return -1;
        }

	
	gettime(strtime);	
	sprintf(msg,"%s: Arranque del sistema...",strtime);	
	printf("%s\n",msg);
	
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
	
	while (DEF_TRUE) {                                          
		
		//OSTimeDlyHMSM((CPU_INT16U)0u, (CPU_INT16U)0u, (CPU_INT16U)10u, (CPU_INT16U)0u, OS_OPT_TIME_HMSM_STRICT, &os_err);
	
		gettime(strtime);
		sprintf(msg,"MAIN TASK: %s - Tarea Principal IoT_RTOS ...",strtime);
		printf("%s\n",msg);
	
		
		OSSemPost(&p_sem_001, OS_OPT_POST_ALL, &os_err);

		switch(os_err)
                {
                        case OS_ERR_NONE:
				gettime(strtime);
				printf("MAIN TASK:%s Starting measurement process correctly ...\n",strtime);
				break;
			default:
				printf("Error posting semaphore\n"); 
				break;
		}

		OSSemPend(&p_sem_002,0u,OS_OPT_PEND_BLOCKING,(CPU_TS *)0,&os_err);

                switch(os_err)
                {
                        case OS_ERR_NONE:
				gettime(strtime);
                                printf("MAIN TASK:%s Finished measurement process correctly ...\n",strtime);
                                OSSemSet(&p_sem_002,0,&os_err);
                                break;
                        default:
                                printf("Mutex was deleted\n");
                                OSSemPendAbort(&p_sem_002,OS_OPT_PEND_ABORT_1,&os_err);
                                break;
		}	

		OSSemPost(&p_sem_003, OS_OPT_POST_ALL, &os_err);

                switch(os_err)
                {
                        case OS_ERR_NONE:
                                gettime(strtime);
                                printf("MAIN TASK:%s Starting sending measurement process correctly ...\n",strtime);
                                break;
                        default:
                                printf("Error posting semaphore\n");
                                break;
                }
	
	

		OSSemPend(&p_sem_004,0u,OS_OPT_PEND_BLOCKING,(CPU_TS *)0,&os_err);

                switch(os_err)
                {
                        case OS_ERR_NONE:
                                gettime(strtime);
                                printf("MAIN TASK:%s Finished sending measurement process correctly ...\n",strtime);
                                OSSemSet(&p_sem_004,0,&os_err);
                                break;
                        default:
                                printf("Mutex was deleted\n");
                                OSSemPendAbort(&p_sem_004,OS_OPT_PEND_ABORT_1,&os_err);
                                break;
                }


		gettime(strtime);
		printf("MAIN TASK:%s - ********** FINISHED PROCESS *************\n",strtime);
				                           

	}
}

static void App_TaskAQSense(void *p_arg)
{
        OS_ERR os_err;
        char strtime[81];

        (void)p_arg;                                                /* See Note #1                                          */

        CPU_Init();
        Mem_Init();                                                 /* Initialize the Memory Management Module              */
        Math_Init();                                                /* Initialize the Mathematical Module                   */

        OS_CPU_SysTickInit();

        while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
                

		gettime(strtime);
		printf("SENSE TASK:%s - Waiting response ...\n",strtime);
		OSSemPend(&p_sem_001,0u,OS_OPT_PEND_BLOCKING,(CPU_TS *)0,&os_err);
		
		switch(os_err)		
		{
			case OS_ERR_NONE:
				gettime(strtime);
				printf("SENSE TASK:%s Starting measurement process ..\n",strtime);			
				OSSemSet(&p_sem_001,0,&os_err);
				//OSMutexPendAbort(&p_mutex_001,OS_OPT_PEND_ABORT_ALL,&os_err);	
				break;
			case OS_ERR_OBJ_DEL:
				printf("Mutex was deleted\n");
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				break;
			case OS_ERR_OBJ_PTR_NULL:
				printf("Mutex is a NULL pointer\n");
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				break;
			case OS_ERR_OBJ_TYPE:
				printf("Mutex is not pointing at a mutex\n");
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				break;
			case OS_ERR_OPT_INVALID:
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				printf("Not valid option\n");
				break;
			case OS_ERR_OS_NOT_RUNNING:
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				printf("uCOS is not running\n");
				break;
			case OS_ERR_PEND_ABORT:
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				printf("Pending task was finished by another task\n");
				break;
			case OS_ERR_PEND_ISR:
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				printf("ISR and the result would lead to a suspension\n");
				break;
			case OS_ERR_PEND_WOULD_BLOCK:
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				printf("Mutex not blocking but was not available\n");
				break;
			case OS_ERR_SCHED_LOCKED:
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				printf("Scheduled is locked\n");
				break;
			case OS_ERR_STATUS_INVALID:
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				printf("Pend status has an invalid value\n");
				break;
			case OS_ERR_TIMEOUT:
				printf("Semaphore was not recieved within the specified timeout\n");
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				break;
			default:
				OSSemPendAbort(&p_sem_001,OS_OPT_PEND_ABORT_1,&os_err);
				break;
		}
		
		gettime(strtime);
		printf("SENSE TASK:%s - Syncronized TASK SENSE + TASK MAIN\n",strtime);	
                
		gettime(strtime);
		printf("SENSE TASK:%s - Adquiring measurement .....\n",strtime);
		
		gettime(strtime);
		printf("SENSE TASK:%s - Exit TASK SENSE\n",strtime);
		
		OSSemPost(&p_sem_002, OS_OPT_POST_ALL, &os_err);

                switch(os_err)
                {
                        case OS_ERR_NONE:
                                gettime(strtime);
                                printf("SENSE TASK:%s Confirming measurement process has been do it ...\n",strtime);
                                break;
                        default:
                                printf("SENSE TASK: Error posting semaphore\n");
                                break;
                } 

		
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
		

		gettime(strtime);
		sprintf(msg,"PUBLISH TASK: %s: Tarea de publicacion de datos ...",strtime);
		printf("%s\n",msg);
		
		OSSemPend(&p_sem_003,0u,OS_OPT_PEND_BLOCKING,(CPU_TS *)0,&os_err);

                switch(os_err)
                {
                        case OS_ERR_NONE:
				gettime(strtime);
                                printf("PUBLISH TASK:%s Starting publish measurement process ....\n",strtime);
                                OSSemSet(&p_sem_003,0,&os_err);
                                break;
                        default:
                                gettime(strtime);
				printf("PUBLISH TASK:%s Error publishing measurements ....\n",strtime);
                                OSSemPendAbort(&p_sem_003,OS_OPT_PEND_ABORT_1,&os_err);
                                break;
		}

		
		OSSemPost(&p_sem_004, OS_OPT_POST_ALL, &os_err);

                switch(os_err)
                {
                        case OS_ERR_NONE:
                                gettime(strtime);
                                printf("PUBLISH TASK:%s Confirming publish measurement process has been do it ...\n",strtime);
                                break;
                        default:
                                printf("PUBLISH TASK: Error posting semaphore\n");
                                break;
                }		
    	
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
