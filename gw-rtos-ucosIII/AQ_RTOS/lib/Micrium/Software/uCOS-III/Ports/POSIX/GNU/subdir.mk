
 
C_SRCS += \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Ports/POSIX/GNU/os_cpu_c.c 

OBJS += \
$(ROOTDIR)/build/Debug/obj/lib/os_cpu_c.o 

C_DEPS += \
$(ROOTDIR)/build/Debug/obj/lib/os_cpu_c.d 


# Each subdirectory must supply rules for building sources it contributes
$(ROOTDIR)/build/Debug/obj/lib/os_cpu_c.o: $(ROOTDIR)/lib/Micrium/Software/uCOS-III/Ports/POSIX/GNU/os_cpu_c.c
	@echo 'Generando el fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLIBS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"Micrium/Software/uCOS-III/Ports/POSIX/GNU/os_cpu_c.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


