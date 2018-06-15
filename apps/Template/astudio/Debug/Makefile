################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../stack/ \
../stack/phy/ \
../stack/phy/atmegarfr2/ \
../stack/phy/atmegarfr2/inc \
../stack/phy/atmegarfr2/src


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../../../../phy/atmegarfr2/src/phy.c \
../../template.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
stack/phy/atmegarfr2/src/phy.o \
template.o

OBJS_AS_ARGS +=  \
stack/phy/atmegarfr2/src/phy.o \
template.o

C_DEPS +=  \
stack/phy/atmegarfr2/src/phy.d \
template.d

C_DEPS_AS_ARGS +=  \
stack/phy/atmegarfr2/src/phy.d \
template.d

OUTPUT_FILE_PATH +=Template.elf

OUTPUT_FILE_PATH_AS_ARGS +=Template.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler





stack/phy/atmegarfr2/src/%.o: ../../../../phy/atmegarfr2/src/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DPHY_ATMEGARFR2 -DHAL_ATMEGA256RFR2 -DPLATFORM_XPLAINED_PRO_ATMEGA256RFR2 -DF_CPU=8000000  -I"../../../../hal/atmega256rfr2/inc" -I"../../../../phy/atmegarfr2/inc" -I"../../../../nwk/inc" -I"../../../../sys/inc" -I"../.."  -Os -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atmega256rfr2 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./%.o: ../../%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DPHY_ATMEGARFR2 -DHAL_ATMEGA256RFR2 -DPLATFORM_XPLAINED_PRO_ATMEGA256RFR2 -DF_CPU=8000000  -I"../../../../hal/atmega256rfr2/inc" -I"../../../../phy/atmegarfr2/inc" -I"../../../../nwk/inc" -I"../../../../sys/inc" -I"../.."  -Os -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atmega256rfr2 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Template.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega256rfr2  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Template.elf" "Template.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-size.exe" "Template.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Template.elf" "Template.a" "Template.hex" "Template.lss" "Template.eep" "Template.map" "Template.srec" "Template.usersignatures"
	