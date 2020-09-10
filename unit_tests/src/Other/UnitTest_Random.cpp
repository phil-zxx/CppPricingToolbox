#include <doctest/doctest.h>
#include <toolbox/Core/ApproxValue.hpp>
#include <toolbox/Random/RandomVariableGenerator.hpp>
#include <toolbox/Random/MonteCarloEngine.hpp>


using namespace Toolbox;


TEST_CASE("UnitTest_Random_RV_Generator")
{
    constexpr unsigned int seed = 10;

    RandomVariableGenerator rvg1(std::uniform_int_distribution<>(0, 5), seed);
    #ifdef _MSC_VER
    CHECK(rvg1.getNext()       == 5);
    CHECK(rvg1.getAntithetic() == 0);
    CHECK(rvg1.getNext()       == 3);
    CHECK(rvg1.getAntithetic() == 2);
    #else
    CHECK(rvg1.getNext()       == 4);
    CHECK(rvg1.getAntithetic() == 1);
    CHECK(rvg1.getNext()       == 1);
    CHECK(rvg1.getAntithetic() == 4);
    #endif

    RandomVariableGenerator rvg2(std::uniform_real_distribution<>(0, 5), seed);
    CHECK(ApproxValue(rvg2.getNext())       == 1.4938057933134499);
    CHECK(ApproxValue(rvg2.getAntithetic()) == 3.5061942066865504);
    CHECK(ApproxValue(rvg2.getNext())       == 2.4729496415480412);
    CHECK(ApproxValue(rvg2.getAntithetic()) == 2.5270503584519588);

    RandomVariableGenerator rvg3(std::exponential_distribution<>(0.2), seed);
    CHECK(ApproxValue(rvg3.getNext())       == 1.7745336740165090);
    CHECK(ApproxValue(rvg3.getAntithetic()) == 6.0405541263088525);
    CHECK(ApproxValue(rvg3.getNext())       == 3.4119257803495748);
    CHECK(ApproxValue(rvg3.getAntithetic()) == 3.5201314370331396);
}

TEST_CASE("UnitTest_Random_MonteCarloEngine1")
{
    constexpr unsigned int seed = 10;

    RandomVariableGenerator rvg(std::exponential_distribution<>(0.012), seed);
    MonteCarloEngine mce(rvg, 10'000);
    CHECK(mce.getStats().mean()     == 0);
    CHECK(mce.getStats().variance() == 0);

    constexpr auto payoff = [T = 5](const double& tau) { return tau < T ? 0.6 - tau * 0.01 : -T * 0.01; };
    mce.run(payoff);
    auto npv = mce.getStats().mean() * 10'000'000;
    CHECK(ApproxValue(npv) == -150136.53532115807);
}

TEST_CASE("UnitTest_Random_MonteCarloEngine2")
{
    constexpr unsigned int seed = 10;

    RandomVariableGenerator rvg(std::exponential_distribution<>(0.012), seed);
    MonteCarloEngine mce(rvg, 10'000, true);
    CHECK(mce.getStats().mean()     == 0);
    CHECK(mce.getStats().variance() == 0);

    constexpr auto payoff = [T = 5](const double& tau) { return tau < T ? 0.6 - tau * 0.01 : -T * 0.01; };
    mce.run(payoff);
    auto npv = mce.getStats().mean() * 10'000'000;
    CHECK(ApproxValue(npv) == -151704.00568797035);
}
