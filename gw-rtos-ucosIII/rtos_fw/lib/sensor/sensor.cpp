                                                                                  

#include "rest_client.hpp"                                                                                                                
#include "sensor.hpp"
 
using namespace std;   



Sensor::Sensor()
{
	enum REST::type_IoT_Services _type = ckan;
	try
	{
		strCredentials _cred;
		_cred.API_KEY=(char *)malloc(sizeof(char)* API_KEY.length()+1);		
		_cred.Server=(char *)malloc(sizeof(char) * SERVER.length()+1);
		strcpy(_cred.API_KEY,API_KEY.c_str());
		strcpy(_cred.Server,SERVER.c_str());
		client=new REST::Rest_Client(_type,_cred);
		setparametters();
	
	}catch(std::exception& e)                                                                                                    
        {                                                                                                                            
                cout << "Excepcion: " << e.what() << endl;                                                                           
        }
	cout << "Sensor inicializado " << endl;     
	

}
void Sensor::print_data_sensor()                                                                                   
{                                                                                                                                    
        cout << "SENSOR DEVICE: " << getIdentificador()  << endl;                                                   
        cout << "UBICACION: " << endl;                                                                                               
        cout << "       LONGITUD: " << getLongitud() << endl;                                                       
        cout << "       LATITUD:  " << getLatitud() << endl;                                                        
        cout << "MEDIDA: " << getMedida() << endl;                                 
        cout << "MAGNITUD: " << getMagnitud() << endl;                                                             
        cout << "DESCRIPCION " << getDescripcion() << endl;                                                        
        cout << "FECHA: " << getFecha() << endl;                                                                   
}  

string Sensor::getIdentificador()
{
	return Identificador;
}
void Sensor::setIdentificador(string _identificador)                            
{
	Identificador = _identificador;
}
 
void Sensor::setLongitud(float _longitud)
{
	Longitud=_longitud;
}
        
void Sensor::setLatitud(float _latitud)
{
	Latitud=_latitud;
}                                          
        
void Sensor::setMedida(float _medida)
{
	Medida=_medida;

}                                            

void Sensor::setMagnitud(string _magnitud)
{
	Magnitud=_magnitud;
}           

void Sensor::setDescripcion(string _descripcion)
{
 	Descripcion=_descripcion;       
}
	
void Sensor::setFecha(string _fecha)
{
	Fecha=_fecha;

}                 
                                                             
float Sensor::getLongitud()
{
	return Longitud;
}          
        
float Sensor::getLatitud()
{
	return Latitud;
}           

float Sensor::getMedida()
{
	return Medida;
}          

string Sensor::getMagnitud()
{
	return Magnitud;
}                              

string Sensor::getDescripcion()
{
	return Descripcion;
}

string Sensor::getFecha()
{
	return Fecha;
}



char * Sensor::getrecord(char *out,char *buffer,char *Identificador)                                                                         
{                                                                                                                                    
        int pos_ini,pos_fin,i,index,completed=0,count=0;                                                                             
        char *aux;                                                                                                                   
        aux=strstr(buffer,Identificador);                                                                                            
        if(aux!=NULL)                                                                                                                
        {                                                                                                                            
                pos_ini=(int)((aux-buffer)+(strlen(Identificador)+2));                                                               
                pos_fin=strlen(buffer);                                                                                              
                index=0;                                                                                                             
                for(i=pos_ini;(i<pos_fin)&&(!completed);i++)                                                                         
                {                                                                                                                    
                        if(buffer[i]=='"')                                                                                           
                        {                                                                                                            
                                count++;                                                                                             
                                if(count==2)                                                                                         
                                        completed=1;                                                                                 
                        }                                                                                                            
                        else{                                                                                                        
                                out[index++]=buffer[i];                                                                              
                        }                                                                                                            
                }                                                                                                                    
                out[index]='\0';                                                                                                     
                return out;                                                                                                          
        }                                                                                                                            
        else                                                                                                                         
                return NULL;                                                                                                         
                                                                                                                                     
}  


