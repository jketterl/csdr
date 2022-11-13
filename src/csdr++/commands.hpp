/*
Copyright (c) 2021 Jakob Ketterl <jakob.ketterl@gmx.de>

This file is part of csdr++.

csdr++ is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

csdr++ is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with csdr++.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "CLI11.hpp"
#include "module.hpp"
#include "shift.hpp"
#include "power.hpp"
#include "fir.hpp"

namespace Csdr {

    class Command: public CLI::App {
        public:
            Command(std::string name, std::string description): CLI::App(description, name) {}
        protected:
            template <typename T, typename U>
            void runModule(Module<T, U>* module);
            virtual void processFifoData(std::string data) {}
            virtual size_t bufferSize() { return 10485760; }
            std::string fifoName = "";
            CLI::Option* addFifoOption();
    };

    class AgcCommand: public Command {
        public:
            AgcCommand();
        private:
            template <typename T>
            void runAgc();
            std::string format = "float";
            std::string profile = "fast";
            unsigned long int hangtime = 0;
            float attack = 0;
            float decay = 0;
            float max_gain = 65535;
            float reference = 0.8;
            float initial_gain = 1;
    };

    class FmdemodCommand: public Command {
        public:
            FmdemodCommand();
    };

    class AmdemodCommand: public Command {
        public:
            AmdemodCommand();
    };

    class DcBlockCommand: public Command {
        public:
            DcBlockCommand();
    };

    class ReduceNoiseCommand: public Command {
        public:
            ReduceNoiseCommand();
            unsigned int fftSize = 4096;
            unsigned int wndSize = 32;
            int dBthreshold = 10;
            FilterModule<float>* module;
    };

    class ConvertCommand: public Command {
        public:
            ConvertCommand();
        private:
            std::string inFormat = "float";
            std::string outFormat = "s16";
    };

    class FftCommand: public Command {
        public:
            FftCommand();
        private:
            bool isPowerOf2(unsigned int size);
            unsigned int fftSize = 0;
            unsigned int everyNSamples = 0;
            std::string window = "hamming";
    };

    class LogPowerCommand: public Command {
        public:
            LogPowerCommand();
        private:
            float add_db = 0;
    };

    class LogAveragePowerCommand: public Command {
        public:
            LogAveragePowerCommand();
        private:
            unsigned int fftSize = 0;
            unsigned int avgNumber = 0;
            float add_db = 0.0;
    };

    class FftExchangeSidesCommand: public Command {
        public:
            FftExchangeSidesCommand();
        private:
            unsigned int fftSize = 0;
    };

    class RealpartCommand: public Command {
        public:
            RealpartCommand();
    };

    class ShiftCommand: public Command {
        public:
            ShiftCommand();
        protected:
            void processFifoData(std::string data) override;
        private:
            Shift* shiftModule;
            float rate = 0.0;
    };

    class FirDecimateCommand: public Command {
        public:
            FirDecimateCommand();
        protected:
            size_t bufferSize() override { return 10 * Command::bufferSize(); }
        private:
            unsigned int decimationFactor = 1;
            float transitionBandwidth = 0.05;
            std::string window = "hamming";
    };

    class BenchmarkCommand: public Command {
        public:
            BenchmarkCommand();
    };

    class FractionalDecimatorCommand: public Command {
        public:
            FractionalDecimatorCommand();
        private:
            template <typename t>
            void runDecimator();
            std::string format = "float";
            float decimation_rate;
            unsigned int num_poly_points = 12;
            float transition = 0.03;
            std::string window = "hamming";
            bool prefilter = false;
    };

    class AdpcmCommand: public Command {
        public:
            AdpcmCommand();
        private:
            bool encode = false;
            bool decode = false;
            bool sync = false;
    };

    class FftAdpcmCommand: public Command {
        public:
            FftAdpcmCommand();
        private:
            unsigned int fftSize = 0;
    };

    class LimitCommand: public Command {
        public:
            LimitCommand();
        private:
            float maxAmplitude = 1.0f;
    };

    class PowerCommand: public Command {
        public:
            PowerCommand();
        private:
            std::string outFifoName;
            unsigned int decimation = 1;
            unsigned int reportInterval = 1;
    };

    class SquelchCommand: public Command {
        public:
            SquelchCommand();
        protected:
            void processFifoData(std::string data) override;
        private:
            Squelch* squelch;
            std::string outFifoName;
            unsigned int decimation = 1;
            unsigned int reportInterval = 1;
    };

    class DeemphasisCommand: public Command {
        public:
            DeemphasisCommand();
        private:
            unsigned int sampleRate;
            float tau = 50e-6;
    };

    class GainCommand: public Command {
        public:
            GainCommand();
        private:
            float gain = 1.0f;
    };

    class BandPassCommand: public Command {
        public:
            BandPassCommand();
        protected:
            void processFifoData(std::string data) override;
        private:
            float lowcut = 0.0f;
            float highcut = 0.0f;
            float transition = 0.0f;
            bool use_fft = 0;
            std::string window = "hamming";
            Window* windowObj;
            FilterModule<complex<float>>* module;
    };

    class DBPskDecoderCommand: public Command {
        public:
            DBPskDecoderCommand();
    };

    class VaricodeDecoderCommand: public Command {
        public:
            VaricodeDecoderCommand();
    };

    class TimingRecoveryCommand: public Command {
        public:
            TimingRecoveryCommand();
        private:
            unsigned int decimation = 0;
            float loop_gain = 0.5f;
            float max_error = 2.0f;
            bool use_q = false;
            std::string algorithm = "gardner";
    };

}
