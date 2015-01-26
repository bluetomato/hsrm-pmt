################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aufgabe\ 2/BMP.c \
../Aufgabe\ 2/test2.c 

OBJS += \
./Aufgabe\ 2/BMP.o \
./Aufgabe\ 2/test2.o 

C_DEPS += \
./Aufgabe\ 2/BMP.d \
./Aufgabe\ 2/test2.d 


# Each subdirectory must supply rules for building sources it contributes
Aufgabe\ 2/BMP.o: ../Aufgabe\ 2/BMP.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 2/BMP.d" -MT"Aufgabe\ 2/BMP.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Aufgabe\ 2/test2.o: ../Aufgabe\ 2/test2.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 2/test2.d" -MT"Aufgabe\ 2/test2.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


