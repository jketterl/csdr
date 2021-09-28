cmake_minimum_required (VERSION 3.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL None)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

project (csdr VERSION 0.18.0)
add_definitions(-DVERSION="${PROJECT_VERSION}-dev")

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

find_package(Threads REQUIRED)

include(CheckLibraryExists)
check_library_exists(m floorf "" CSDR_HAS_LIBM)

include(FindPkgConfig)
pkg_check_modules(FFTW3 REQUIRED fftw3f)

include(cmake/DetectIfunc.cmake)

pkg_check_modules(SAMPLERATE REQUIRED samplerate)

pkg_check_modules(PULSEAUDIO REQUIRED libpulse-simple)

if(NOT DEFINED CSDR_GPL)
    set(CSDR_GPL true)
endif()

if(NOT DEFINED CSDR_IMA_ADPCM)
    set(CSDR_IMA_ADPCM true)
endif()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    SET(CMAKE_CXX_FLAGS "-ffast-math -mfpmath=sse")
    SET(CMAKE_C_FLAGS "-ffast-math -mfpmath=sse")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES ^arm.*)
    execute_process(COMMAND "cat" "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)
    string(FIND ${CPUINFO} "neon" NEON_POSITION)
    if(NEON_POSITION GREATER_EQUAL 0)
        set(HAS_NEON true)
    endif()
    if (HAS_NEON)
        SET(CMAKE_CXX_FLAGS "-ffast-math -march=armv7-a -mtune=cortex-a8 -funsafe-math-optimizations -Wformat=0 -mfloat-abi=hard -mfpu=neon -mvectorize-with-neon-quad")
        SET(CMAKE_C_FLAGS "-ffast-math -march=armv7-a -mtune=cortex-a8 -funsafe-math-optimizations -Wformat=0 -mfloat-abi=hard -mfpu=neon -mvectorize-with-neon-quad")
    else()
        SET(CMAKE_CXX_FLAGS "-ffast-math -march=armv7-a -mtune=cortex-a8 -funsafe-math-optimizations -Wformat=0")
        SET(CMAKE_C_FLAGS "-ffast-math -march=armv7-a -mtune=cortex-a8 -funsafe-math-optimizations -Wformat=0")
    endif()
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES ^aarch64.*)
    # aarch64 mandated neon
    set(HAS_NEON true)
    SET(CMAKE_CXX_FLAGS "-ffast-math -march=armv8-a -mtune=cortex-a72 -funsafe-math-optimizations -Wformat=0")
    SET(CMAKE_C_FLAGS "-ffast-math -march=armv8-a -mtune=cortex-a72 -funsafe-math-optimizations -Wformat=0")
endif()

SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_C_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -O3")
SET(CMAKE_C_FLAGS_DEBUG "-g -O3")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3 -DNDEBUG")
SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -O3 -DNDEBUG")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)
