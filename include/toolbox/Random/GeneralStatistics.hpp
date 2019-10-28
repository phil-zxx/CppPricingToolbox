#pragma once

#include <vector>
#include <array>
#include <numeric>
#include <iostream>


class GeneralStatistics
{
public:
    GeneralStatistics() = default;

    GeneralStatistics& reset()
    {
        m_samples.clear();
        m_convergenceTable.fill({ 0,0 });
        m_checkPoint = 8;
        return *this;
    }

    GeneralStatistics& reserve(size_t sampleSize)
    {
        m_samples.reserve(sampleSize);
        return *this;
    }

    void addSample(double value)
    {
        m_samples.emplace_back(value);

        if (m_samples.size() == m_checkPoint)
        {
            const size_t i = static_cast<size_t>(std::log2(m_samples.size()));
            m_convergenceTable[i] = { mean(), errorEstimate() };
            m_checkPoint *= 2;
        }
    }

    double mean() const
    {
        const size_t N = sampleSize();
        if (N == 0)
            return 0;

        return (1.0 / N) * std::accumulate(m_samples.begin(), m_samples.end(), 0.0);
    }

    double variance() const
    {
        const size_t N = sampleSize();
        if (N <= 1)
            return 0;
        
        const double s2 = std::accumulate(m_samples.begin(), m_samples.end(), 0.0, [mu = mean()](double s, double x) { return s + (x - mu) * (x - mu); });
        return s2 * N / (N - 1.0);
    }

    double standardDeviation() const
    {
        return std::sqrt(variance());
    }

    double errorEstimate() const
    {
        return std::sqrt(variance() / sampleSize());
    }

    size_t sampleSize() const
    {
        return m_samples.size();
    }

    void printConvergenceTable() const
    {
        std::cout << "Convergence Table:\n";
        for (const auto& el : m_convergenceTable)
            std::cout << el.mean << ": " << el.error << "\n";
    }

private:
    std::vector<double> m_samples;

    size_t m_checkPoint;
    struct ConvergencePoint { double mean, error; };
    std::array<ConvergencePoint, 32> m_convergenceTable;
};