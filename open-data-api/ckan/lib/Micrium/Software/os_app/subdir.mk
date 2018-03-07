C_SRCS += \
$(ROOTDIR)/src/application/os_app_hooks.c 

OBJS += \
$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.o 

C_DEPS += \
$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.d 



$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.o: $(ROOTDIR)/src/application/os_app_hooks.c
	@echo 'Generando el fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LDFLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizada generacion $<'
	@echo ' '


