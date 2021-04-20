/**
 * @file    align.cpp
 * @ingroup src
 * @author  Chirag Jain <cjain7@gatech.edu>
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <chrono>
#include <functional>
#include <cstdio>

#include "map/include/map_parameters.hpp"
#include "map/include/base_types.hpp"
#include "map/include/winSketch.hpp"
#include "map/include/computeMap.hpp"
#include "map/include/parseCmdArgs.hpp"

#include "align/include/align_parameters.hpp"
#include "align/include/computeAlignments.hpp"
#include "align/include/parseCmdArgs.hpp"

#include "yeet/include/parse_args.hpp"

//External includes
#include "common/args.hxx"
#include "common/ALeS.hpp"

int main(int argc, char** argv) {
    /*
     * Make sure env variable MALLOC_ARENA_MAX is unset 
     * for efficient multi-thread execution
     */
    unsetenv((char *)"MALLOC_ARENA_MAX");

    // get our parameters from the command line
    skch::Parameters map_parameters;
    align::Parameters align_parameters;
    yeet::Parameters yeet_parameters;
    yeet::parse_args(argc, argv, map_parameters, align_parameters, yeet_parameters);

    //parameters.refSequences.push_back(ref);
    auto t0 = skch::Time::now();

    //skch::parseandSave(argc, argv, cmd, parameters);
    if (!yeet_parameters.remapping) {
        skch::printCmdOptions(map_parameters);

        std::cerr << "INFO, ALeS, Generating spaced seeds" << std::endl;
        uint32_t seed_weight = 10;
        uint32_t seed_count = 5;
        uint32_t region_length = 20;
        float similarity = 0.75;
        std::vector<ales::spaced_seed> spaced_seeds = ales::generate_spaced_seeds(seed_weight, seed_count, similarity, region_length);
        std::chrono::duration<double> time_spaced_seeds = skch::Time::now() - t0;
        std::cerr << "INFO, ALeS, Time spent generating spaced seeds " << time_spaced_seeds.count()  << " seconds" << std::endl;


        //Build the sketch for reference
        //skch::Sketch referSketch(map_parameters);
        skch::Sketch referSketch(map_parameters, spaced_seeds);

        std::chrono::duration<double> timeRefSketch = skch::Time::now() - t0;
        std::cerr << "[mashz::map] time spent computing the reference index: " << timeRefSketch.count() << " sec" << std::endl;

        //Map the sequences in query file
        t0 = skch::Time::now();

        //skch::Map mapper = skch::Map(map_parameters, referSketch);
        skch::Map mapper = skch::Map(map_parameters, referSketch, spaced_seeds);

        std::chrono::duration<double> timeMapQuery = skch::Time::now() - t0;
        std::cerr << "[mashz::map] time spent mapping the query: " << timeMapQuery.count() << " sec" << std::endl;
        std::cerr << "[mashz::map] mapping results saved in: " << map_parameters.outFileName << std::endl;

        if (yeet_parameters.approx_mapping) {
            return 0;
        }
    }

    align::printCmdOptions(align_parameters);

    t0 = skch::Time::now();

    align::Aligner alignObj(align_parameters);

    std::chrono::duration<double> timeRefRead = skch::Time::now() - t0;
    std::cerr << "[mashz::align] time spent read the reference sequences: " << timeRefRead.count() << " sec" << std::endl;

    //Compute the alignments
    alignObj.compute();

    std::chrono::duration<double> timeAlign = skch::Time::now() - t0;
    std::cerr << "[mashz::align] time spent computing the alignment: " << timeAlign.count() << " sec" << std::endl;

    std::cerr << "[mashz::align] alignment results saved in: " << align_parameters.pafOutputFile << std::endl;

}
