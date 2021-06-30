#pragma once

#include "CLI11.hpp"
#include "module.hpp"

namespace Csdr {

    class Command: public CLI::App {
        public:
            Command(std::string name, std::string description): CLI::App(description, name) {}
        protected:
            template <typename T, typename U>
            void runModule(Module<T, U>* module);
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

}