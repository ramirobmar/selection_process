
SHELL = /bin/sh
.PHONY: clean, mkdir, install, uninstall, html 

-include sources.mk
-include lib/Micrium/Software/uCOS-III/Source/subdir.mk
-include lib/Micrium/Software/uCOS-III/Ports/POSIX/GNU/subdir.mk
-include lib/Micrium/Software/uC-LIB/subdir.mk
-include lib/Micrium/Software/uC-CPU/Posix/GNU/subdir.mk
-include lib/Micrium/Software/uC-CPU/subdir.mk
-include src/application/subdir.mk
-include objects.mk


ifndef basedir
	basedir = $(shell pwd)
endif

ifndef srcdir
	srcdir = ${basedir}/src 
endif


ifndef prefix
	prefix = /usr/local
endif

ifndef exec_prefix
	exec_prefix = ${prefix}
endif


ifndef mqttsrcdir
	mqttsrcdir = ./lib/mqtt/MQTTPacket/src
endif


ifndef libdir
	libdir = ./lib
endif



ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif



LD_FLAGS += -I /usr/include \
-I ./lib/cJSON \
-I ./lib/rest \
-I ./lib/sensor \
-I ./include

CPP_FLAGS := -O0 -g3 -Wall -fmessage-length=0 -std=gnu++98 -fno-rtti \
-fstrict-aliasing -Wall -Wunused-function -DLINUX_SO -fPIC

C_FLAGS :=   
SRC_LIBS := ./lib/cJSON/cJSON.c \
./lib/sensor/sensor.cpp \
./lib/rest/rest_client.cpp

IoT_SN := ./bin/IoT_SN
IoT_RTOS := ./bin/IoT_RTOS

CCFLAGS_SO := -g -fPIC -Os -Wall -fvisibility=hidden -DLINUX_SO




#determine current platform
ifeq ($(OS),Windows_NT)
	OSTYPE = $(OS)
else
	OSTYPE = $(shell uname -s)
	MACHINETYPE = $(shell uname -m)
endif


ifeq ($(OSTYPE),Linux)

CC ?= gcc
CPP ?= g++

ifndef INSTALL
	INSTALL = install
endif

INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA =  $(INSTALL) -m 644



MQTT_EMBED_LIB_C = mqtt3c
MAJOR_VERSION = 1
MINOR_VERSION = 0
VERSION = ${MAJOR_VERSION}.${MINOR_VERSION}
EMBED_MQTTLIB_C_TARGET = ./lib/mqtt/lib/lib$(MQTT_EMBED_LIB_C).so.${VERSION}
LDFLAGS_C = -shared -Wl,-soname,lib$(MQTT_EMBED_LIB_C).so
SOURCE_FILES_C = ./lib/mqtt/src/MQTTPacket/src/*.c
HEADERS_C = ./lib/mqtt/src/MQTTPacket/src/*.h
TRANSPORT_LAYER_FILES_C = ./lib/mqtt/src/MQTTPacket/samples/transport.c

C_LIBS +=  \
-L"/usr/lib" -lmraa

libs: ${EMBED_MQTTLIB_C_TARGET}

all: build
	
build: | mkdir ${IoT_SN} ${IoT_RTOS} ${EMBED_MQTTLIB_C_TARGET}

clean:
	rm -rf ./bin/*
	rm -rf ./lib/mqtt/lib/*
	rm -rf $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS)	

mkdir:
	mkdir -p ./bin
	mkdir -p ./build/Debug/obj/lib
	mkdir -p ./build/Debug/obj/application
	mkdir -p ./build/Debug/bin
	mkdir -p ./lib/mqtt/lib

${IoT_SN}: ./src/main.cpp
	g++ $< ${SRC_LIBS} ${CPP_FLAGS} ${LD_FLAGS} ${C_LIBS} -o ${IoT_SN}

${IoT_RTOS}: $(OBJS) $(USER_OBJS) 
	g++ -o ${IoT_RTOS} ${OBJS} ${USER_OBJS} ${C_LIBS} 
#	g++  ./src/application/rtos_main.c ${SRC_LIBS} ${OBJS} ${USER_OBJS} ${C_LIBS} ${C_FLAGS} ${LD_FLAGS} -o ${IoT_RTOS}

${EMBED_MQTTLIB_C_TARGET}: ${SOURCE_FILES_C} ${HEADERS_C}
	gcc ${CCFLAGS_SO} -o $@ ${SOURCE_FILES_C} ${LDFLAGS_C}
	-ln -s ./lib/mqtt/lib/lib$(MQTT_EMBED_LIB_C).so.${VERSION} ./lib/mqtt/lib/lib$(MQTT_EMBED_LIB_C).so.${MAJOR_VERSION}
	-ln -s ./lib/mqtt/lib/lib$(MQTT_EMBED_LIB_C).so.${VERSION} ./lib/mqtt/lib/lib$(MQTT_EMBED_LIB_C).so

install-strip: build strip_options install

install: build
	$(INSTALL_DATA) ${INSTALL_OPTS} ./lib/mqtt/lib/lib$(MQTT_EMBED_LIB_C).so.${VERSION} $(DESTDIR)/usr/lib
	/sbin/ldconfig $(DESTDIR)/usr/lib

uninstall:
	rm $(DESTDIR)/usr/lib/lib$(MQTT_EMBED_LIB_C).so.${VERSION}
	/sbin/ldconfig $(DESTDIR)/usr/lib
	rm $(DESTDIR)/usr/lib/lib$(MQTT_EMBED_LIB_C).so


endif
