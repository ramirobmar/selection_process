//################# LIBRARIES ################
#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>
#include "mraa.hpp"

#include <map>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include <time.h>


#include "cJSON.h"

#include "sensor.hpp"
#include "rest_client.hpp"


using namespace std;
using namespace REST;

//################ CKAN VARIABLES ################




int main()
{
	
	Sensor * sensor_device=new Sensor();		
	Sensor * sensor_reading=new Sensor();	
	for (;;) {
		
		sensor_device->publish_measurements();		
		sleep(5);
		sensor_reading->read_publish_measurements("AF01234513");
		sensor_reading->print_data_sensor();
		sleep(5);
	}
	return 0;
}
