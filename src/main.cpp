#include "utils.h"

#include <algorithm>
#include <iterator>
#include <iostream>

void demo(pc::InputData const& data) {
    std::cout << "= positions =" << std::endl;
    std::copy(std::begin(data.bodyPositions),
        std::end(data.bodyPositions) ,
        std::ostream_iterator< pc::Vec2 >(std::cout, "\n")
    );

    std::cout << "= targets =" << std::endl;
    std::copy(std::begin(data.targetPositions),
        std::end(data.targetPositions),
        std::ostream_iterator< pc::Vec2 >(std::cout, "\n")
    );
}

int main(int argc, char* argv[])
{
    pc::Options opts = pc::Options::parseCommandLine(argc, argv);
    std::cout << opts << std::endl;

    // Use this code to get initial values
    // You do not have to use the provided data structure Vec2, but use the
    // generated values!
    pc::InputData data = pc::InputData::generate(opts);

    demo(data);
    return 0;
}
