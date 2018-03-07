C_SRCS += \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_cfg_app.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_core.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_dbg.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_flag.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_int.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_mem.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_mon.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_msg.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_mutex.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_pend_multi.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_prio.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_q.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_sem.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_stat.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_task.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_tick.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_time.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_tmr.c \
$(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/os_var.c 

OBJS += \
$(ROOTDIR)/build/Debug/obj/lib/os_cfg_app.o \
$(ROOTDIR)/build/Debug/obj/lib/os_core.o \
$(ROOTDIR)/build/Debug/obj/lib/os_dbg.o \
$(ROOTDIR)/build/Debug/obj/lib/os_flag.o \
$(ROOTDIR)/build/Debug/obj/lib/os_int.o \
$(ROOTDIR)/build/Debug/obj/lib/os_mem.o \
$(ROOTDIR)/build/Debug/obj/lib/os_mon.o \
$(ROOTDIR)/build/Debug/obj/lib/os_msg.o \
$(ROOTDIR)/build/Debug/obj/lib/os_mutex.o \
$(ROOTDIR)/build/Debug/obj/lib/os_pend_multi.o \
$(ROOTDIR)/build/Debug/obj/lib/os_prio.o \
$(ROOTDIR)/build/Debug/obj/lib/os_q.o \
$(ROOTDIR)/build/Debug/obj/lib/os_sem.o \
$(ROOTDIR)/build/Debug/obj/lib/os_stat.o \
$(ROOTDIR)/build/Debug/obj/lib/os_task.o \
$(ROOTDIR)/build/Debug/obj/lib/os_tick.o \
$(ROOTDIR)/build/Debug/obj/lib/os_time.o \
$(ROOTDIR)/build/Debug/obj/lib/os_tmr.o \
$(ROOTDIR)/build/Debug/obj/lib/os_var.o 

C_DEPS += \
$(ROOTDIR)/build/Debug/obj/lib/os_cfg_app.d \
$(ROOTDIR)/build/Debug/obj/lib/os_core.d \
$(ROOTDIR)/build/Debug/obj/lib/os_dbg.d \
$(ROOTDIR)/build/Debug/obj/lib/os_flag.d \
$(ROOTDIR)/build/Debug/obj/lib/os_int.d \
$(ROOTDIR)/build/Debug/obj/lib/os_mem.d \
$(ROOTDIR)/build/Debug/obj/lib/os_mon.d \
$(ROOTDIR)/build/Debug/obj/lib/os_msg.d \
$(ROOTDIR)/build/Debug/obj/lib/os_mutex.d \
$(ROOTDIR)/build/Debug/obj/lib/os_pend_multi.d \
$(ROOTDIR)/build/Debug/obj/lib/os_prio.d \
$(ROOTDIR)/build/Debug/obj/lib/os_q.d \
$(ROOTDIR)/build/Debug/obj/lib/os_sem.d \
$(ROOTDIR)/build/Debug/obj/lib/os_stat.d \
$(ROOTDIR)/build/Debug/obj/lib/os_task.d \
$(ROOTDIR)/build/Debug/obj/lib/os_tick.d \
$(ROOTDIR)/build/Debug/obj/lib/os_time.d \
$(ROOTDIR)/build/Debug/obj/lib/os_tmr.d \
$(ROOTDIR)/build/Debug/obj/lib/os_var.d 


# Each subdirectory must supply rules for building sources it contributes
$(ROOTDIR)/build/Debug/obj/lib/%.o: $(ROOTDIR)/lib/Micrium/Software/uCOS-III/Source/%.c
	@echo 'Generando el fichero: $<'
	@echo 'Invocando: Cross GCC Compiler'
	$(CC) $(LDFLAGS) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finalizado generacion: $<'
	@echo ' '


