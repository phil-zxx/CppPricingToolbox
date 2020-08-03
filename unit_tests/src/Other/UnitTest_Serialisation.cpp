#include <doctest/doctest.h>
#include <filesystem>
#include <toolbox/Generic/Serialisation.hpp>

using namespace Toolbox;


TEST_CASE("UnitTest_Serialisation_Base")
{
    ByteArchive ba;

    const auto in1 = 123;
    const auto in2 = 45601234560.789;
    const auto in3 = std::string("this is a test");
    const auto in4 = std::vector<int>{ 5, 2, 6, 99 };
    const auto in5 = std::map<std::string, int>{ {"one",11}, {"two",22}, {"three",33} };
    const auto in6 = std::unordered_map<std::string, int>{ {"four",55}, {"five",55}, {"six",66}, {"seven",77}, {"eight",88} };
    const auto in7 = SampleData(567, "some value", { 5,2,45,39,883,25 });
    const auto in8 = std::array<int, 5>{7,2,4,3,9};
    const auto in9 = std::make_tuple<int, char, double>(2, 'R', 10.5);

    ba.store(in1);
    ba.store(in2);
    ba.store(in3);
    ba.store(in4);
    ba.store(in5);
    ba.store(in6);
    ba.store(in7);
    ba.store(in8);
    ba.store(in9);

    const auto out1 = ba.load<decltype(in1)>();
    const auto out2 = ba.load<decltype(in2)>();
    const auto out3 = ba.load<decltype(in3)>();
    const auto out4 = ba.load<decltype(in4)>();
    const auto out5 = ba.load<decltype(in5)>();
    const auto out6 = ba.load<decltype(in6)>();
    const auto out7 = ba.load<decltype(in7)>();
    const auto out8 = ba.load<decltype(in8)>();
    const auto out9 = ba.load<decltype(in9)>();
    CHECK_THROWS(ba.load<int>());

    CHECK(in1 == out1);
    CHECK(in2 == out2);
    CHECK(in3 == out3);
    CHECK(in4 == out4);
    CHECK(in5 == out5);
    CHECK(in6 == out6);

    CHECK(in7.a == out7.a);
    CHECK(in7.b == out7.b);
    CHECK(in7.c == out7.c);

    CHECK(in8 == out8);
    CHECK(in9 == out9);
}

TEST_CASE("UnitTest_Serialisation_Ptr")
{
    ByteArchive ba;

    const auto in1 = new int();
    const int* in2 = new int(34);
    const int* in3 = nullptr;
    const auto in4 = std::unique_ptr<int>();
    const auto in5 = std::make_unique<const int>(150);
    const auto in6 = std::make_shared<std::string>("test");
    const auto in7 = std::make_unique<const std::vector<std::string>>(3, "some");
    const auto in8 = new const SampleData(33, "test ptr", std::vector<int>{ 55,44,22,11,4,1,90 });
    const auto in9 = std::make_shared<SampleData>(44, "ptr test", std::vector<int>{ 34,7,9 });

    ba.store(in1);
    ba.store(in2);
    ba.store(in3);
    ba.store(in4);
    ba.store(in5);
    ba.store(in6);
    ba.store(in7);
    ba.store(in8);
    ba.store(in9);

    const auto out1 = ba.load<decltype(in1)>();
    const auto out2 = ba.load<decltype(in2)>();
    const auto out3 = ba.load<decltype(in3)>();
    const auto out4 = ba.load<decltype(in4)>();
    const auto out5 = ba.load<decltype(in5)>();
    const auto out6 = ba.load<decltype(in6)>();
    const auto out7 = ba.load<decltype(in7)>();
    const auto out8 = ba.load<decltype(in8)>();
    const auto out9 = ba.load<decltype(in9)>();
    CHECK_THROWS(ba.load<double>());

    CHECK(*in1 == *out1);
    CHECK(*in2 == *out2);
    CHECK( in3 ==  out3);
    CHECK( in4 ==  out4);
    CHECK(*in5 == *out5);
    CHECK(*in6 == *out6);
    CHECK(*in7 == *out7);

    CHECK(in8->a == out8->a);
    CHECK(in8->b == out8->b);
    CHECK(in8->c == out8->c);

    CHECK(in9->a == out9->a);
    CHECK(in9->b == out9->b);
    CHECK(in9->c == out9->c);
}

TEST_CASE("UnitTest_Serialisation_Other")
{
    ByteArchive ba;

    const auto in1 = std::optional<std::string>();
    const auto in2 = std::optional<int>(5);
    const auto in3 = std::variant<int, std::string, double>(24);
    const auto in4 = std::variant<int, std::string, double>(25);
    const auto in5 = std::variant<int, std::string, double>("test string");
    const auto in6 = std::variant<int, std::string, double>(3.148);

    ba.store(in1);
    ba.store(in2);
    ba.store(in3);
    ba.store(in4);
    ba.store(in5);
    ba.store(in6);

    const auto out1 = ba.load<decltype(in1)>();
    const auto out2 = ba.load<decltype(in2)>();
    const auto out3 = ba.load<decltype(in3)>();
    const auto out4 = ba.load<decltype(in4)>();
    const auto out5 = ba.load<decltype(in5)>();
    const auto out6 = ba.load<decltype(in6)>();
    CHECK_THROWS(ba.load<std::string>());

    CHECK(in1 == out1);
    CHECK(in2 == out2);
    CHECK(in3 == out3);
    CHECK(in4 == out4);
    CHECK(in6 == out6);
}

TEST_CASE("UnitTest_Serialisation_ToFromFile")
{
    const std::string fileName = "__temp_file.dat";

    ByteArchive ba;
    const auto in1 = double(2.6);
    const auto in2 = std::string("some text");
    const auto in3 = std::vector<int>{ 9,2,-3,7 };
    ba.store(in1, in2, in3);

    // Check saveToFile & loadFromFile (stored in binary format)
    ba.saveToFile(fileName, true);
    CHECK(ba == ByteArchive::loadFromFile(fileName, true));
    
    // Check saveToFile & loadFromFile (stored as human-readable hex format)
    ba.saveToFile(fileName, false);
    CHECK(ba == ByteArchive::loadFromFile(fileName, false));
    
    // Delete temporary file
    CHECK(std::filesystem::exists(fileName) == true);
    std::filesystem::remove(fileName);
    CHECK(std::filesystem::exists(fileName) == false);
}

TEST_CASE("UnitTest_Serialisation_ToString")
{
    ByteArchive ba;
    const auto in1 = double(2.6);
    const auto in2 = std::string("some text");
    const auto in3 = std::vector<int>{ 9,2,-3,7 };
    ba.store(in1, in2, in3);

    const std::string str1 = ba.toString();
    const std::string str2 = ByteArchive::fromString(str1).toString();
    CHECK(str1 == str2);
}
