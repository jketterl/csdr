# Copyright (c) 2021-2022 Jakob Ketterl <jakob.ketterl@gmx.de>
#
# This file is part of libcsdr.
#
# libcsdr is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libcsdr is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libcsdr.  If not, see <https://www.gnu.org/licenses/>.

add_library(csdr++ SHARED module.cpp ringbuffer.cpp writer.cpp agc.cpp fmdemod.cpp amdemod.cpp dcblock.cpp converter.cpp fft.cpp window.cpp logpower.cpp logaveragepower.cpp fftexchangesides.cpp realpart.cpp shift.cpp firdecimate.cpp fir.cpp benchmark.cpp reader.cpp fractionaldecimator.cpp adpcm.cpp limit.cpp power.cpp deemphasis.cpp gain.cpp filter.cpp fftfilter.cpp noisefilter.cpp dbpsk.cpp varicode.cpp timingrecovery.cpp async.cpp source.cpp sink.cpp audioresampler.cpp downmix.cpp version.cpp)
set_target_properties(csdr++ PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
file(GLOB LIBCSDR_HEADERS "${PROJECT_SOURCE_DIR}/include/*.hpp")
set_target_properties(csdr++ PROPERTIES PUBLIC_HEADER "${LIBCSDR_HEADERS}")
target_link_libraries(csdr++ ${FFTW3_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${SAMPLERATE_LIBRARIES})
target_compile_definitions(csdr++ PRIVATE "-D_GNU_SOURCE")

if (HAS_IFUNC)
    target_compile_definitions(csdr++ PUBLIC "-DCSDR_FMV")
endif()

install(TARGETS csdr++
    EXPORT CsdrTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/csdr"
)
