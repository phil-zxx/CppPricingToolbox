#pragma once

#include <toolbox/Random/RandomVariableGenerator.hpp>
#include <toolbox/Random/GeneralStatistics.hpp>

#include <future>


namespace Toolbox
{
    template<class Distr, class Engine>
    class MonteCarloEngine
    {
    public:
        MonteCarloEngine(const RandomVariableGenerator<Distr, Engine>& rvg, const size_t& sampleSize, const bool& useAntitheticVariate = false)
            : m_rvg(rvg), m_sampleSize(sampleSize), m_useAntitheticVariate(useAntitheticVariate), m_stats() { }

        template<class Payoff>
        void run(const Payoff& payoff)
        {
            m_stats.reset().reserve(m_sampleSize);

            for (size_t j = 0; j < m_sampleSize; j++)
            {
                const auto& sample = m_rvg.getNext();
                const auto price   = payoff(sample);

                if (m_useAntitheticVariate)
                {
                    const auto& sampleAnti = m_rvg.getAntithetic();
                    const auto priceAnti   = payoff(sampleAnti);
                    m_stats.addSample((price + priceAnti) / 2.0);
                }
                else
                {
                    m_stats.addSample(price);
                }
            }
        }

        const GeneralStatistics& getStats() const
        {
            return m_stats;
        }

    private:
        RandomVariableGenerator<Distr, Engine> m_rvg;
        size_t m_sampleSize;
        bool m_useAntitheticVariate;
        GeneralStatistics m_stats;
    };
}
