
#include "rest_client.hpp"
#include "sensor.hpp"                                                                                             

using namespace std;  
using namespace REST;


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



REST::Rest_Client::Rest_Client()
{


}

REST::Rest_Client::Rest_Client(type_IoT_Services _type, strCredentials _cred)
{
	string _localurl;	                                                                      
	switch(_type)                                                   
        {                                                               
        	case ckan:                                              
			set_APIKEY(_cred.API_KEY);
			set_SERVER(_cred.Server);		
			_localurl = "http://"+ Rest_Client::SERVER + "/api/action/datastore_upsert";                                                                                
			set_URL(_localurl.c_str());
			break;                                          
        	case fiware:                                            
                                                                                
                	break;                                          
                                                                                
                case azure:                                             
                                                                                
                	break;                                          
                                                                                
                default:                                                
                                                                                
                	break;                                          
                                                                                
        }                                                               


}

void REST::Rest_Client::set_body(const char * _body)
{
	this->body=_body;

}

void REST::Rest_Client::set_APIKEY(const char * _apikey) 
{ 
	Rest_Client::APIKEY = _apikey;
}            
void REST::Rest_Client::set_RESOURCE(const char * _resourceID) 
{ 
	Rest_Client::RESOURCE = _resourceID; 
}
void REST::Rest_Client::set_SERVER(const char * _servername)
{
	Rest_Client::SERVER = _servername;
}
void REST::Rest_Client::set_URL(const char * _url)
{
	Rest_Client::URL = _url;
}

void REST::Rest_Client::method_post(HttpResponse *response)
{

	CURL * curl;                                                                                                                 
        CURLcode res; 	


	CONTENT="'application/json'";                                                                                                
        header_auth_str="Authorization: " + APIKEY;                                                                                  
        header_content_str="Content-Type: "+ CONTENT;          

	curl = curl_easy_init();                                                                                                     
                                                                                                                                     
        if(curl) {                                                                                                                   
                                                                                                                                     
                curl_easy_setopt(curl, CURLOPT_URL, Rest_Client::URL.c_str());                                                                        
                struct curl_slist *headers = NULL;                                                                                   
                headers = curl_slist_append(headers,header_content_str.c_str());                                                     
                headers = curl_slist_append(headers,header_auth_str.c_str());                                                        
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);                                                                 
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());                                                                  
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);                                                                  
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback_func);                                             
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void **)&response->data);                                                 
                                                                                                                                     
                res = curl_easy_perform(curl);                                                                                       
                if(response) {                                                                                                       
                        response->code = 0;                                                                                          
                        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response->code);                                           
                }                                                                                                                    
                if(res != CURLE_OK)                                                                                                  
                        cerr << "POST: ERROR!" << curl_easy_strerror(res) << endl;                                                   
                else                                                                                                                 
                        cout << "POST: OK! " << endl;                                                                                
        }                                                                                                                            
        curl_easy_cleanup(curl);                                                                                                     
        body="";           


}                                                                                    
void REST::Rest_Client::method_get(HttpResponse *response)
{
	
	CURL * curl;                                                                                                                 
        CURLcode res; 

	CONTENT="'application/json'";                                                                                         
        header_auth_str="Authorization: " + APIKEY;                                                                           
        header_content_str="Content-Type: "+ CONTENT;


	curl = curl_easy_init();                                                                                                     
                                                                                                                                     
        if(curl) {                                                                                                                   
                curl_easy_setopt(curl, CURLOPT_URL, Rest_Client::URL.c_str() );                                                                        
                                                                                                                                     
                struct curl_slist *headers = NULL;                                                                                   
                                                                                                                                     
                headers = curl_slist_append(headers,header_content_str.c_str());                                                     
                headers = curl_slist_append(headers,header_auth_str.c_str());                                                        
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);                                                                 
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);                                                                  
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback_func);                                             
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void **)&response->data);                                                 
                                                                                                                                     
                try{                                                                                                                 
                        res = curl_easy_perform(curl);                                                                               
                                                                                                                                     
                        if(response) {                                                                                               
                                response->code = 0;                                                                                  
                                curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response->code);                                   
                                //doit((char *)response->data,sensor_device);                                                          
                                //print_data_sensor(sensor_device);                                                                    
                        }                                                                                                            
                                                                                                                                     
                        if(res != CURLE_OK)                                                                                          
                                cerr << "GET: ERROR -  " << curl_easy_strerror(res) << endl;                                         
                        else{                                                                                                        
                                cout << "GET: OK! " << endl;                                                                         
                }                                                                                                                    
                }catch(std::exception& e)                                                                                            
                {                                                                                                                    
                        cout << "Excepcion: " << e.what() << endl;                                                                   
                }                                                                                                                    
                                                                                                                                     
                                                                                                                                     
        }                                                                                                                            
        curl_easy_cleanup(curl);  
}


