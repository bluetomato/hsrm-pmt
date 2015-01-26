################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aufgabe\ 3/ArrayList.c \
../Aufgabe\ 3/TestArrayList.c \
../Aufgabe\ 3/mainBinTree.c \
../Aufgabe\ 3/reimwoerterbuch.c \
../Aufgabe\ 3/test3.c 

OBJS += \
./Aufgabe\ 3/ArrayList.o \
./Aufgabe\ 3/TestArrayList.o \
./Aufgabe\ 3/mainBinTree.o \
./Aufgabe\ 3/reimwoerterbuch.o \
./Aufgabe\ 3/test3.o 

C_DEPS += \
./Aufgabe\ 3/ArrayList.d \
./Aufgabe\ 3/TestArrayList.d \
./Aufgabe\ 3/mainBinTree.d \
./Aufgabe\ 3/reimwoerterbuch.d \
./Aufgabe\ 3/test3.d 


# Each subdirectory must supply rules for building sources it contributes
Aufgabe\ 3/ArrayList.o: ../Aufgabe\ 3/ArrayList.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 3/ArrayList.d" -MT"Aufgabe\ 3/ArrayList.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Aufgabe\ 3/TestArrayList.o: ../Aufgabe\ 3/TestArrayList.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 3/TestArrayList.d" -MT"Aufgabe\ 3/TestArrayList.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Aufgabe\ 3/mainBinTree.o: ../Aufgabe\ 3/mainBinTree.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 3/mainBinTree.d" -MT"Aufgabe\ 3/mainBinTree.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Aufgabe\ 3/reimwoerterbuch.o: ../Aufgabe\ 3/reimwoerterbuch.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 3/reimwoerterbuch.d" -MT"Aufgabe\ 3/reimwoerterbuch.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Aufgabe\ 3/test3.o: ../Aufgabe\ 3/test3.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Aufgabe 3/test3.d" -MT"Aufgabe\ 3/test3.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