void Sensor::format_ckan_register(char * out, char * in)                                                                                     
{                                                                                                                                    
        char *aux;int index;                                                                                                         
        aux=strstr(in,(char*)"[{");                                                                                                  
        int pos_ini=(int)(aux-in);                                                                                                   
        aux=strstr(in,(char*)"}]");                                                                                                  
        int pos_fin=(int)(aux-in)+1;                                                                                                 
        if(aux!=NULL)                                                                                                                
        {                                                                                                                            
                strncpy(out,in,pos_ini+2);                                                                                           
                out[pos_ini+2]='\0';                                                                                                 
                int index_out=pos_ini;                                                                                               
                out[index_out++]='[';                                                                                                
                out[index_out++]='{';                                                                                                
                for(index=pos_ini+1;index<pos_fin;index++)                                                                           
                {                                                                                                                    
                        if( (in[index]!='{') and (in[index]!='}') )                                                                  
                                out[index_out++]=in[index];                                                                          
                                                                                                                                     
                }                                                                                                                    
                out[index_out++]='}';                                                                                                
                out[index_out++]=']';                                                                                                
                out[index_out++]='}';                                                                                                
                out[index_out]='\0';                                                                                                 
                                                                                                                                     
        }                                                                                                                            
                                                                                                                                     
}  


void Sensor::format_records_json(cJSON * record, const char * field, const char * value)                                                          
{                                                                                                                                    
        cJSON *auxiliar;                                                                                                             
        auxiliar=cJSON_CreateObject();                                                                                               
        cJSON_AddStringToObject(auxiliar,field,value);                                                                               
        cJSON_AddItemToArray(record,auxiliar);                                                                                       
} 



void Sensor::translate(char *text)                                                        
{                                                                             
        char *out;cJSON *json;                                                 
	int pos_ini,pos_fin,i,index=0;       
	char *aux_str=NULL,*buffer=NULL;
	char data[75];
        char * record_str=(char *)malloc(sizeof(char*)*strlen(text));                                                                                       
	string param;       
 
	json=cJSON_Parse(text);
        if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
        else                                                                                        
        {                                                     
	        out=cJSON_PrintUnformatted(json);
		aux_str=strstr(out,"records");
		if(aux_str != NULL)
		{
			pos_ini=(int)(aux_str-out);
			pos_fin=strlen(out);
			index=0;
			for(i=pos_ini;i<pos_fin;i++)
				record_str[index++]=out[i];
			record_str[index]='\0';
			aux_str=strstr(record_str,"[{");
			pos_ini=(int)(aux_str-record_str);
			aux_str=strstr(record_str,"}]");
			pos_fin=(int)(aux_str-record_str);
			buffer=(char *)malloc(sizeof(char)*(pos_fin-pos_ini+1));
			index=0;
			for(i=pos_ini+2;i<pos_fin;i++)
				buffer[index++]=record_str[i];
			getrecord(data,buffer,(char *)"Identificador");
			param=data;
			Sensor::setIdentificador(data);
			
			getrecord(data,buffer,(char *)"Fecha");
			param=data;
			Sensor::setFecha(param);
			
			getrecord(data,buffer,(char *)"Longitud");
			Sensor::setLongitud(atof(data));
		
			getrecord(data,buffer,(char *)"Latitud");
			Sensor::setLatitud(atof(data));
		
			getrecord(data,buffer,(char *)"Medida");
			Sensor::setMedida(atof(data));
			
			getrecord(data,buffer,(char *)"Magnitud");
			param=data;
			Sensor::setMagnitud(param);
			
			getrecord(data,buffer,(char *)"Descripcion");
			param=data;
			Sensor::setDescripcion(data);
			
			cJSON_Delete(json);                                     
			free(buffer);
		}
		free(out);
		free(record_str);
		                                    
        }                                                           
}   




