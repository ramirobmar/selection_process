#include <cstring>
#include <unistd.h>
#include <stdio.h>

#include <iostream>


using std::memset;
using std::memcpy;


#define MQTTCLIENT_QOS2 1
#include "MQTTClient.h"
#define DEFAULT_STACK_SIZE -1
#include "linux.cpp"


int arrivedcount = 0;

void messageArrived(MQTT::MessageData& md)
{
    	MQTT::Message &message = md.message;

	printf("Message %d arrived: qos %d, retained %d, dup %d, packetid %d\n", 
		++arrivedcount, message.qos, message.retained, message.dup, message.id);
    	printf("Payload %.*s\n", message.payloadlen, (char*)message.payload);
}


int main(int argc, char* argv[])
{   
    IPStack ipstack = IPStack();
    float version = 0.3;
    const char* topic = "$SYS/SP_001";
    
    printf("Version: %.2f\n", version);
              
    MQTT::Client<IPStack, Countdown> client = MQTT::Client<IPStack, Countdown>(ipstack);
    
    const char* hostname = "192.168.0.31";
    int port = 1883;
    printf("Conectando con %s:%d\n", hostname, port);
    int rc = ipstack.connect(hostname, port);
    if (rc != 0)
	printf("rc from TCP connect is %d\n", rc);
 
    printf("MQTT conectando ...\n");
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
    data.MQTTVersion = 3;
    data.clientID.cstring = (char*)"GU-SN-S001";
    rc = client.connect(data);
    if (rc != 0){
	printf("rc procedente de la conexión MQTT es %d\n", rc);
        exit(-1);
    }
    
    printf("MQTT conectado\n");
    
    rc = client.subscribe(topic, MQTT::QOS2, messageArrived);   
    
    if (rc != 0){
        printf("rc procedente de la subscripción MQTT es %d\n", rc);
        exit(-1);
    }
    
    MQTT::Message message;

    // QoS 0
    char buf[100];
    sprintf(buf, "Hello World!  QoS 0 message from app version %f", version);
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)buf;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    if (rc != 0){
	printf("Error %d from sending QoS 0 message\n", rc);
        exit(-1);
    }

    else while (arrivedcount == 0)
        client.yield(100);
        
    // QoS 1
    printf("Now QoS 1\n");
    sprintf(buf, "Hello World!  QoS 1 message from app version %f", version);
    message.qos = MQTT::QOS1;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    if (rc != 0)
    {
	printf("Error %d from sending QoS 1 message\n", rc);
        exit(-1);
    }
    else while (arrivedcount == 1)
        client.yield(100);
        
    // QoS 2
    sprintf(buf, "Hello World!  QoS 2 message from app version %f", version);
    message.qos = MQTT::QOS2;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    
    if (rc != 0){
	printf("Error %d from sending QoS 2 message\n", rc);
    	exit(-1);
    }
    while (arrivedcount == 2)
        client.yield(100);
    
    
    rc = client.unsubscribe(topic);
    
    if (rc != 0){
        printf("rc from unsubscribe was %d\n", rc);
    	exit(-1);
    }
    rc = client.disconnect();
    if (rc != 0){
        printf("rc from disconnect was %d\n", rc);
    	exit(-1);
    }
    ipstack.disconnect();
    
    printf("Finishing with %d messages received\n", arrivedcount);
    
    return 0;
}

