################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aufgabe\ 1/BMP.c \
../Aufgabe\ 1/test.c 

OBJS += \
./Aufgabe\ 1/BMP.o \
./Aufgabe\ 1/test.o 

C_DEPS += \
./Aufgabe\ 1/BMP.d \
./Aufgabe\ 1/test.d 


# Each subdirectory must supply rules for building sources it contributes
Aufgabe\ 1/BMP.o: ../Aufgabe\ 1/BMP.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 1/BMP.d" -MT"Aufgabe\ 1/BMP.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Aufgabe\ 1/test.o: ../Aufgabe\ 1/test.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 1/test.d" -MT"Aufgabe\ 1/test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


