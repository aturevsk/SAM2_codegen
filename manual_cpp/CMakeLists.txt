cmake_minimum_required(VERSION 3.16)
project(sam2_manual CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Release flags — optimised for Apple Silicon
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native -ffast-math -funroll-loops")

# Source files
set(SOURCES
    main.cpp
    sam2.cpp
    sam2_ops.cpp
    sam2_hiera.cpp
    sam2_decoder.cpp
)

add_executable(sam2_manual ${SOURCES})
target_include_directories(sam2_manual PRIVATE ${CMAKE_SOURCE_DIR})

# Accelerate framework (macOS BLAS/LAPACK)
if(APPLE)
    target_link_libraries(sam2_manual "-framework Accelerate")
    message(STATUS "Linking with Accelerate (BLAS)")
endif()

# OpenMP (optional speedup for loops — disable to not disturb training)
find_package(OpenMP)
if(OpenMP_CXX_FOUND AND NOT "$ENV{NO_OMP}" STREQUAL "1")
    target_link_libraries(sam2_manual OpenMP::OpenMP_CXX)
    message(STATUS "OpenMP enabled")
else()
    message(STATUS "OpenMP disabled (set NO_OMP=0 to enable)")
endif()
