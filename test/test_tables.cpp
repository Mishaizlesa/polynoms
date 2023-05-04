#include "gtest/gtest.h"
#include <list>
#include "table.h"
#include "TableT.h"
#include "tree.h"
#include "TreeT.h"
#include "HashTable.h"
#include "hash_table.h"
template <typename T>
class FooTest : public testing::Test {
public:
    using MyTable = T;
};

using MyTypes = ::testing::Types<
    TableT<std::string, int>
    , Table<std::string, int>
    ,TreeT<std::string, int>
    , Tree<std::string, int>
     ,HashTable<int, std::string>
    , my_unordered_map<int, std::string>

>;
TYPED_TEST_SUITE(FooTest, MyTypes);

TYPED_TEST(FooTest, can_insert)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values.insert(std::make_pair("str", 5551)));
}

TYPED_TEST(FooTest, correct_value_after_insert)
{
    typename TestFixture::MyTable values;
    values.insert(std::make_pair("str", 5551));
    EXPECT_EQ(values["str"], 5551);
}

TYPED_TEST(FooTest, can_insert_many_times)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values.insert(std::make_pair("str1", 1)));
    EXPECT_NO_THROW(values.insert(std::make_pair("str2", 2)));
    EXPECT_NO_THROW(values.insert(std::make_pair("str3", 3)));
    EXPECT_NO_THROW(values.insert(std::make_pair("str4", 4)));
    EXPECT_NO_THROW(values.insert(std::make_pair("str5", 5)));
}

TYPED_TEST(FooTest, correct_value_after_many_insert)
{
    typename TestFixture::MyTable values;
    values.insert(std::make_pair("str1", 1));
    values.insert(std::make_pair("str2", 2));
    values.insert(std::make_pair("str3", 3));
    values.insert(std::make_pair("str4", 4));
    values.insert(std::make_pair("str5", 5));

    EXPECT_EQ(values["str1"], 1);
    EXPECT_EQ(values["str2"], 2);
    EXPECT_EQ(values["str3"], 3);
    EXPECT_EQ(values["str4"], 4);
    EXPECT_EQ(values["str5"], 5);
}

TYPED_TEST(FooTest, repeated_insertion_does_not_change_the_element)
{
    typename TestFixture::MyTable values;
    values.insert(std::make_pair("str", 1));
    values.insert(std::make_pair("str", 2));

    EXPECT_EQ(values["str"], 1);

}

TYPED_TEST(FooTest, can_used_square_brackets)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values["de"] = 58);
}

TYPED_TEST(FooTest, square_brackets_from_a_non_existent_key_returns_the_default_value)
{
    typename TestFixture::MyTable values;
    EXPECT_EQ(values["de"], 0);
}

TYPED_TEST(FooTest, can_return_iterator_to_begining)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values.begin());
}

TYPED_TEST(FooTest, can_return_iterator_to_ending)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values.end());
}

TYPED_TEST(FooTest, can_erase)
{
    typename TestFixture::MyTable values;
    values["str"] = 5;
    EXPECT_NO_THROW(values.erase("str"));
}

TYPED_TEST(FooTest, removing_the_missing_element_does_nothing)
{
    typename TestFixture::MyTable values;
    values["str"] = 5;
    values.erase("str5");
    EXPECT_EQ(values["str"], 5);
}


TYPED_TEST(FooTest, after_erase_correct_value)
{
    typename TestFixture::MyTable values;
    values["str"] = 5;
    values.erase("str");
    EXPECT_EQ(values["str"], 0);
}



TYPED_TEST(FooTest, can_erase_many_times)
{
    typename TestFixture::MyTable values;
    values["str1"] = 1;
    values["str2"] = 2;
    values["str3"] = 3;
    values["str4"] = 4;
    values["str5"] = 5;

    values.erase("str5");
    values.erase("str3");
    values.erase("str4");
    bool ok = 1;
    ok &= values["str1"] == 1;
    ok &= values["str2"] == 2;
    ok &= values["str3"] == 0;
    ok &= values["str4"] == 0;
    ok &= values["str5"] == 0;

    EXPECT_TRUE(ok);
}






