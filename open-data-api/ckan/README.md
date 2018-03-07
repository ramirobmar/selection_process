CKAN API
--------


Introduction
------------
We was interesting to develop an API ( Application Programing Interface) as a tool that it can be useful for
publish open-data to out open-data platform. This API can help us to deploy quickly applications in open-hardware
platforms as our case, Intel Galileo 2 Board, integrating an AFE and providing a USB-WIFI adapter we can have
a simple embedded electronic device with the capability to publish in real-time measurements to the cloud and 
our open-data portal.

How we can connect with our deployment environment
--------------------------------------------------
We can acces to the Galileo Board across ssh, as the next example:

>>ssh root@galileo


How we can configure our environment
------------------------------------
The first step that it necesary to do is configure your CKAN credentials, we will begin using the open-project

http://demo.ckan.org

We must create a count, when we are finished this process we can obtain a set of credentials that
we will use for configure our application, into the main.cpp file:


In a first stage the API-KEY joined to our account
string CKAN_APIKEY="f1d1af32-7a08-4a07-94e8-35243b54ec75";

In a second state, when we are finished out first data-set, the id of our work-dataset
string CKAN_RESOURCE ="f0b10490-b45d-4e92-85ae-3989cf72705b";                 




