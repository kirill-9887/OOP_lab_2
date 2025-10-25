#include <gtest/gtest.h>
#include "../include/eleven.h"

TEST(ElevenClassTest, TestNoParametersConstructor)
{
    EXPECT_EQ(Eleven().getStr(), "0");
}

TEST(ElevenClassTest, TestConstructorWithFiller)
{
    EXPECT_EQ(Eleven(1).getStr(), "0");
    EXPECT_EQ(Eleven(1, 0).getStr(), "0");
    EXPECT_EQ(Eleven(10).getStr(), "0");
    EXPECT_EQ(Eleven(10, 0).getStr(), "0");
    EXPECT_EQ(Eleven(1, 1).getStr(), "1");
    EXPECT_EQ(Eleven(10, 1).getStr(), "1111111111");
    EXPECT_EQ(Eleven(1, 10).getStr(), "a");
    EXPECT_EQ(Eleven(5, 10).getStr(), "aaaaa");

    EXPECT_THROW(Eleven(0), std::invalid_argument);
    EXPECT_THROW(Eleven(0, 1), std::invalid_argument);
    EXPECT_THROW(Eleven(1, 11), std::invalid_argument);
    EXPECT_THROW(Eleven(1, -1), std::invalid_argument);
    EXPECT_THROW(Eleven(10, 100), std::invalid_argument);
}

TEST(ElevenClassTest, TestInitializerListConstructor)
{
    EXPECT_THROW(Eleven({}), std::invalid_argument);

    EXPECT_EQ((Eleven{0}).getStr(), "0");
    EXPECT_EQ((Eleven{0, 0, 0}).getStr(), "0");
    EXPECT_EQ((Eleven{0, 0, 1}).getStr(), "1");
    EXPECT_EQ((Eleven{1}).getStr(), "1");
    EXPECT_EQ((Eleven{5}).getStr(), "5");
    EXPECT_EQ((Eleven{0, 0, 1, 0}).getStr(), "10");
    EXPECT_EQ((Eleven{1, 0}).getStr(), "10");
    EXPECT_EQ((Eleven{10}).getStr(), "a");
    EXPECT_EQ((Eleven{10, 1}).getStr(), "a1");
    EXPECT_EQ((Eleven{10, 10, 10}).getStr(), "aaa");
    EXPECT_EQ((Eleven{1, 2, 3}).getStr(), "123");
    EXPECT_EQ((Eleven{5, 4, 10, 3, 2, 0, 0, 10, 1, 0, 0}).getStr(), "54a3200a100");

    EXPECT_THROW((Eleven{11}), std::invalid_argument);
    EXPECT_THROW((Eleven{1, 11}), std::invalid_argument);
    EXPECT_THROW((Eleven{11, 2}), std::invalid_argument);
    EXPECT_THROW((Eleven{3, 15, 4}), std::invalid_argument);
    EXPECT_THROW((Eleven{0, 100}), std::invalid_argument);
}

TEST(ElevenClassTest, TestConstructorWithString)
{   
    EXPECT_EQ(Eleven("0").getStr(), "0");
    EXPECT_EQ(Eleven("000").getStr(), "0");
    EXPECT_EQ(Eleven("001").getStr(), "1");
    EXPECT_EQ(Eleven("1").getStr(), "1");
    EXPECT_EQ(Eleven("5").getStr(), "5");
    EXPECT_EQ(Eleven("0010").getStr(), "10");
    EXPECT_EQ(Eleven("10").getStr(), "10");
    EXPECT_EQ(Eleven("a").getStr(), "a");
    EXPECT_EQ(Eleven("a1").getStr(), "a1");
    EXPECT_EQ(Eleven("aaa").getStr(), "aaa");
    EXPECT_EQ(Eleven("AAA").getStr(), "aaa");
    EXPECT_EQ(Eleven("123").getStr(), "123");
    EXPECT_EQ(Eleven("54a3200a100").getStr(), "54a3200a100");
    EXPECT_EQ(Eleven("54a3200A100").getStr(), "54a3200a100");

    EXPECT_THROW(Eleven(""), std::invalid_argument);
    EXPECT_THROW(Eleven("b"), std::invalid_argument);
    EXPECT_THROW(Eleven("1b"), std::invalid_argument);
    EXPECT_THROW(Eleven("b2"), std::invalid_argument);
    EXPECT_THROW(Eleven("3f4"), std::invalid_argument);
    EXPECT_THROW(Eleven("0B"), std::invalid_argument);
    EXPECT_THROW(Eleven("P"), std::invalid_argument);
    EXPECT_THROW(Eleven("-1"), std::invalid_argument);
    EXPECT_THROW(Eleven("="), std::invalid_argument);
    EXPECT_THROW(Eleven("+1"), std::invalid_argument);
    EXPECT_THROW(Eleven("."), std::invalid_argument);
}

