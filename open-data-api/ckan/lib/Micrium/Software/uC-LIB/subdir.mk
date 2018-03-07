 
C_SRCS += \
$(ROOTDIR)/lib/Micrium/Software/uC-LIB/lib_ascii.c \
$(ROOTDIR)/lib/Micrium/Software/uC-LIB/lib_math.c \
$(ROOTDIR)/lib/Micrium/Software/uC-LIB/lib_mem.c \
$(ROOTDIR)/lib/Micrium/Software/uC-LIB/lib_str.c 

OBJS += \
$(ROOTDIR)/build/Debug/obj/lib/lib_ascii.o \
$(ROOTDIR)/build/Debug/obj/lib/lib_math.o \
$(ROOTDIR)/build/Debug/obj/lib/lib_mem.o \
$(ROOTDIR)/build/Debug/obj/lib/lib_str.o 

C_DEPS += \
$(ROOTDIR)/build/Debug/obj/lib/lib_ascii.d \
$(ROOTDIR)/build/Debug/obj/lib/lib_math.d \
$(ROOTDIR)/build/Debug/obj/lib/lib_mem.d \
$(ROOTDIR)/build/Debug/obj/lib/lib_str.d 


# Each subdirectory must supply rules for building sources it contributes
$(ROOTDIR)/build/Debug/obj/lib/%.o: $(ROOTDIR)/lib/Micrium/Software/uC-LIB/%.c
	@echo 'Generando fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LD_FLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizando fichero: $<'
	@echo ' '


