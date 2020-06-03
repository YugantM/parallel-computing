#include "utils.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>

#include <getopt.h>

namespace pc {

std::ostream&
operator<< (std::ostream& stream, pc::Vec2 const& v)
{
    stream << "Vec2( "
        << std::setprecision(5) << v.x
        << ", "
        << std::setprecision(5) << v.y
        << " )";

    return stream;
}

/* static */
InputData InputData::generate(Options const& o)
{
    std::mt19937_64 gen(o.numBodies);
    std::uniform_real_distribution<double> dist(0.0, o.planeSize * 1.0);
    InputData d;

    d.bodyPositions.resize(o.numBodies);
    std::generate(std::begin(d.bodyPositions),
        std::end(d.bodyPositions),
        [&] { return Vec2(dist(gen), dist(gen)); });

    d.targetPositions.resize(o.numTargetsPerBody * o.numBodies);
    std::generate(std::begin(d.targetPositions),
        std::end(d.targetPositions),
        [&] { return Vec2(dist(gen), dist(gen)); });

    return d;
}


void usage(char const* programName)
{
    std::cerr << "Usage: " << programName
        << " [-h show this help]"
        << " [-m mode {seq, pt, omp}]"
        << " [-n numBodies]"
        << " [-p number of threads]"
        << " [-r avoidance radius]"
        << " [-s random seed]"
        << " [-t num targets per body]"
        << " [-v Vmax]"
        << " [-w field size]"
        << std::endl;
}

/* static */
Options
Options::parseCommandLine(int argc, char * const argv[])
{
    Options result;

    int opt;
    while ((opt = getopt(argc, argv, "hm:n:r:p:s:t:v:w:")) != -1) {
        switch (opt) {
        case 'h':
            usage(argv[0]);
            exit(EXIT_FAILURE);
        case 'm':
            if (strncmp(optarg, "seq", 3) == 0) {
                result.mode = Mode::Sequential;
            } else if (strncmp(optarg, "pt", 2) == 0) {
                result.mode = Mode::PThreads;
            } else if (strncmp(optarg, "omp", 3) == 0) {
                result.mode = Mode::OpenMP;
            } else {
                usage(argv[0]);
                exit(EXIT_FAILURE);
            }
            break;
        case 'n':
            result.numBodies = std::stoul(optarg);
            break;
        case 'p':
            result.numThreads= std::stoul(optarg);
            break;
        case 'r':
            result.radius = std::stod(optarg);
            break;
        case 's':
            result.seed = std::stoul(optarg);
            break;
        case 't':
            result.numTargetsPerBody = std::stoul(optarg);
            break;
        case 'v':
            result.Vmax = std::stod(optarg);
            break;
        case 'w':
            result.planeSize = std::stoul(optarg);
            break;
        default: /* '?' */
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        std::cerr << "Unknown argument " << argv[optind] << std::endl;
        exit(EXIT_FAILURE);
    }

   return result;
}


} // namespace pc


std::ostream& operator<< (std::ostream& stream, pc::Options const& o)
{
    stream
        << "mode: " << o.mode
        << ", n-bodies: " << o.numBodies
        << ", radius: " << o.radius
        << ", n-threads: " << o.numThreads
        << ", output: " << o.outFileName
        << ", size: " << o.planeSize
        << ", seed: " << o.seed
        << ", n-targets: " << o.numTargetsPerBody
        << ", Vmax: " << o.Vmax
        ;

    return stream;
}
