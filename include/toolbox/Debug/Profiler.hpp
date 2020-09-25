#pragma once

#include <iostream>
#include <sstream>
#include <array>
#include <chrono>
#include <iomanip>
#include <cmath>


namespace Toolbox
{
    class Profiler
    {
    public:
        Profiler();

        void reset();
        void lapStart();
        void lap();
        void printStats(const bool& withDistribution = false);

        static void sleepForSeconds(const double& seconds);
        static void sleepForNanoSeconds(const uint64_t& nanos);

        uint64_t getTotalTime() const;

        std::string toString(const bool& withDistribution = false) const;

    private:
        uint64_t m_minTime, m_maxTime, m_lastTime, m_timeTotal, m_trialsTotal;

        struct BucketData { uint64_t trials, time; };
        std::array<BucketData, 64> m_buckets;

        static uint64_t getNanos();

        static std::string nanosToPrettyString(const uint64_t& nanos);
    };

    // Inline Definitions

    inline Profiler::Profiler()
        : m_minTime(static_cast<uint64_t>(-1)), m_maxTime(0), m_timeTotal(0), m_trialsTotal(0)
    {
        m_buckets.fill({ 0,0 });
        m_lastTime = getNanos();
    }

    inline void Profiler::reset()
    {
        *this = Profiler();
    }

    inline void Profiler::lapStart()
    {
        m_lastTime = getNanos();
    }

    inline void Profiler::lap()
    {
        const uint64_t finishTime = getNanos();
        const uint64_t diffTime   = finishTime - m_lastTime;

        m_lastTime = finishTime;
        m_maxTime  = (m_maxTime > diffTime ? m_maxTime : diffTime);
        m_minTime  = (m_minTime < diffTime ? m_minTime : diffTime);

        const size_t bucketIdx = static_cast<size_t>(std::log2(diffTime));
        m_buckets[bucketIdx].time += diffTime;
        ++m_buckets[bucketIdx].trials;

        m_timeTotal += diffTime;
        ++m_trialsTotal;
    }

    inline void Profiler::printStats(const bool& withDistribution)
    {
        if (m_trialsTotal == 0)
            this->lap();

        std::cout << this->toString(withDistribution) << std::endl;
    }

    inline void Profiler::sleepForSeconds(const double& seconds)
    {
        sleepForNanoSeconds(static_cast<uint64_t>(seconds * 1'000'000'000));
    }

    inline void Profiler::sleepForNanoSeconds(const uint64_t& nanos)
    {
        const uint64_t endTime = getNanos() + nanos;
        while(getNanos() < endTime) { }
    }

    inline uint64_t Profiler::getTotalTime() const
    {
        return m_timeTotal;
    }

    inline std::string Profiler::toString(const bool& withDistribution) const
    {
        std::ostringstream os;

        size_t bottom = 0, top = 63;

        for (bottom = 0; bottom < m_buckets.size(); ++bottom)
            if (m_buckets[bottom].trials > 0)
                break;

        for (size_t i = bottom; i < m_buckets.size(); ++i)
            if (m_buckets[i].trials > 0)
                top = i;


        os << "Profiling Results:\n" <<
            "\tMin        = " << nanosToPrettyString(m_minTime) << std::endl <<
            "\tMean       = " << nanosToPrettyString(m_timeTotal / (1 > m_trialsTotal ? 1 : m_trialsTotal)) << std::endl <<
            "\tMax        = " << nanosToPrettyString(m_maxTime) << std::endl <<
            "\tTotal Time = " << nanosToPrettyString(m_timeTotal) << std::endl;

        if (withDistribution)
        {
            os << std::endl << "\t" << std::setw(14) << "Range |" << std::setw(11) << "Count |" << std::setw(11) << "Count %" <<
                  std::endl << "\t" << "-------------+----------+-----------" << std::endl;

            uint64_t x = uint64_t(1) << bottom;
            for (size_t i = bottom; i <= top; ++i)
            {
                uint64_t divisor = (x < 1000 ? 1 : (x < 1'000'000 ? 1000 : (x < 1'000'000'000 ? 1'000'000 : 1'000'000'000)));
                const char* unit = (x < 1000 ? "ns" : (x < 1'000'000 ? "us" : (x < 1'000'000'000 ? "ms" : " s")));

                os << "\t" << std::setw(4) << x / divisor << "-" << std::setw(4) << 2 * x / divisor << " " << unit << " | " <<
                    std::setw(8) << m_buckets[i].trials << " | " <<
                    std::setw(7) << std::fixed << std::setprecision(1) << m_buckets[i].trials * 100. / m_trialsTotal << "%\n";

                x = x * 2;
            }
        }

        return os.str();
    }

    inline uint64_t Profiler::getNanos()
    {
        return static_cast<uint64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    inline std::string Profiler::nanosToPrettyString(const uint64_t& nanos)
    {
        std::ostringstream os;

        const uint64_t sec  = (nanos                ) / 1'000'000'000;
        const uint64_t msec = (nanos % 1'000'000'000) /     1'000'000;
        const uint64_t usec = (nanos %     1'000'000) /         1'000;
        const uint64_t nsec = (nanos %         1'000);
        os << std::setw(10) << nanos << " ns (= " <<
            std::setw(3) << sec << " sec, " <<
            std::setw(3) << msec << " ms, " <<
            std::setw(3) << usec << " us, " <<
            std::setw(3) << nsec << " ns)";

        return os.str();
    }
}
