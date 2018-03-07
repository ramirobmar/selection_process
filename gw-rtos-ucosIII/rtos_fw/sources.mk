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

LD_FLAGS := -I $(ROOTDIR)/lib/Micrium/Software/uC-CPU \
-I $(ROOTDIR)/include \
-I $(ROOTDIR)/lib/Micrium/Software/uC-CPU/Posix/GNU \
-I $(ROOTDIR)/lib/Micrium/Software/uC-LIB \
-I $(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source \
-I $(ROOTDIR)/lib/Micrium/Software/uCOS-III/Ports/POSIX/GNU 


  
CFLAGS := -O0 -g3 -Wall -c -fmessage-length=0 -fstrict-aliasing -Wall -Wextra \
-Wunused-function -std=gnu99


CPPFLAGS := -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++98 -fno-rtti \
-fstrict-aliasing -Wall -Wunused-function


LIBDIR :=  

C_LIBS :=  \
-L"/usr/lib/i586-poky-linux/4.9.1" -lgcc \
-L"/usr/lib" -lstdc++ \
-L"/usr/lib" -lm \
-L"/usr/lib" -ldl \
-L"/usr/lib" -lcrypt \
-L"/usr/lib" -lc \
-L"/usr/lib" -lrt \
-L"/usr/lib" -lcurl \
-L"/usr/lib" -lpthread 
