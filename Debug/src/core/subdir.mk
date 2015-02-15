################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/BlobDetector.cpp \
../src/core/ThresholdCalibrator.cpp 

CC_SRCS += \
../src/core/BlobDetectorThread.cc 

OBJS += \
./src/core/BlobDetector.o \
./src/core/BlobDetectorThread.o \
./src/core/ThresholdCalibrator.o 

CC_DEPS += \
./src/core/BlobDetectorThread.d 

CPP_DEPS += \
./src/core/BlobDetector.d \
./src/core/ThresholdCalibrator.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=gnu++11 -I/usr/local/include/opencv -I/usr/local/include/opencv2 -O3 -g3 -Wall -c -fmessage-length=0 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/core/%.o: ../src/core/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=gnu++11 -I/usr/local/include/opencv -I/usr/local/include/opencv2 -O3 -g3 -Wall -c -fmessage-length=0 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


