
#if !defined(REST_CLIENT_HPP)
#define REST_CLIENT_HPP

//LIBRARIES
#include <stdio.h>                                                                          
#include <stdlib.h>                                                                         
#include <string.h>
                                                                                            
#include <curl/curl.h>                                                                      
#include <map>                                                                              
#include <unistd.h>                                                                         
#include <iostream>                                                                         
#include <sstream>                                                                          
#include <time.h>                                                                           
                                                                                            
#include "cJSON.h"                                                                          


using namespace std;  




namespace REST
{

enum type_IoT_Services { ckan, fiware, azure };
struct Credentials{
	char * API_KEY;
	char * Server;
};
typedef struct Credentials strCredentials;

typedef struct _HttpResponse {                                                  
    long code;                                                                  
    char *data;                                                                 
} HttpResponse; 


/*
size_t static curl_write_callback_func(char *buffer,size_t size,size_t nitems,void **outstream)                                      
{                                                                                                                                    
        size_t write_length;                                                                                                         
        char * fragment;                                                                                                             
        int size_stream=0;                                                                                                           
                                                                                                                                     
        try{                                                                                                                         
                if(*outstream != NULL)                                                                                               
                {                                                                                                                    
                        fragment=(char *)strndup((const char*)buffer, (size_t)(size * nitems));                                      
                        size_stream = strlen((char *)*outstream);                                                                    
                        size_stream += strlen(fragment) + 1;                                                                         
                        *outstream = (char *)realloc((char*)*outstream,size_stream);                                                 
                        strcat((char *)*outstream,fragment);                                                                         
                        write_length=strlen((char *)*outstream);                                                                     
                        free(fragment);                                                                                              
                }else{                                                                                                               
                                                                                                                                     
                        *outstream=(char *)strndup((const char *)buffer, (size_t)(size * nitems));                                   
                        write_length=strlen((char *)*outstream);                                                                     
                }                                                                                                                    
        }catch(std::exception& e)                                                                                                    
        {                                                                                                                            
                cout << "Excepcion: " << e.what() << endl;                                                                           
        }                                                                                                                            
                                                                                                                                     
        return write_length;                                                                                                         
                                                                                                                                     
}      
*/



class Rest_Client
{
protected:
	 
	string body;
	
	string APIKEY;                
	string RESOURCE;             
	string SERVER;                                     
	string URL; 

	string CONTENT;	
	string header_auth_str;                                                                
        string header_content_str; 


public:

	Rest_Client();
	Rest_Client(type_IoT_Services _type, strCredentials _cred);

	void set_body(const char*  _body);

	void method_post(HttpResponse *response);
	void method_get(HttpResponse *response);
	
	void set_APIKEY(const char * _apikey);
	void set_RESOURCE(const char * _resourceID);
	void set_SERVER(const char * _servername);
	void set_URL(const char * _url);

private:

};




}


#endif
