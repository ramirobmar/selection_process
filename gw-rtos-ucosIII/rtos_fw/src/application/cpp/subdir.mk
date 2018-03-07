C_SRCS += \
$(ROOTDIR)/src/application/rtos_main.cpp

OBJS += \
$(ROOTDIR)/build/Debug/obj/application/rtos_main.o

C_DEPS += \
$(ROOTDIR)/build/Debug/obj/application/rtos_main.d 


$(ROOTDIR)/build/Debug/obj/application/rtos_main.o: $(ROOTDIR)/src/application/rtos_main.cpp
	@echo 'Generando el fichero: $<'                                            
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LD_FLAGS) $(CPP_FLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizada generacion $<'
	@echo ' '
