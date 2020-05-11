#include "gtest/gtest.h"
#include "../libs/ip_filter_lib.h"

TEST(CONVERT, CONVERT_IP)
{
    std::vector<std::string> input {"1", "46", "22", "15"};
    std::vector<unsigned char> result {1, 46, 22, 15};
    ASSERT_EQ(convert_to_uchars(input), result);
    std::vector<std::string> input2 {"Best", "ip", "addres", "ever"};
    ASSERT_THROW(convert_to_uchars(input2), std::invalid_argument);
    std::vector<std::string> input3 {"1", "2", "3"};
    ASSERT_THROW(convert_to_uchars(input3), std::invalid_argument);
    std::vector<std::string> input4 {"1", "2", "3q", "4q"};
    ASSERT_THROW(convert_to_uchars(input4), std::invalid_argument);
    std::vector<std::string> input5 {"1", "2", "3", "256"};
    ASSERT_THROW(convert_to_uchars(input5), std::invalid_argument);
    std::vector<std::string> input6 {"1", "2", "3", "-1"};
    ASSERT_THROW(convert_to_uchars(input6), std::invalid_argument);
    std::vector<std::string> input7 {"1", "2", "3.2", "-1"};
    ASSERT_THROW(convert_to_uchars(input7), std::invalid_argument);
}

TEST(FILTER, FILTER_1_OCTET)
{
    std::vector<std::vector<unsigned char> > input{{46, 182, 19, 219}, 
                                                {46, 251, 197, 23}, 
                                                {127, 0, 0, 1}, 
                                                {46, 251, 197, 2}};
    std::vector<std::vector<unsigned char> > result{{46, 182, 19, 219}, 
                                                {46, 251, 197, 23},
                                                {46, 251, 197, 2}};
    ASSERT_EQ(filter(input, 46), result);
    ASSERT_EQ(filter(input, 4), std::vector<std::vector<unsigned char> >());
    ASSERT_EQ(filter(std::vector<std::vector<unsigned char> >(), 46), std::vector<std::vector<unsigned char> >());
}

TEST(FILTER, FILTER_2_OCTET)
{
    std::vector<std::vector<unsigned char> > input{{46, 182, 19, 219}, 
                                                {46, 251, 197, 23}, 
                                                {127, 0, 0, 1}, 
                                                {46, 251, 197, 2}};
    std::vector<std::vector<unsigned char> > result{{46, 251, 197, 23},
                                                {46, 251, 197, 2}};
    ASSERT_EQ(filter(input, 46, 251), result);
    ASSERT_EQ(filter(input, 4, 251), std::vector<std::vector<unsigned char> >());
    ASSERT_EQ(filter(std::vector<std::vector<unsigned char> >(), 4, 251), std::vector<std::vector<unsigned char> >());
}

TEST(FILTER, FILTER_ANY)
{
    std::vector<std::vector<unsigned char> > input{{46, 182, 19, 219}, 
                                                {46, 251, 197, 23}, 
                                                {127, 0, 0, 1}, 
                                                {46, 251, 197, 2}};
    std::vector<std::vector<unsigned char> > result{{46, 251, 197, 23},
                                                {46, 251, 197, 2}};
    ASSERT_EQ(filter_any(input, 251), result);
    ASSERT_EQ(filter_any(input, 21), std::vector<std::vector<unsigned char> >());
    ASSERT_EQ(filter_any(std::vector<std::vector<unsigned char> >(), 251), std::vector<std::vector<unsigned char> >());

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}