################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../core/filter.cpp \
../core/flipImage.cpp \
../core/hough.cpp \
../core/houghUtilities.cpp 

OBJS += \
./core/filter.o \
./core/flipImage.o \
./core/hough.o \
./core/houghUtilities.o 

CPP_DEPS += \
./core/filter.d \
./core/flipImage.d \
./core/hough.d \
./core/houghUtilities.d 


# Each subdirectory must supply rules for building sources it contributes
core/%.o: ../core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/cfitsio_lib_mac/include -I/Users/mrv/Documents/opencv-3.0.0/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


