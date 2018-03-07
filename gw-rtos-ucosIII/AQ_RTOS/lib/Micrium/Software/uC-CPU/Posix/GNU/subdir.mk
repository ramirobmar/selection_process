 
C_SRCS += \
$(ROOTDIR)/lib/Micrium/Software/uC-CPU/Posix/GNU/cpu_c.c 

OBJS += \
$(ROOTDIR)/build/Debug/obj/lib/cpu_c.o 

C_DEPS += \
$(ROOTDIR)/build/Debug/obj/lib/cpu_c.d 


# Each subdirectory must supply rules for building sources it contributes
$(ROOTDIR)/build/Debug/obj/lib/%.o: $(ROOTDIR)/lib/Micrium/Software/uC-CPU/Posix/GNU/%.c
	@echo 'Generando fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LDFLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizando fichero: $<'
	@echo ' '


