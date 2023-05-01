#include "solve_expr.h"
#include <gtest/gtest.h>
#include <iostream>

template <typename T>
class translate : public testing::Test {
public:
    using MyTable = T;
protected:

    MyTable t1;
    stdvector<polynome>a;

    polynome A, B, C, D;

    translate()
    {
        srand(40);
        const int K = 5;
        for (int i = 0; i < 5; ++i)
        {
            A.insert(monome(rand(), rand(), rand(), rand()));
            A.insert(monome(rand(), rand(), rand(), rand()));

            B.insert(monome(rand(), rand(), rand(), rand()));
            B.insert(monome(rand(), rand(), rand(), rand()));

            C.insert(monome(rand(), rand(), rand(), rand()));
            C.insert(monome(rand(), rand(), rand(), rand()));
            C.insert(monome(rand(), rand(), rand(), rand()));

            D.insert(monome(rand(), rand(), rand(), rand()));
        }

        t1["A"] = A;
        t1["B"] = B;
        t1["C"] = C;
        t1["D"] = D;
    }
    
};

using MyTypes = ::testing::Types<
    TableT<std::string, polynome>
    , Table<std::string, polynome>
    , TreeT<std::string, polynome>
    , Tree<std::string, polynome>
    ,HashTable<polynome, std::string>
    , my_unordered_map<polynome, std::string>

>;
TYPED_TEST_SUITE(translate, MyTypes);


TYPED_TEST(translate, can_solve)
{
    EXPECT_NO_THROW(solve<MyTable>("A + B + C * A", t1,  a));
}

TYPED_TEST(translate, correct_add)
{
    auto res = solve<MyTable>("A + B", t1, a);
    EXPECT_TRUE(res.first == A + B);
}

TYPED_TEST(translate, correct_sub)
{
    auto res = solve<MyTable>("A - B", t1, a);
    auto sub = A - B;
    EXPECT_TRUE(res.first == sub);

}

TYPED_TEST(translate, correct_mul)
{
    auto res = solve<MyTable>("A * B",t1, a);
    auto mul = A * B;
    EXPECT_TRUE(res.first == mul);
    
}



TYPED_TEST(translate, correct_div)
{
    auto res = solve<MyTable>("A / B", t1, a);
    polynome div = A / B;
    EXPECT_TRUE(res.first == div);
    
}


TYPED_TEST(translate, correct_priority_of_oper1)
{
    auto res = solve<MyTable>("A + B * C", t1, a);
    auto ans = B * C;
    ans = A + ans;
    EXPECT_TRUE(res.first == ans);

}

TYPED_TEST(translate, correct_priority_of_oper2)
{
    auto res = solve<MyTable>("( A + B ) * C", t1, a);
    auto ans = A + B;
    ans = ans * C;
    EXPECT_TRUE(res.first == ans);

}


TYPED_TEST(translate, cant_solve_expr_with_invalid_lexems)
{
    auto res = solve<MyTable>("A < 3", t1, a);
    EXPECT_EQ(res.second, 0);
}
