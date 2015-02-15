################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/com/ServerThread.cpp \
../src/com/SocketServer.cpp 

OBJS += \
./src/com/ServerThread.o \
./src/com/SocketServer.o 

CPP_DEPS += \
./src/com/ServerThread.d \
./src/com/SocketServer.d 


# Each subdirectory must supply rules for building sources it contributes
src/com/%.o: ../src/com/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=gnu++11 -I/usr/local/include/opencv -I/usr/local/include/opencv2 -O3 -g3 -Wall -c -fmessage-length=0 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


