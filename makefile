#
# The project name is the name of current directory
#
PROJ_NAME=$(shell basename $(CURDIR))

#
# C compiler for ARM Cortex
#
CC=arm-none-eabi-gcc

#
# The command for calling the linker
#
LD=arm-none-eabi-ld

#
# Macros for Tiva TM4C123GH6PM
#
TIVA_MACROS=-DPART_TM4C123GH6PM       \
            -DTARGET_IS_TM4C123_RB1

#
# Set the compiler CPU/FPU options.
#
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=hard

#
# The flags passed to the compiler.
#
CFLAGS=-c                             \
       -O0                            \
       $(TIVA_MACROS)                 \
       -I$(TIVA_LIB)                  \
       -mthumb                        \
       ${CPU}                         \
       ${FPU}                         \
       -ffunction-sections            \
       -fdata-sections                \
       -MD                            \
       -std=c99                       \
       -Wall                          \
       -MMD                           \
       -MP                            \
       -MF"$(@:%.o=%.d)"              \
       -MT"$(@)"

#
# Libraries used in the project.
#
LIBS=-ldriver

#
# The flags passed to the linker.
#
LDFLAGS=-L$(TIVA_LIB_DRIVER)          \
        $(LIBS)                       \
        --gc-sections                 \
        --static                      \
        -T                            \
        ./def/project.ld

#
# Sources to .c and .h
#
CSOURCES=$(wildcard ./src/*.c)

#
# Objects and dependencies files from .c files
#
OBJ=$(subst .c,.o,$(subst ./,./Debug/,$(CSOURCES)))
DEPS=$(subst .c,.d,$(subst ./,./Debug/,$(CSOURCES)))

#
# Making the binary
#
all: debugFolder $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(OBJ)
	@ echo 'Building target: $@'
	@ echo 'Invoking: Cross GCC Linker'
	$(LD) $(OBJ) $(LDFLAGS) -o $@ 
	@ echo 'Finished building target: $@'
	@ echo ' '
	@ $(MAKE) --no-print-directory post-build

./Debug/src/%.o: ./src/%.c
	@ echo 'Building file: $<'
	$(CC) $< $(CFLAGS) -o $@
	@ echo ' '

debugFolder:
	@ test -d Debug || echo "Creating Debug folder"
	@ test -d Debug || mkdir Debug
	@ test -d ./Debug/src || echo "Creating src folder inside Debug folder"
	@ test -d ./Debug/src || mkdir ./Debug/src
	@ echo ' '

post-build:
	@ echo 'Generate binary file from elf file'
	arm-none-eabi-objcopy -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	@ echo ' '

#
# Other Targets
#
clean:
	@ rm -rf $(OBJ) $(DEPS) $(PROJ_NAME).elf $(PROJ_NAME).bin *~
	@ rmdir -p Debug/src

flash:
	@ echo 'Flashing into device...'
	@ $(TIVA_FLASH)/dslite.sh --mode flash --config=$(CURDIR)/def/tm4c123gh6pm.ccxml $(CURDIR)/$(PROJ_NAME).elf

.PHONY: all clean

.SECONDARY: post-build
