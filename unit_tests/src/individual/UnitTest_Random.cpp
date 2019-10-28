#include <catch.hpp>

#include <toolbox/Random/RandomVariableGenerator.hpp>
#include <toolbox/Random/MonteCarloEngine.hpp>
#include <iostream>


using namespace Toolbox;


TEST_CASE("UnitTest_Random", "[UnitTest_Random]")
{
    constexpr unsigned int seed = 10;

    RandomVariableGenerator rvg1(std::uniform_int_distribution<>(0, 5), seed);
    CHECK(rvg1.getNext() == 5);
    CHECK(rvg1.getAntithetic() == 0);
    CHECK(rvg1.getNext() == 3);
    CHECK(rvg1.getAntithetic() == 2);

    RandomVariableGenerator rvg2(std::uniform_real_distribution<>(0, 5), seed);
    CHECK(Approx(rvg2.getNext()) == 1.4938057933);
    CHECK(Approx(rvg2.getAntithetic()) == 3.5061942067);
    CHECK(Approx(rvg2.getNext()) == 2.4729496415);
    CHECK(Approx(rvg2.getAntithetic()) == 2.5270503585);

    RandomVariableGenerator rvg3(std::exponential_distribution<>(0.2), seed);
    CHECK(Approx(rvg3.getNext()) == 1.774533674);
    CHECK(Approx(rvg3.getAntithetic()) == 6.040554126);
    CHECK(Approx(rvg3.getNext()) == 3.4119257803);
    CHECK(Approx(rvg3.getAntithetic()) == 3.520131437);

    RandomVariableGenerator rvg4(std::exponential_distribution<>(0.012), seed);
    MonteCarloEngine mce(rvg4, 10'000);

    constexpr auto payoff = [T = 5](const double& tau) { return tau < T ? 0.6 - tau * 0.01 : -T * 0.01; };
    mce.run(payoff);
    auto npv = mce.getStats().mean() * 10'000'000;
    CHECK(Approx(npv) == -150136.53);
}
