PLATFORM ?= nrf52840
TARGET = app-$(PLATFORM)
BUILD_DIR := build

# Path
REPO_DIR = $(shell git rev-parse --show-toplevel)
NRF_MDK_DIR = $(REPO_DIR)/vendor/nrfx/mdk
ARM_CMSIS_DIR = $(REPO_DIR)/vendor/CMSIS_5/CMSIS

# Architectures Specific Flags
LINKER_FILE = $(NRF_MDK_DIR)/nrf52840_xxaa.ld
CPU = cortex-m4
ISA_ARCH = thumb
# Skip standard lib for now
# SPECS = nano.specs

# Compile Tools
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
SIZETOOL = arm-none-eabi-size
DUMPTOOL = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy

#  Target specific flags
TARGET_SPECIFIC_FLAGS = -mcpu=$(CPU) \
						-m$(ISA_ARCH) \
						-mfloat-abi=hard -mfpu=fpv4-sp-d16

#Compiler Flags
CFLAGS =  -g -O0 -Wall -Werror -std=gnu11 \
			$(TARGET_SPECIFIC_FLAGS)

# Include directories
CFLAGS += -I$(NRF_MDK_DIR)
CFLAGS += -I$(ARM_CMSIS_DIR)/Core/Include

#Linker Flags
LDFLAGS = $(TARGET_SPECIFIC_FLAGS)\
		  -nostdlib \
          -Wl,-Map=$(BUILD_DIR)/$(TARGET).map \
		  -Wl,-L$(NRF_MDK_DIR) \
		  -T $(LINKER_FILE)

# Required nRF mdk defines
ifeq ($(PLATFORM), nrf52840)
	CFLAGS += -DNRF52840_XXAA
else ifeq ($(PLATFORM), nrf52832)
	CFLAGS += -DNRF52832_XXAA
endif

# Define entry point as main (skipping stdlib)
CFLAGS += -D__START=main

# Source files
SRCS = main.c \
         $(NRF_MDK_DIR)/gcc_startup_$(PLATFORM).S \
		 $(NRF_MDK_DIR)/system_$(PLATFORM).c

# Normalize all paths to absolute, then make object paths under build/
ABS_SRCS := $(realpath $(SRCS))
OBJS := $(patsubst /%, build/%.o, $(ABS_SRCS))

# Building and linking to obtain the final target
.PHONY: all
all:$(BUILD_DIR)/$(TARGET).hex

#Generating the object files
$(BUILD_DIR)/%.o : /%
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

$(BUILD_DIR)/%.hex : $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O ihex $^ $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Cleaning all non-source files and executables
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
