#if !defined(SENSOR_HPP)                                                                       
#define SENSOR_HPP                                                                             
                                                                                  
//LIBRARIES                                                                                    
#include <stdio.h>                                                                              
#include <stdlib.h>                                                                               
                                                                                                                                     
#include <curl/curl.h>                                                            
#include <map>                                                                    
#include <unistd.h>                                                
#include <iostream>                                                                       
#include <sstream>                                                                          
#include <time.h>                                                                           
                                                                                                  
#include "cJSON.h"                                                                             


#include "rest_client.hpp"                                                                                                                
                                                                                    
using namespace std;   
using namespace REST;

//using REST::Rest_Client;




const float SENSOR_LATITUD=40.6295047;                                                                                               
const float SENSOR_LONGITUD=-3.172255;                                                                                               
const string SENSOR_ID = "AF01234518";                                                                                               
const string MAGNITUD= "'Kwh'";                                                                                                      
const string DESCRIPCION_SENSOR="Power-Electricity Sensor"; 

const string API_KEY="f1d1af32-7a08-4a07-94e8-35243b54ec75";                                                                    
const string RESOURCE="f0b10490-b45d-4e92-85ae-3989cf72705b";                                                                  
const string SERVER = "demo.ckan.org";




class Sensor
{

private:


public:

	Sensor();
	
	void print_data_sensor(); 
	char * getrecord(char *out,char *buffer,char *Identificador);
	void format_ckan_register(char * out, char * in);
	void format_records_json(cJSON * record, const char * field, const char * value);
	void translate(char *text);  
	
	float read_dataAFE();
	
	void setparametters();		
	void read_publish_measurements(string Identificador);
	void publish_measurements();
	
	void setIdentificador(string _identificador);
	void setLongitud(float _longitud);
	void setLatitud(float _latitud);
	void setMedida(float _medida);
	void setMagnitud(string _magnitud);
	void setDescripcion(string _descripcion);
	void setFecha(string _fecha);

	string getIdentificador();
	float getLongitud();
	float getLatitud();
	float getMedida();
	string getMagnitud();
	string getDescripcion();
	string getFecha();

protected:

	string Identificador;                                                                                                      
        float Longitud;                                                                                                              
        float Latitud;                                                                                                               
        float Medida;                                                                                                                
        string Magnitud;                                                                                                           
        string Descripcion;                                                                                                        
        string Fecha;	

	REST::Rest_Client *client;	


};



                                                                                                                                     
                                                                                                                                     
                                                                                                                                     
#endif  



