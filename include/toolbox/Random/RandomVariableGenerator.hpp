#pragma once

#include <toolbox/Core/Typetraits.hpp>

#include <random>
#include <iostream>


namespace Toolbox
{
    template<class Distr, class Engine = std::mt19937>
    class RandomVariableGenerator
    {
    public:
        using ReturnType   = decltype(std::declval<Distr>()(std::declval<Engine&>()));
        using Distribution = Distr;

        RandomVariableGenerator()
            : m_last(), m_distr() { }

        explicit RandomVariableGenerator(const Distr& distr)
            : m_last(), m_distr(distr) { }

        explicit RandomVariableGenerator(size_t seed)
            : m_last(), m_distr(), m_engine(seed) { }

        RandomVariableGenerator(const Distr& distr, unsigned int seed)
            : m_last(), m_distr(distr), m_engine(seed) { }

        void setSeed(unsigned int seed)
        {
            m_engine.seed(seed);
        }

        const ReturnType& getNext()
        {
            m_last = m_distr(m_engine);
            return m_last;
        }

        const ReturnType& getLast() const
        {
            return m_last;
        }

        const ReturnType& getAntithetic()
        {
            if constexpr (std::is_same_v<Distr, std::uniform_int_distribution<>> || std::is_same_v<Distr, std::uniform_real_distribution<>>)
                m_last = (m_distr.a() + m_distr.b()) - m_last;
            else if constexpr (std::is_same_v<Distr, std::normal_distribution<>>)
                m_last = 2 * m_distr.mean() - m_last;
            else if constexpr (std::is_same_v<Distr, std::exponential_distribution<>>)
                m_last = -std::log(1 - std::exp(-m_distr.lambda() * m_last)) / m_distr.lambda();
            else
                static_assert(false_template<Distr>::value, "Given distribution is not supported in antithetic calculation");

            return m_last;
        }

        void printSamples(const size_t& count = 5)
        {
            for (size_t i = 0; i < count; ++i)
                std::cout << getNext() << "  ";
            std::cout << std::endl;
        }

    private:
        ReturnType m_last;
        Distr m_distr;
        Engine m_engine = Engine(std::random_device{}());
    };
}
