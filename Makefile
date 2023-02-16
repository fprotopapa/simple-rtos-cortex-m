TARGET ?= main

ST_UC ?= STM32F401xE
M_ARCH ?= cortex-m4
M_FPU ?= fpv4-sp-d16
M_FLOAT ?= soft


TOOLCHAIN ?= arm-none-eabi-
LINKER_SCRIPT ?= $(wildcard $(SRC_DIR)/*.ld)
BUILD_DIR ?= build

SRC_DIR = src
INC_DIR = include

CC = $(TOOLCHAIN)gcc
DB = $(TOOLCHAIN)gdb
AS = $(TOOLCHAIN)gcc 
OC = $(TOOLCHAIN)objcopy
SZ = $(TOOLCHAIN)size
HEX = $(OC) -O ihex
BIN = $(OC) -O binary -S

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.s) $(wildcard $(SRC_DIR)/*/*.s)
LD_SCRIPT = $(LINKER_SCRIPT)
INCLUDES   = -I$(INC_DIR)

DEFS =  \
-D$(ST_UC)

CPU = -mcpu=$(M_ARCH)
FPU = -mfpu=$(M_FPU)
FLOAT-ABI = -mfloat-abi=$(M_FLOAT)

MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

AS_INCLUDES =
AS_DEFS = 
LIBS = -lc -lm -lnosys 

DEBUG_FLAGS = -g -O0 -Wextra -Warray-bounds 
CFLAGS = $(MCU)
CFLAGS += $(DEBUG_FLAGS)
CFLAGS += $(DEFS) $(INCLUDES) -Wall -fcommon -fdata-sections -ffunction-sections 
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
LDFLAGS = $(MCU) -specs=nano.specs -T$(LD_SCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref,--gc-sections

C_OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_FILES)))
ASM_OBJ = $(patsubst %.s,$(BUILD_DIR)/%.o,$(notdir $(ASM_FILES)))
OBJ = $(C_OBJ) $(ASM_OBJ)

.PHONY: all clean

vpath %.s src
vpath %.c src

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo '[CC] -c $< -o $@'
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR) 
	@echo '[AS] -c $< -o $@'
	@$(AS) -c $(ASFLAGS) $< -o $@ 

$(BUILD_DIR)/$(TARGET).elf: $(OBJ)
	@echo '[LD] $(OBJ) -o $@'
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@
	@echo '----------------------------------'
	$(SZ) $@
	@echo ' '

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf  | $(BUILD_DIR) 
	@echo '[HEX] $@'
	@$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf  | $(BUILD_DIR) 
	@echo '[BIN] $@'
	@$(BIN) $< $@	

$(BUILD_DIR):
	@mkdir -p $@

clean: 
	rm -rf build

debug:
	st-util

flash:
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

