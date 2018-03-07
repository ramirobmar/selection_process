
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


C_LIBS +=  \
-L"/usr/lib" -lmraa


all: build
	
build: | mkdir ${IoT_SN} ${IoT_RTOS}
 

clean:
#	rm -rf ./bin/*
	rm -rf $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS)	
mkdir:
	mkdir -p ./bin
	mkdir -p ./build/Debug/obj/lib
	mkdir -p ./build/Debug/obj/application
	mkdir -p ./build/Debug/bin

${IoT_SN}: ./src/main.cpp
	g++ $< ${SRC_LIBS} ${CPP_FLAGS} ${LD_FLAGS} ${C_LIBS} -o ${IoT_SN}

${IoT_RTOS}: $(OBJS) $(USER_OBJS) 
	g++ -o ${IoT_RTOS} ${OBJS} ${USER_OBJS} ${C_LIBS} 
#	g++  ./src/application/rtos_main.c ${SRC_LIBS} ${OBJS} ${USER_OBJS} ${C_LIBS} ${C_FLAGS} ${LD_FLAGS} -o ${IoT_RTOS}
endif
