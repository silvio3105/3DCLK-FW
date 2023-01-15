
######################################
# CONFIG
######################################
# CPU CORE
CPU = -mcpu=cortex-m0plus

# CHIP
CHIP = STM32L051K8

# START ADDRESS FOR .bin FILE
ADDR = 0x08000000

# OUTPUT NAME
TARGET = 3DCLK_FW

# OUTPUT LOCATION
BUILD_DIR = .build

# RELEASE BUILD
RELEASE = 0

# OPT FLAG FOR SIZE
SIZE = 0

# LAST LINE OF DEFENCE IN CASE OF ROM SHORTAGE
FLTO = 0

# USE -g3 FLAG IN NON RELEASE BUILD
USE_G3 = 0

# USE G++ INSTEAD OF GCC
GPP = 0

# GENERATE STACK ANALYSIS FILE FOR EACH TRANSLATION UNIT
STACK_ANALYSIS = 0

# WARN IF STACKOVERFLOW MIGHT HAPPEND. SET TO 0 TO DISABLE WARNING
STACK_OVERFLOW = 512

# GENERATE RUNTIME TYPE IDENTIFICATION INFORMATION
RTTI = 0

# CATCH EXCEPTIONS
EXCEPTIONS = 0

# USE DEFAULT LIB
DEF_LIB = 0

# PRINT GCC VERSION AFTER BUILD
PRINT_VER = 0

# MAKEFILE FILE NAME
MAKEFILE = mk

# JLINK SCRIPTS
FLASH_SCRIPT = JLink_Flash.jlink
ERASE_SCRIPT = JLink_Erase.jlink

# STARTUP FILE
ifeq ($(CHIP), STM32L051K8)
STARTUP = startup_stm32l051xx.s
endif

# LINKER SCRIPT FILE
ifeq ($(CHIP), STM32L051K8)
LDSCRIPT = STM32L051K8Tx_FLASH.ld
endif

######################################
# TRANSLATION UNITS
######################################
# C UNITS
C_SOURCES =  \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_adc.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rtc.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.c \
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.c \
Core/Src/system_stm32l0xx.c

# C++ UNITS
CPP_SOURCES =  \
Core/Src/main.cpp \
Core/Src/stm32l0xx_it.cpp \
Core/Src/init.cpp \
Core/Src/sStd.cpp \
Core/Src/SHT40.cpp \
Core/Src/LED.cpp \
Core/Src/TnH.cpp \
Core/Src/Log.cpp \
Core/Src/sWatchdog.cpp


# ASSEMBLER UNITS
ASM_SOURCES =  \
$(STARTUP)


######################################
# INCLUDE DIRECTORIES
######################################
# ASSEMBLER INCLUDE DIRECTORIES
AS_INCLUDES =  \


# C/C++ INCLUDE DIRECTORIES
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/STM32L0xx_HAL_Driver/Inc \
-IDrivers/CMSIS/Device/ST/STM32L0xx/Include \
-IDrivers/CMSIS/Include


######################################
# DEFINES
######################################
# ASSEMBLER DEFINES
AS_DEFS =  \


# C/C++ DEFINES
C_DEFS +=  \
-DUSE_FULL_LL_DRIVER \
-DHSE_VALUE=8000000 \
-DHSE_STARTUP_TIMEOUT=100 \
-DLSE_STARTUP_TIMEOUT=5000 \
-DLSE_VALUE=32768 \
-DMSI_VALUE=2097000 \
-DHSI_VALUE=16000000 \
-DLSI_VALUE=37000 \
-DVDD_VALUE=3300 \
-DPREFETCH_ENABLE=0 \
-DINSTRUCTION_CACHE_ENABLE=1 \
-DDATA_CACHE_ENABLE=1 \
-DSTM32L051xx


#######################################
# OPTIMIZATION
#######################################
ifeq ($(RELEASE), 0)
C_DEFS += -DDEBUG
OPT += -Og
else ifeq ($(SIZE), 1)
OPT += -Os
else
OPT += -Ofast
endif

