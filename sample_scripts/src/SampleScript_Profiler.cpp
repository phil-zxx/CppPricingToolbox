#include <toolbox/Debug/Profiler.hpp>

using namespace TB;


int main()
{
    Profiler p;

    for (int i = 0; i < 1000; ++i)
    {
        Profiler::sleepForSeconds(0.001);
        p.lap();
    }

    p.printStats(true);

    return 0;
}
