/*
*********************************************************************************************************
*                                              
*
*                          		
*
*               
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            AQ_RTOS
*
*                                         
*
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : RBM
*                 SB
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <app_cfg.h>
#include  <os.h>
#include  <stdio.h>

#include  <lib_mem.h>
#include  <lib_math.h>

#include <xively.h>
#include <xi_helpers.h>

#include <time.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <datahandler.h>

#include "ae.h"
#include "anet.h"
#include "mqtt.h"
#include "zmalloc.h"
#include "packet.h"
#include "client.h"

#include <mqtt_client.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

extern Client client;

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_TCB        App_TaskStartTCB;
static  CPU_STK_SIZE  App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];
static  OS_TCB        App_TaskSendDataTCB;
static  CPU_STK_SIZE  App_TaskSendDataStk[APP_CFG_TASK_START_STK_SIZE];
static  OS_TCB        App_TaskDustAllergSenseTCB;
static  CPU_STK_SIZE  App_TaskDustAllergSenseStk[APP_CFG_TASK_START_STK_SIZE];
static  OS_TCB        App_TaskAQSenseTCB;
static  CPU_STK_SIZE  App_TaskAQSenseStk[APP_CFG_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void App_TaskStart(void *p_arg);
static void App_TaskSendData(void *p_arg);
static void App_TaskDustAllergSense(void *p_arg);
static void App_TaskAQSense(void *p_arg);


static int initIoTEnv();
static char * gettime(char * msg);

static void log(char * seccion, char * message);

static void initMQTTClient();


/*
*********************************************************************************************************
*					CLOUD PARAMS
*********************************************************************************************************
*/

static char* API_KEY = "111111-1111-1111-11111";
static unsigned int FEED_ID = 10;
static char * DATASTREAM_ID = "datastream_id";
static unsigned int meassurement = 12;
static xi_context_t* xi_context= NULL;

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This the main standard entry point.
*
* Note(s)     : none.
*********************************************************************************************************
*/

int  main (void)
{
    
	int resp;
	OS_ERR  err;

	OSInit(&err);                                               /* Initialize "uC/OS-III, The Real-Time Kernel"         */
	resp=initIoTEnv();
	if(resp==-1)
	{
		log("INICIALIZACION","Error de inicializacion");
	}
	
	initMQTTClient();

	OSTaskCreate((OS_TCB *)&App_TaskStartTCB,               /* Create the start task                                */
                 (CPU_CHAR  *)"App Task Start",
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

	/*OSTaskCreate((OS_TCB *)&App_TaskSendDataTCB,                                              
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
	*/

	OSTaskCreate((OS_TCB *)&App_TaskAQSenseTCB,               /* Create the send data task                                */
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

	OSTaskCreate((OS_TCB *)&App_TaskDustAllergSenseTCB,               /* Create the send data task                                */
                 (CPU_CHAR *)"App Task Send",
                 (OS_TASK_PTR ) App_TaskDustAllergSense,
                 (void *) 0,
                 (OS_PRIO) APP_CFG_TASK_START_PRIO,
                 (CPU_STK *)&App_TaskDustAllergSenseStk[0],
                 (CPU_STK)(APP_CFG_TASK_START_STK_SIZE / 10u),
                 (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY) 0,
                 (OS_TICK) 0,
                 (void *) 0,
                 (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR *)&err);

    	OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */

	

    	while(DEF_ON){						/* Should Never Get Here							    */
    	};
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Notes       : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static void App_TaskStart(void *p_arg)
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
		sprintf(msg,"%s: Tarea Principal AQ_RTOS",strtime);
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
                sprintf(msg,"%s: Tarea medida contaminacion en el ambiente",strtime);
                printf("%s\n",msg);
        }
}

static void App_TaskDustAllergSense(void *p_arg)
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
                sprintf(msg,"%s: Tarea medida concentraciones alegenos",strtime);
                printf("%s\n",msg);
        }
}




static void App_TaskSendData(void *p_arg)
{
	OS_ERR os_err;
	char strtime[81];
	char msg[81];
	(void)p_arg;                                                /* See Note #1                                          */

	CPU_Init();
	Mem_Init();                                                 /* Initialize the Memory Management Module              */
	Math_Init();                                                /* Initialize the Mathematical Module                   */

	OS_CPU_SysTickInit();



	if(connect_datahandler()==-1)
		printf("Error en conexión con el servidor\n");
	else
		printf("Conectado con el servidor\n");

	xi_datapoint_t datapoint;
    	xi_set_value_i32(&datapoint,meassurement);


        time_t timer = 0;
        time(&timer);
        datapoint.timestamp.timestamp = timer;

    	xi_datastream_create(xi_context,FEED_ID,DATASTREAM_ID,&datapoint);
	printf( "err: %d - %s\n", ( int ) xi_get_last_error(), xi_get_error_string( xi_get_last_error() ) );


	while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        	//printf("Tarea envio de datos AQ_RTOS\n");
		OSTimeDlyHMSM(0u, 0u, 10u, 0u,OS_OPT_TIME_HMSM_STRICT,&os_err);
		time(&timer);
        	datapoint.timestamp.timestamp = timer;
		xi_datastream_update(xi_context,FEED_ID,DATASTREAM_ID,&datapoint);
    		printf( "err: %d - %s\n", ( int ) xi_get_last_error(), xi_get_error_string( xi_get_last_error() ) );
		gettime(strtime);
		sprintf(msg,"%s: Tarea de envio de datos AQ_RTOS",strtime);
		printf("%s\n",msg);
    	}
}

static char * gettime(char * msg)
{
	struct tm * _fecha;
	time_t temp;
	temp=time(NULL);
	_fecha=localtime(&temp);
	sprintf(msg,"%.2d/%.2d/%.4d - %.2d:%.2d:%.2d",_fecha->tm_mday,_fecha->tm_mon+1,_fecha->tm_year+1900,_fecha->tm_hour,_fecha->tm_min,_fecha->tm_sec);
	return msg;
}


static int initIoTEnv()
{
	xi_context = xi_create_context(XI_HTTP,API_KEY,FEED_ID);
	if( xi_context == 0 )
	{
		return -1;
	}



	return 0;
}



static void initMQTTClient()
{

	MqttMsg _msg;
	int _msgid=1;
	char * _topic="Temp";
	char * _payload="10.0";
	int msgId;

	client_prepare();
        //init
        client_init();

        //parse args
        client_setup();

        //set stdin event
        client_open();

        //set callbacks
        set_callbacks(client.mqtt);

        if(mqtt_connect(client.mqtt) < 0) {
        	log("MQTT", "MQTT conexión fallida");
		return;
    	}
	else
		log("MQTT","Conexión correcta MQTT Cliente");
	
	//mqtt_run(client.mqtt);

	mqtt_ping(client.mqtt);
	
	

	msgId=mqtt_subscribe(client.mqtt, _topic, 1);
	printf("Realizada suscripción msgId:%d\n",msgId);





	//mqtt_disconnect(client.mqtt);	

	_msg.topic=_topic;
	_msg.payload=_payload;

	//printf("%s\n",_msg.topic);

	//msgId=mqtt_publish(client.mqtt, &_msg);
	//printf("Realizada publicación de datos: %d\n",msgId);


	on_publish(client.mqtt, &_msg, _msgid);
	

}

static void log(char * seccion, char * message)
{

	char msg[81];
	char strtime[81];
	
	gettime(strtime);
        sprintf(msg,"%s: %s - %s", strtime, seccion, message);
        printf("%s\n", message);
}

