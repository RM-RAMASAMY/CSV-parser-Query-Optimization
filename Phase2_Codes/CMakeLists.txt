cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MiniProject1)

# compilers to use (9.2)
set(CMAKE_C_COMPILER /opt/homebrew/Cellar/gcc/11.2.0_3/bin/gcc-11)
set(CMAKE_CXX_COMPILER  /opt/homebrew/Cellar/gcc/11.2.0_3/bin/g++-11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

# openmp flags
#SET(OPENMP_CXX_FLAGS "-O3 -fopenmp --target=x86_64-pc-linux-gnu")
SET(OPENMP_CXX_FLAGS "-O3 -fopenmp")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS}" )

# Add the executable
add_executable(MiniProject1
    main.cpp
    RecTimeStamp.h
    RecPlace.h
    RecPeople.h
    RecVehicle.h
    CrashRecord.h
    RecReader.h
    search.h
)