void Sensor::read_publish_measurements(string Identificador)
{
	

	HttpResponse *response=(HttpResponse *)malloc(sizeof(HttpResponse));
	response->data=(char *)malloc(sizeof(char) * 1024);
	strcpy(response->data,"");

	const string url_datastore_search = "http://"+ SERVER + "/api/action/datastore_search" + "?" + "resource_id=" + RESOURCE + "&q=" + Identificador; 

	char urlChar[url_datastore_search.length()];                                                                           
        strcpy(urlChar, url_datastore_search.c_str()); 

	client->set_URL(urlChar);
	//client->set_body(body);                                                                                                       
                                                                                                                                     
        try{                                                                                                                         
                                                                                                                                     
                client->method_post(response);                                                                                       
       
	}
	catch(std::exception& e)                                                                                                    
        {                                                                                                                            
                cout << "Excepcion: " << e.what() << endl;                                                                           
        }                                                                                                                            
        

	translate(response->data);
                                                                                                                                     
        free(response->data);                                                                                                        
        free(response);                                                                                                              

}



void Sensor::publish_measurements(){
		
	char aux_str[25];
	cJSON *root,*regs;                                                                         
        char * out;                                                                               
	
	HttpResponse *response=(HttpResponse *)malloc(sizeof(HttpResponse));                        
        response->data=(char *)malloc(sizeof(char) * 1024);                                         
        strcpy(response->data,"");	
	
                                                                                                
        root=cJSON_CreateObject();                                                                
		
	cJSON_AddStringToObject(root,"resource_id", RESOURCE.c_str());
	cJSON_AddStringToObject(root,"method","insert");
	cJSON_AddStringToObject(root,"force","True");
	cJSON_AddItemToObject(root,"records",regs=cJSON_CreateArray());
	format_records_json(regs,(const char*)"Identificador", getIdentificador().c_str());
	sprintf(aux_str,"%.6f",getLongitud());
	format_records_json(regs,(const char*)"Longitud",(const char*)aux_str);
	sprintf(aux_str,"%.7f",getLatitud());
	format_records_json(regs,(const char*)"Latitud",(const char*)aux_str);
	sprintf(aux_str,"%.2f",getMedida());	
	format_records_json(regs,(const char*)"Medida",(const char*)aux_str);
	format_records_json(regs,(const char*)"Magnitud", getMagnitud().c_str());
	format_records_json(regs,(const char*)"Descripcion", getDescripcion().c_str());
	format_records_json(regs,(const char*)"Fecha", getFecha().c_str());

	out=cJSON_PrintUnformatted(root); 

	char *body=(char *)malloc(sizeof(char)*512);
	format_ckan_register(body,out);


	const string url_datastore_post = "http://"+ SERVER + "/api/action/datastore_upsert";
                                                                                                                                     
        char urlChar[url_datastore_post.length()];                                                                                 
        strcpy(urlChar, url_datastore_post.c_str());

	client->set_URL(urlChar);
	client->set_body(body);
	
	try{

		client->method_post(response); 

	}catch(std::exception& e)                                                                                                    
        {                                                                                                                            
                cout << "Excepcion: " << e.what() << endl;                                                                           
        }                                                                                                                            
	
	free(response->data);                                                                                                        
        free(response);                                                                                                              
	free(body);	
}

float Sensor::read_dataAFE(){
	
	return 1145.00;
}

void Sensor::setparametters()
{
	struct tm * _fecha;
	time_t temp;
	char _strfecha[25];
	string param;	
	
	temp=time(NULL);
	_fecha=localtime(&temp);        
	sprintf(_strfecha,"%.4d-%.2d-%.2dT%.2d:%.2d:%.2d",_fecha->tm_year+1900,_fecha->tm_mon,_fecha->tm_mday,_fecha->tm_hour,_fecha->tm_min,_fecha->tm_sec);
	
	param=_strfecha;
	
	setFecha(param);
	setIdentificador(SENSOR_ID);
        setLongitud(SENSOR_LONGITUD);                                                                                                           
        setLatitud(SENSOR_LATITUD);                                                                                                            
        setMedida(Sensor::read_dataAFE());                                                                                                               
        setMagnitud(MAGNITUD);                                                                                                        
        setDescripcion(DESCRIPCION_SENSOR);                                                                                                     


}

                                                                                                                                     
                                                                                                                                     
                                                                                                                                     



