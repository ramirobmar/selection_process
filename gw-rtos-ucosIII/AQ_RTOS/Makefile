

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lib/Micrium/Software/uCOS-III/Source/subdir.mk
-include lib/Micrium/Software/uCOS-III/Ports/POSIX/GNU/subdir.mk
-include lib/Micrium/Software/uC-LIB/subdir.mk
-include lib/Micrium/Software/uC-CPU/Posix/GNU/subdir.mk
-include lib/Micrium/Software/uC-CPU/subdir.mk
-include src/application/subdir.mk
-include subdir.mk
-include objects.mk

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

-include ../makefile.defs

BINFILE := $(ROOTDIR)/build/Debug/bin/AQ_RTOS

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(BINFILE)

# Tool invocations
$(BINFILE): $(OBJS) $(USER_OBJS)
	@echo 'Generando: $@'
	@echo 'Invocando: Cross G++ Linker'
	$(G++) -o $(BINFILE) $(OBJS) $(USER_OBJS) $(CLIBS)
	@echo ' '
	@echo '####################################################'
#	@echo 'Completado: $@'
	@echo 'Completado: AQ_RTOS'
	@echo 'Disponible en: build/Debug/bin'
	@echo '####################################################'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) $(BINFILE)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
