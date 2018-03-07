C_SRCS += \
$(ROOTDIR)/src/application/os_app_hooks.c \
$(ROOTDIR)/src/application/rtos_main.c

OBJS += \
$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.o \
$(ROOTDIR)/build/Debug/obj/application/rtos_main.o

C_DEPS += \
$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.d \
$(ROOTDIR)/build/Debug/obj/application/rtos_main.d 



$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.o: $(ROOTDIR)/src/application/os_app_hooks.c
	@echo 'Generando el fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LD_FLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizada generacion $<'
	@echo ' '

$(ROOTDIR)/build/Debug/obj/application/rtos_main.o: $(ROOTDIR)/src/application/rtos_main.c
	@echo 'Generando el fichero: $<'                                            
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LD_FLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizada generacion $<'
	@echo ' '
