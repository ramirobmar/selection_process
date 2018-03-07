#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <pthread.h>

#include <signal.h>



#include "datahandler.h"

#define TRUE 1
#define FALSE 0


static int sd=0;
static int Connected = FALSE;



int connect_datahandler(){


	int res, nbytes;
	void * buffer;
	struct addrinfo hints,*result,*rp;

	memset(&hints,0,sizeof(hints));
	hints.ai_flags=0;
	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_protocol=0;
	buffer=(char *)malloc(128);
	res=getaddrinfo("127.0.0.1","49502",&hints,&result);
	if(res!=0)
	{

		return -1;
	}

	for(rp=result;rp!=NULL;rp=rp->ai_next)
	{
		sd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
		if(sd == -1){
			return -1;
		}
		if(connect(sd,rp->ai_addr,rp->ai_addrlen)!=1)
			break;
		close(sd);
	}

	if(rp == NULL)
	{
		return -1;
	}
	else{
		Connected = TRUE;
	}

	//for(;;)
	//{

		//nbytes=recv(sd,buffer,128,0);
		//if(nbytes == -1){
		//	return -1;
		//}
		//else{
		//	free(buffer);
		//}
	//}

	return sd;


}

int send_data(char * data)
{

	
	int nbytes;

	if(Connected == TRUE)
	{
		nbytes=send(sd,data,strlen(data),0);
		if(nbytes == -1){

			return -1;
		}

	}


	return 0;
}

char * read_data()
{


	int nbytes;
	char buffer[128];
	if(Connected == TRUE)
	{

		for(;;)
		{

			nbytes=recv(sd,buffer,128,0);
			if(nbytes == -1)
			{

				return -1;
			}
			else{
				return buffer;
			}
		}

	}
	return -1;
}
