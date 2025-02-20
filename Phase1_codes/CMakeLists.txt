cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MiniProject1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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

# Include directories
target_include_directories(MiniProject1 PRIVATE
    ${PROJECT_SOURCE_DIR}
)

# Add any additional libraries if needed
# target_link_libraries(MiniProject1 <library_name>)