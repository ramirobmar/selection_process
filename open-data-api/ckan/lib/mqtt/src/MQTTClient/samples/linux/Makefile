#*******************************************************************************
#  Copyright (c) 2009, 2014 IBM Corp.
# 
#  All rights reserved. This program and the accompanying materials
#  are made available under the terms of the Eclipse Public License v1.0
#  and Eclipse Distribution License v1.0 which accompany this distribution. 
# 
#  The Eclipse Public License is available at 
#     http://www.eclipse.org/legal/epl-v10.html
#  and the Eclipse Distribution License is available at 
#    http://www.eclipse.org/org/documents/edl-v10.php.
# 
#  Contributors:
#     Xiang Rong - 442039 Add makefile to Embedded C client
#*******************************************************************************/
# Note: on OS X you should install XCode and the associated command-line tools

SHELL = /bin/sh
.PHONY: clean, mkdir, install, uninstall, html 

# assume this is normally run in the main Paho directory
ifndef srcdir
  srcdir = MQTTPacket/src
endif

ifndef blddir
  blddir = build/output
endif

ifndef clientdir
	clientdir = $(shell pwd)
endif

ifndef prefix
	prefix = /usr/local
endif

ifndef exec_prefix
	exec_prefix = ${prefix}
endif

bindir = $(exec_prefix)/bin
includedir = $(prefix)/include
libdir = $(exec_prefix)/lib

SOURCE_FILES_C = $(srcdir)/*.c
HEADERS = $(srcdir)/*.h


SAMPLE_FILES_C = pub0sub1 qos0pub
SYNC_SAMPLES = ${addprefix ${blddir}/samples/,${SAMPLE_FILES_C}}

TRANSPORT_LAYER_FILES_C = transport.c
TRANSPORT_LAYER_SYNC = ../../../MQTTPacket/samples/${TRANSPORT_LAYER_FILES_C}


TEST_FILES_C = test1
SYNC_TESTS = ${addprefix ${blddir}/test/,${TEST_FILES_C}}


SRC := ${clientdir}/../../../MQTTPacket/src/MQTTPacket.c
SRC += ${clientdir}/../../../MQTTPacket/src/MQTTDeserializePublish.c
SRC += ${clientdir}/../../../MQTTPacket/src/MQTTConnectClient.c
SRC += ${clientdir}/../../../MQTTPacket/src/MQTTSubscribeClient.c
SRC += ${clientdir}/../../../MQTTPacket/src/MQTTSerializePublish.c
SRC += ${clientdir}/../../../MQTTPacket/src/MQTTUnsubscribeClient.c


CLIENTS = bin/hello 



# The names of libraries to be built
MQTT_EMBED_LIB_C = paho-embed-mqtt3c


# determine current platform
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

MAJOR_VERSION = 1
MINOR_VERSION = 0
VERSION = ${MAJOR_VERSION}.${MINOR_VERSION}

EMBED_MQTTLIB_C_TARGET = ${blddir}/lib${MQTT_EMBED_LIB_C}.so.${VERSION}

CLIBS = -L"/usr/lib/i586-poky-linux/4.9.1" -lgcc -L "/usr/lib" -lstdc++ -lm -ldl -lcrypt -lc -lrt -lmqtt3c 
CCFLAGS_SO = -g -fPIC -Os -Wall -fvisibility=hidden -DLINUX_SO
FLAGS_EXE = -I ../../../MQTTClient/src -I ../../../MQTTPacket/src -I ../../src/linux
LDFLAGS_C = -shared -Wl,-soname,libmqtt3c.so 


all: build
	
build: | mkdir ${CLIENTS}

clean:
	rm -rf ${clientdir}/bin/hello
	
mkdir:
	mkdir -p ${clientdir}/bin
	mkdir -p ${clientdir}/../../../bin

${CLIENTS}: ${clientdir}/hello.cpp
	g++ $< ${FLAGS_EXE} -o ${CLIENTS} ${SRC} ${TRANSPORT_LAYER_SYNC}  

endif