TEST(ElevenClassTest, TestCopyConstructor)
{
    Eleven number_1("54a3200a100");
    Eleven number_2{number_1};
    EXPECT_EQ(number_1.getStr(), "54a3200a100");
    EXPECT_EQ(number_2.getStr(), "54a3200a100");
}

TEST(ElevenClassTest, TestMoveConstructor)
{
    Eleven number_1("54a3200a100");
    Eleven number_2 = std::move(number_1);

    EXPECT_EQ(number_1.getStr(), "0");
    EXPECT_EQ(number_2.getStr(), "54a3200a100");

    EXPECT_EQ(number_1.add(number_1).getStr(), "0");
    EXPECT_EQ(number_1.add(Eleven("0")).getStr(), "0");
    EXPECT_EQ(number_1.add(Eleven("12345")).getStr(), "12345");

    EXPECT_EQ(number_2.add(number_1).getStr(), "54a3200a100");
    EXPECT_EQ(number_2.add(Eleven("0")).getStr(), "54a3200a100");
    EXPECT_EQ(number_2.add(Eleven("12345")).getStr(), "54a32021445");

    EXPECT_EQ(number_2.substract(number_1).getStr(), "54a3200a100");
    EXPECT_EQ(number_1.substract(Eleven("0")).getStr(), "0");
    EXPECT_EQ(Eleven("0").substract(number_1).getStr(), "0");
    EXPECT_EQ(number_1.substract(number_1).getStr(), "0");

    EXPECT_TRUE(number_1.equal(number_1));
    EXPECT_TRUE(number_1.equal(Eleven("0")));
    EXPECT_TRUE(Eleven("0").equal(number_1));
}

TEST(ElevenClassTest, TestEqual)
{
    EXPECT_TRUE(Eleven("0").equal(Eleven("0")));
    EXPECT_TRUE(Eleven("000").equal(Eleven("0")));
    EXPECT_TRUE(Eleven("0").equal(Eleven("00000")));
    EXPECT_TRUE(Eleven("0").equal(Eleven()));
    EXPECT_TRUE(Eleven("0000000010").equal(Eleven("10")));
    EXPECT_TRUE(Eleven("5453").equal(Eleven("5453")));
    EXPECT_TRUE(Eleven("0aaaa").equal(Eleven("aaaa")));
    EXPECT_TRUE(Eleven("aA").equal(Eleven("Aa")));
    EXPECT_TRUE(Eleven("12345678900987654321aaaa0192837465123456789012345678900987654321aaaa01928374651234567890").equal(
        Eleven("12345678900987654321aaaa0192837465123456789012345678900987654321aaaa01928374651234567890")));

    Eleven number("123a");
    EXPECT_TRUE(number.equal(number));

    EXPECT_FALSE(Eleven("0").equal(Eleven("1")));
    EXPECT_FALSE(Eleven("a").equal(Eleven("0")));
    EXPECT_FALSE(Eleven("A").equal(Eleven("10")));
    EXPECT_FALSE(Eleven("11").equal(Eleven("a")));
    EXPECT_FALSE(Eleven("5453").equal(Eleven("5443")));
    EXPECT_FALSE(Eleven("0aaaa").equal(Eleven("aaaaa")));
    EXPECT_FALSE(Eleven("102938").equal(Eleven("564738")));
    EXPECT_FALSE(Eleven("1111111111").equal(Eleven("2222222222")));
}

