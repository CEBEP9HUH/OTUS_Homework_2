#include "gtest/gtest.h"
#include "ip_filter_lib.h"

TEST(FILTER, FILTER_1_OCTET)
{
    std::vector<std::vector<std::string> > input{{"46", "182", "19", "219"}, 
                                                {"46", "251", "197", "23"}, 
                                                {"127", "0", "0", "1"}, 
                                                {"46", "251", "197", "2"}};
    std::vector<std::vector<std::string> > result{{"46", "182", "19", "219"}, 
                                                {"46", "251", "197", "23"},
                                                {"46", "251", "197", "2"}};
    ASSERT_EQ(filter(input, 46), result);
    ASSERT_EQ(filter(input, 4), std::vector<std::vector<std::string> >());
}

TEST(FILTER, FILTER_2_OCTET)
{
    std::vector<std::vector<std::string> > input{{"46", "182", "19", "219"}, 
                                                {"46", "251", "197", "23"}, 
                                                {"127", "0", "0", "1"}, 
                                                {"46", "251", "197", "2"}};
    std::vector<std::vector<std::string> > result{{"46", "251", "197", "23"},
                                                {"46", "251", "197", "2"}};
    ASSERT_EQ(filter(input, 46, 251), result);
    ASSERT_EQ(filter(input, 4, 251), std::vector<std::vector<std::string> >());
}

TEST(FILTER, FILTER_ANY)
{
    std::vector<std::vector<std::string> > input{{"46", "182", "19", "219"}, 
                                                {"46", "251", "197", "23"}, 
                                                {"127", "0", "0", "1"}, 
                                                {"46", "251", "197", "2"}};
    std::vector<std::vector<std::string> > result{{"46", "251", "197", "23"},
                                                {"46", "251", "197", "2"}};
    ASSERT_EQ(filter_any(input, 251), result);
    ASSERT_EQ(filter_any(input, 21), std::vector<std::vector<std::string> >());

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}