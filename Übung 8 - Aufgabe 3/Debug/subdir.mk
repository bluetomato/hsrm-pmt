################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ArrayList.c \
../TestArrayList.c \
../mainBinTree.c \
../reimwoerterbuch.c \
../test3.c 

OBJS += \
./ArrayList.o \
./TestArrayList.o \
./mainBinTree.o \
./reimwoerterbuch.o \
./test3.o 

C_DEPS += \
./ArrayList.d \
./TestArrayList.d \
./mainBinTree.d \
./reimwoerterbuch.d \
./test3.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


