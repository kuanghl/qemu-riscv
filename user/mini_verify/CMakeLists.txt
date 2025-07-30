
cmake_minimum_required(VERSION 3.5.1)

project(dilithium C)

# debug or release compile c flags
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE     "-Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
                                -Wshadow -Wvla -Wpointer-arith -O3 -fomit-frame-pointer")

# select Dilithium2/3/5
option(nl "set the Dilithium NIST Level(2-4x4,3-6x5,5-8x7)" 2)
if(nl)
    message(STATUS "Config: NIST Level=${nl}")
    add_definitions("-DDILITHIUM_MODE=${nl}") 
endif()

set(dilithium_PRIVATE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(dilithium_PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(dilithium STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sign.c 
                             ${CMAKE_CURRENT_SOURCE_DIR}/packing.c 
                             ${CMAKE_CURRENT_SOURCE_DIR}/polyvec.c 
                             ${CMAKE_CURRENT_SOURCE_DIR}/poly.c 
                             ${CMAKE_CURRENT_SOURCE_DIR}/ntt.c 
                             ${CMAKE_CURRENT_SOURCE_DIR}/reduce.c 
                             ${CMAKE_CURRENT_SOURCE_DIR}/rounding.c
                             ${CMAKE_CURRENT_SOURCE_DIR}/fips202.c 
                             ${CMAKE_CURRENT_SOURCE_DIR}/symmetric-shake.c)

target_include_directories(dilithium    PRIVATE ${dilithium_PRIVATE_INCLUDE_DIR}
                                        PUBLIC ${dilithium_PUBLIC_INCLUDE_DIR})

add_executable(test_pem ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
target_link_libraries(test_pem dilithium)