TEST(ElevenClassTest, TestNotEqual)
{
    EXPECT_FALSE(Eleven("0").notEqual(Eleven("0")));
    EXPECT_FALSE(Eleven("000").notEqual(Eleven("0")));
    EXPECT_FALSE(Eleven("0").notEqual(Eleven("00000")));
    EXPECT_FALSE(Eleven("0").notEqual(Eleven()));
    EXPECT_FALSE(Eleven("0000000010").notEqual(Eleven("10")));
    EXPECT_FALSE(Eleven("5453").notEqual(Eleven("5453")));
    EXPECT_FALSE(Eleven("0aaaa").notEqual(Eleven("aaaa")));
    EXPECT_FALSE(Eleven("aA").notEqual(Eleven("Aa")));
    EXPECT_FALSE(Eleven("12345678900987654321aaaa0192837465123456789012345678900987654321aaaa01928374651234567890").notEqual(
        Eleven("12345678900987654321aaaa0192837465123456789012345678900987654321aaaa01928374651234567890")));

    Eleven number("123a");
    EXPECT_FALSE(number.notEqual(number));

    EXPECT_TRUE(Eleven("0").notEqual(Eleven("1")));
    EXPECT_TRUE(Eleven("a").notEqual(Eleven("0")));
    EXPECT_TRUE(Eleven("A").notEqual(Eleven("10")));
    EXPECT_TRUE(Eleven("11").notEqual(Eleven("a")));
    EXPECT_TRUE(Eleven("5453").notEqual(Eleven("5443")));
    EXPECT_TRUE(Eleven("0aaaa").notEqual(Eleven("aaaaa")));
    EXPECT_TRUE(Eleven("102938").notEqual(Eleven("564738")));
    EXPECT_TRUE(Eleven("1111111111").notEqual(Eleven("2222222222")));
}

TEST(ElevenClassTest, TestGreater)
{
    EXPECT_TRUE(Eleven("1").greater(Eleven("0")));
    EXPECT_TRUE(Eleven("2").greater(Eleven("1")));
    EXPECT_TRUE(Eleven("80").greater(Eleven("7a")));
    EXPECT_TRUE(Eleven("33333").greater(Eleven("3333")));
    EXPECT_TRUE(Eleven("10").greater(Eleven("a")));
    EXPECT_TRUE(Eleven("aa").greater(Eleven("a9")));

    Eleven number("123a");
    EXPECT_FALSE(number.greater(number));

    EXPECT_FALSE(Eleven("0").greater(Eleven("0")));
    EXPECT_FALSE(Eleven("0").greater(Eleven("1")));
    EXPECT_FALSE(Eleven("4").greater(Eleven("9")));
    EXPECT_FALSE(Eleven("80").greater(Eleven("81")));
    EXPECT_FALSE(Eleven("3333").greater(Eleven("33333")));
    EXPECT_FALSE(Eleven("3333").greater(Eleven("3333")));
    EXPECT_FALSE(Eleven("a").greater(Eleven("10")));
    EXPECT_FALSE(Eleven("12345678900987654321aaaa0192837465123456789012345678900987654321aaaa01928374651234567890").greater(
        Eleven("12345678900987654321aaaa0192837465123456789012345678900987654321aaaa01928374651234567890")));
}

TEST(ElevenClassTest, TestLess)
{
    EXPECT_TRUE(Eleven("0").less(Eleven("1")));
    EXPECT_TRUE(Eleven("1").less(Eleven("3")));
    EXPECT_TRUE(Eleven("7a").less(Eleven("80")));
    EXPECT_TRUE(Eleven("3333").less(Eleven("33333")));
    EXPECT_TRUE(Eleven("a").less(Eleven("10")));
    EXPECT_TRUE(Eleven("a9").less(Eleven("aa")));

    Eleven number("123a");
    EXPECT_FALSE(number.less(number));

    EXPECT_FALSE(Eleven("0").less(Eleven("0")));
    EXPECT_FALSE(Eleven("22").less(Eleven("0")));
    EXPECT_FALSE(Eleven("9").less(Eleven("8")));
    EXPECT_FALSE(Eleven("80").less(Eleven("79")));
    EXPECT_FALSE(Eleven("33333").less(Eleven("3333")));
    EXPECT_FALSE(Eleven("3333").less(Eleven("3333")));
    EXPECT_FALSE(Eleven("10").less(Eleven("a")));
    EXPECT_FALSE(Eleven("12345678900987654321aaaa0192837465123456789012345678900987654321aaaa01928374651234567890").greater(
        Eleven("12345678900987654321aaaa0192837465123456789012345678900987654321aaaa01928374651234567890")));
}


