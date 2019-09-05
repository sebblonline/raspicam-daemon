# Toolchain file for cross-compiling

# Define our host system
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

# Define the cross compiler locations
SET(CMAKE_C_COMPILER   $ENV{HOME}/devel/raspberrypi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)
#SET(CMAKE_C_COMPILER   $ENV{HOME}/devel/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER $ENV{HOME}/devel/raspberrypi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)
#SET(CMAKE_CXX_COMPILER $ENV{HOME}/devel/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-g++)

#SET(CMAKE_SYSROOT $ENV{HOME}/devel/raspberrypi/rootfs)
# Define the sysroot path for the RaspberryPi distribution in our tools folder
#SET(CMAKE_FIND_ROOT_PATH /home/sebastian/devel/raspberrypi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot/)
SET(CMAKE_FIND_ROOT_PATH $ENV{HOME}/devel/raspberrypi/rootfs)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --sysroot=${CMAKE_FIND_ROOT_PATH}")

# Use our definitions for compiler tools
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers in the target directories only
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(Boost_INCLUDE_DIR ${CMAKE_FIND_ROOT_PATH}/usr/include)
SET(Boost_LIBRARY_DIR ${CMAKE_FIND_ROOT_PATH}/usr/lib)
