C_SRCS += \
$(ROOTDIR)/src/application/app.c \
$(ROOTDIR)/src/application/os_app_hooks.c \
$(ROOTDIR)/src/application/datahandler.c \
$(ROOTDIR)/src/application/mqtt_client.c

OBJS += \
$(ROOTDIR)/build/Debug/obj/application/app.o \
$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.o \
$(ROOTDIR)/build/Debug/obj/application/datahandler.o \
$(ROOTDIR)/build/Debug/obj/application/mqtt_client.o

C_DEPS += \
$(ROOTDIR)/build/Debug/obj/application/app.d \
$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.d \
$(ROOTDIR)/build/Debug/obj/application/datahandler.d \
$(ROOTDIR)/build/Debug/obj/application/mqtt_client.d 


$(ROOTDIR)/build/Debug/obj/application/app.o: $(ROOTDIR)/src/application/app.c
	@echo 'Generando el fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LDFLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizado generacion: $<'
	@echo ' '

$(ROOTDIR)/build/Debug/obj/application/os_app_hooks.o: $(ROOTDIR)/src/application/os_app_hooks.c
	@echo 'Generando el fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LDFLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizada generacion $<'
	@echo ' '

$(ROOTDIR)/build/Debug/obj/application/datahandler.o: $(ROOTDIR)/src/application/datahandler.c
	@echo 'Generando el fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LDFLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizada generacion $<'
	@echo ' '


$(ROOTDIR)/build/Debug/obj/application/mqtt_client.o: $(ROOTDIR)/src/application/mqtt_client.c
	@echo 'Generando el fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LDFLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizada genaracion $<'
	@echo ' '