TEST(ElevenClassTest, TestAdd)
{
    Eleven number("1");
    EXPECT_EQ(number.add(number).getStr(), "2");

    EXPECT_EQ(Eleven("0").add(Eleven("0")).getStr(), "0");
    EXPECT_EQ(Eleven("000").add(Eleven("000")).getStr(), "0");
    EXPECT_EQ(Eleven("0").add(Eleven("000")).getStr(), "0");
    EXPECT_EQ(Eleven("000").add(Eleven("0")).getStr(), "0");
    EXPECT_EQ(Eleven("2").add(Eleven("3")).getStr(), "5");
    EXPECT_EQ(Eleven("a").add(Eleven("1")).getStr(), "10");
    EXPECT_EQ(Eleven("aa").add(Eleven("1")).getStr(), "100");
    EXPECT_EQ(Eleven("aa").add(Eleven("2")).getStr(), "101");
    EXPECT_EQ(Eleven("aa").add(Eleven("0002")).getStr(), "101");
    EXPECT_EQ(Eleven("aaaa").add(Eleven("aa")).getStr(), "100a9");
    EXPECT_EQ(Eleven("1001002").add(Eleven("1230000")).getStr(), "2231002");
}

TEST(ElevenClassTest, TestSubstract)
{
    Eleven number("98123000aa213");
    EXPECT_EQ(number.substract(number).getStr(), "0");

    EXPECT_EQ(Eleven("0").substract(Eleven("0")).getStr(), "0");
    EXPECT_EQ(Eleven("000").substract(Eleven("000")).getStr(), "0");
    EXPECT_EQ(Eleven("0").substract(Eleven("000")).getStr(), "0");
    EXPECT_EQ(Eleven("000").substract(Eleven("0")).getStr(), "0");
    EXPECT_EQ(Eleven("1").substract(Eleven("1")).getStr(), "0");
    EXPECT_EQ(Eleven("5").substract(Eleven("0")).getStr(), "5");
    EXPECT_EQ(Eleven("10").substract(Eleven("1")).getStr(), "a");

    EXPECT_EQ(Eleven("123").substract(Eleven("111")).getStr(), "12");
    EXPECT_EQ(Eleven("a5").substract(Eleven("23")).getStr(), "82");
    EXPECT_EQ(Eleven("7a").substract(Eleven("1a")).getStr(), "60");
    EXPECT_EQ(Eleven("1a0").substract(Eleven("90")).getStr(), "110");
    EXPECT_EQ(Eleven("130").substract(Eleven("51")).getStr(), "8a");
    EXPECT_EQ(Eleven("100").substract(Eleven("1")).getStr(), "aa");
    EXPECT_EQ(Eleven("205").substract(Eleven("a7")).getStr(), "109");
    EXPECT_EQ(Eleven("a0").substract(Eleven("15")).getStr(), "86");
    EXPECT_EQ(Eleven("a").substract(Eleven("5")).getStr(), "5");
    EXPECT_EQ(Eleven("1a").substract(Eleven("a")).getStr(), "10");
    EXPECT_EQ(Eleven("a5").substract(Eleven("56")).getStr(), "4a");

    EXPECT_THROW(Eleven("0").substract(Eleven("56")), std::underflow_error);
    EXPECT_THROW(Eleven("5").substract(Eleven("10")), std::underflow_error);
    EXPECT_THROW(Eleven("1a").substract(Eleven("2a")), std::underflow_error);
}

TEST(ElevenClassTest, TestCopy)
{
    Eleven number("98123000aa213");
    EXPECT_EQ(number.copy().getStr(), "98123000aa213");
    EXPECT_EQ(number.getStr(), "98123000aa213");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}