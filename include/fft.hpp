/*
Copyright (c) 2021 Jakob Ketterl <jakob.ketterl@gmx.de>

This file is part of libcsdr.

libcsdr is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "module.hpp"
#include "complex.hpp"
#include "window.hpp"

#include <fftw3.h>

namespace Csdr {

    class Fft: public Module<complex<float>, complex<float>> {
        public:
            Fft(unsigned int fftSize, unsigned int everyNSamples, Window* window = nullptr);
            ~Fft() override;
            bool canProcess() override;
            void process() override;
            void setEveryNSamples(unsigned int everyNSamples);
        private:
            unsigned int fftSize;
            unsigned int everyNSamples;
            unsigned int skipped = 0;
            PrecalculatedWindow* window;
            fftwf_plan plan;
            complex<float>* windowed;
            complex<float>* output_buffer;
    };

}