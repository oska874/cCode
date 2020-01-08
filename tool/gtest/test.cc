#include <gtest/gtest.h>
#include <numeric>
#include <vector>


class VectorTest : public testing::Test
{
protected:
    virtual void SetUp() override
    {
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
    }
    std::vector<int> vec;
};

// 注意这里使用 TEST_F，而不是 TEST
TEST_F(VectorTest, PushBack)
{
    // 虽然这里修改了 vec，但对其它测试函数来说是不可见的
    vec.push_back(4);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.back(), 4);
}

TEST_F(VectorTest, Size)
{
    EXPECT_EQ(vec.size(), 3);
}

TEST(MyTest, Sum)
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    EXPECT_EQ(sum, 15);
}

TEST(MyTest, Add)
{
    EXPECT_EQ(1+1, 3);
    ASSERT_EQ(1+1, 2);
    EXPECT_EQ(1+1, 2);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}