ifeq ($(RELEASE), 0)
ifeq ($(USE_G3), 1)
CFLAGS += -g3
else
CFLAGS += -g
endif
CFLAGS += -gdwarf-2
else ifeq ($(FLTO), 1)
CFLAGS += -flto
ASFLAGS += -flto
endif


#######################################
# TOOLCHAIN BINARIES
#######################################
PREFIX = arm-none-eabi-
ifeq ($(GPP), 1)
CC = $(PREFIX)g++
AS = $(PREFIX)g++
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
endif
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 

#######################################
# C/C++ FLAGS
#######################################
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
ASFLAGS += $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -Wdouble-promotion -Wshadow -Wformat=2 -Wformat-overflow -Wformat-truncation -fdata-sections -ffunction-sections
CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -Wdouble-promotion -Wshadow -Wformat=2 -Wformat-overflow -Wformat-truncation -fdata-sections -ffunction-sections 

ifeq ($(GPP), 1)
ifeq ($(RTTI), 0)
ASFLAGS += -fno-rtti
CFLAGS += -fno-rtti
endif
endif

ifeq ($(EXCEPTIONS), 0)
ASFLAGS += -fno-exceptions
CFLAGS += -fno-exceptions
endif

ifeq ($(DEF_LIB), 0)
ASFLAGS += -nodefaultlibs
CFLAGS += -nodefaultlibs
endif

ifeq ($(STACK_ANALYSIS), 1)
ASFLAGS += -fstack-usage
CFLAGS += -fstack-usage
endif

ifneq ($(STACK_OVERFLOW), 0)
ASFLAGS += -Wstack-usage=$(STACK_OVERFLOW)
CFLAGS += -Wstack-usage=$(STACK_OVERFLOW)
endif

CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LINKER FLAGS
#######################################
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref,--gc-sections,--print-memory-usage


#######################################
# BUILD
#######################################
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# LIST OF C OBJECTS
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# LIST OF C++ OBJECTS
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

# LIST OF ASM OBJECTS
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c $(MAKEFILE) | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp $(MAKEFILE) | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s $(MAKEFILE) | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(MAKEFILE)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

ifeq ($(PRINT_VER), 1)
	$(CC) --version
endif	
	
$(BUILD_DIR):
	mkdir $@


#######################################
# FLASH CHIP
#######################################
flash: all
	if not exist $(FLASH_SCRIPT) (echo Creating flash script & (echo r& echo h& echo loadbin $(BUILD_DIR)/$(TARGET).bin,$(ADDR)& echo verifybin $(BUILD_DIR)/$(TARGET).bin,$(ADDR)& echo r& echo q) > $(FLASH_SCRIPT)) else (echo Flash script exists) 
	JLink.exe -device $(CHIP) -if SWD -speed 4000 -autoconnect 1 -CommandFile $(FLASH_SCRIPT)
	
#######################################
# ERASE CHIP FLASH MEMORY
#######################################		
erase:
	if not exist $(ERASE_SCRIPT) (echo Creating erase script & (echo r& echo h& echo erase& echo r& echo q) > $(ERASE_SCRIPT)) else (echo Erase script exists)
	JLink.exe -device $(CHIP) -if SWD -speed 4000 -autoconnect 1 -CommandFile $(ERASE_SCRIPT)
	

#######################################
# REMOVE BUILD FOLDER & OTHER STUFF
#######################################
clean:
	if exist $(BUILD_DIR) (echo Deleting build directory & rmdir /s /q $(BUILD_DIR))
	if exist $(FLASH_SCRIPT) (echo Deleting flash script & del $(FLASH_SCRIPT))
	if exist $(ERASE_SCRIPT) (echo Deleting erase script & del $(ERASE_SCRIPT))



-include $(wildcard $(BUILD_DIR)/*.d)
