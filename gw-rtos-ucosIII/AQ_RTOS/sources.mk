ROOTDIR := $(shell pwd)

TOOLCHAIN :=

CC := $(TOOLCHAIN)gcc
G++ := $(TOOLCHAIN)g++ 

O_SRCS := 
CPP_SRCS := 
C_UPPER_SRCS := 
C_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
CXX_SRCS := 
C++_SRCS := 
CC_SRCS := 
C++_DEPS := 
OBJS := 
C_DEPS := 
CC_DEPS := 
CPP_DEPS := 
EXECUTABLES := 
CXX_DEPS := 
C_UPPER_DEPS := 

# Every subdirectory with source files must be described here
SUBDIRS := \
$(ROOTDIR)/src/application \
$(ROOTDIR)/lib/Micrium/Software/uC-CPU/Posix/GNU \
$(ROOTDIR)/lib/Micrium/Software/uC-CPU \
$(ROOTDIR)/lib/Micrium/Software/uC-LIB \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Ports/POSIX/GNU \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source 

LDFLAGS := -I $(ROOTDIR)/lib/Micrium/Software/uC-CPU \
-I $(ROOTDIR)/include \
-I $(ROOTDIR)/lib/Micrium/Software/uC-CPU/Posix/GNU \
-I $(ROOTDIR)/lib/Micrium/Software/uC-LIB \
-I $(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source \
-I $(ROOTDIR)/lib/Micrium/Software/uCOS-III/Ports/POSIX/GNU \
-I $(ROOTDIR)/include/libxively \
-I $(ROOTDIR)/lib/mqtt


XI_WARN_CFLAGS ?= -Wall -Wextra
XI_CFLAGS += -std=gnu99 -Iinclude -fstrict-aliasing
XI_CFLAGS += $(XI_WARN_CFLAGS) $(XI_EXTRA_CFLAGS)
  

CFLAGS := -O0 -g3 -Wall -c -fmessage-length=0 $(XI_CFLAGS) -Wunused-function

LIBDIR := -L/usr/lib32 \
-L/usr/lib/x86_64-linux-gnu  

CLIBS := -L"/usr/lib/x86_64-linux-gnu" -lpthread \
-L"/usr/lib32" -lm -ldl -lcrypt -lc -lrt  \
-L$(ROOTDIR)/lib/libxively/obj -lxively \
-L$(ROOTDIR)/lib/mqtt -lmqttc

