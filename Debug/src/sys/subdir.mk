################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sys/Timer.cpp 

CC_SRCS += \
../src/sys/BaseThread.cc \
../src/sys/FdTimer.cc 

OBJS += \
./src/sys/BaseThread.o \
./src/sys/FdTimer.o \
./src/sys/Timer.o 

CC_DEPS += \
./src/sys/BaseThread.d \
./src/sys/FdTimer.d 

CPP_DEPS += \
./src/sys/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/sys/%.o: ../src/sys/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=gnu++11 -I/usr/local/include/opencv -I/usr/local/include/opencv2 -O3 -g3 -Wall -c -fmessage-length=0 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/%.o: ../src/sys/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=gnu++11 -I/usr/local/include/opencv -I/usr/local/include/opencv2 -O3 -g3 -Wall -c -fmessage-length=0 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


