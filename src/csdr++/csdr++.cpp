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

#include "csdr++.hpp"
#include "ringbuffer.hpp"
#include "writer.hpp"
#include "agc.hpp"
#include "commands.hpp"

#include <iostream>

#include "CLI11.hpp"

using namespace Csdr;

int main (int argc, char** argv) {
    Cli server;
    return server.main(argc, argv);
}

int Cli::main(int argc, char** argv) {
    CLI::App app;

    CLI::Option* version_flag = app.add_flag("-v,--version", "Display version information");
    app.add_flag("-a,--async", "run asynchronously");

    app.add_subcommand(std::shared_ptr<CLI::App>(new AgcCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new FmdemodCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new AmdemodCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new DcBlockCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new ReduceNoiseCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new ConvertCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new FftCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new LogPowerCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new LogAveragePowerCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new FftExchangeSidesCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new RealpartCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new ShiftCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new FirDecimateCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new FractionalDecimatorCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new AdpcmCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new FftAdpcmCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new LimitCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new PowerCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new SquelchCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new DeemphasisCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new GainCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new BandPassCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new DBPskDecoderCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new VaricodeDecoderCommand()));
    app.add_subcommand(std::shared_ptr<CLI::App>(new TimingRecoveryCommand()));

    app.add_subcommand(std::shared_ptr<CLI::App>(new BenchmarkCommand()));

    app.require_subcommand(1);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        if (*version_flag) {
            std::cerr << "csdr++ version " << VERSION << "\n";
            return 0;
        }

        return app.exit(e);
    }

    return 0;
}
