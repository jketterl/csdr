set(LIBCSDR_LIBRARY_SOURCES libcsdr.c fft_fftw.c)

if (CSDR_GPL)
    list(APPEND LIBCSDR_LIBRARY_SOURCES libcsdr_gpl.c fastddc.c)
endif()

if (CSDR_IMA_ADPCM)
    list(APPEND LIBCSDR_LIBRARY_SOURCES ima_adpcm.c)
endif()

add_library(csdr SHARED ${LIBCSDR_LIBRARY_SOURCES})
set_target_properties(csdr PROPERTIES VERSION ${PROJECT_VERSION})
file(GLOB LIBCSDR_HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
set_target_properties(csdr PROPERTIES PUBLIC_HEADER "${LIBCSDR_HEADERS}")

if (CSDR_GPL)
    target_compile_definitions(csdr PUBLIC "-DLIBCSDR_GPL")
endif()

if(CSDR_HAS_LIBM)
    target_link_libraries(csdr m)
endif()

if (FFTW3_FOUND)
    target_compile_definitions(csdr PUBLIC "-DUSE_FFTW")
    target_link_libraries(csdr ${FFTW3_LIBRARIES})
endif()

if (CSDR_IMA_ADPCM)
    target_compile_definitions(csdr PUBLIC "-DUSE_IMA_ADPCM")
endif()

if (HAS_IFUNC)
    target_compile_definitions(csdr PUBLIC "-DCSDR_FMV")
endif()

if (HAS_NEON)
    target_compile_definitions(csdr PUBLIC "-DNEON_OPTS")
endif()

install(TARGETS csdr
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

add_executable(csdr-bin csdr.c benchmark.c)
set_target_properties(csdr-bin PROPERTIES OUTPUT_NAME csdr)
target_link_libraries(csdr-bin csdr)
install(TARGETS csdr-bin DESTINATION ${CMAKE_INSTALL_BINDIR})

if(FFTW3_FOUND)
    set(FFTW3F_REQUIRES "Requires: fftw3f")
endif()
configure_file(csdr.pc.in csdr.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/csdr.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

install(EXPORT CsdrTargets
    FILE CsdrTargets.cmake
    NAMESPACE Csdr::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Csdr
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/CsdrConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Csdr
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CsdrConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CsdrConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CsdrConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Csdr
)

add_subdirectory(lib)
add_subdirectory(csdr++)
add_subdirectory(nmux)