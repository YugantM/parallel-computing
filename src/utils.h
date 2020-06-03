#ifndef PC_UTILS_H
#define PC_UTILS_H

#include <cmath>
#include <ostream>
#include <string>
#include <valarray>

namespace pc
{

struct Vec2 {
    double x;
    double y;

    Vec2() : x(0.0), y(0.0) {}
    explicit Vec2(double val) : x(val), y(val) {}
    Vec2(double xVal, double yVal) : x(xVal), y(yVal) {}
};

std::ostream& operator<< (std::ostream& stream, pc::Vec2 const& v);

enum Mode {
    Sequential,
    PThreads,
    OpenMP
};

struct Options {
    std::uint64_t seed = 1234;
    std::size_t planeSize = 10000;
    std::size_t numBodies = 5000;
    std::size_t numTargetsPerBody = 10;
    Mode mode = Mode::Sequential;
    double radius = 10;
    double Vmax = 5.0;
    std::string outFileName = "ouptut_seq_1.csv";
    std::size_t numThreads = 1;

    static Options parseCommandLine(int argc, char * const argv[]);
};

struct InputData {
    std::valarray< Vec2 > bodyPositions;
    std::valarray< Vec2 > targetPositions;

    static InputData generate(Options const& o);

private:
    InputData() {}
};

} // namespace pc

std::ostream& operator<< (std::ostream& stream, pc::Options const& o);

#endif // PC_UTILS_H
