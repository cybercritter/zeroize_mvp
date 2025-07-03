#include <gtest/gtest.h>
#include "zeroize_test.h"
#include "zeroize.h"

TEST_F(zeroize_test, ZeroizeFillsWithPattern)
{
    unsigned char buffer[16];
    memset(buffer, 0x00, sizeof(buffer));
    ASSERT_EQ(zeroize(buffer, sizeof(buffer)), 0);
    for (size_t i = 0; i < sizeof(buffer); ++i)
    {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(ZEROIZE_PATTERN));
    }
}

TEST_F(zeroize_test, ZeroizeReturnsNonZeroOnNullPointer)
{
    EXPECT_NE(zeroize(nullptr, 10), 0);
}

TEST_F(zeroize_test, ZeroizeReturnsZeroOnZeroSize)
{
    unsigned char buffer[8];
    EXPECT_EQ(zeroize(buffer, 0), 0);
}

TEST_F(zeroize_test, IsZeroizedReturnsTrueForZeroizedBuffer)
{
    unsigned char buffer[8];
    memset(buffer, ZEROIZE_PATTERN, sizeof(buffer));
    EXPECT_TRUE(is_zeroized(buffer, sizeof(buffer)));
}

TEST_F(zeroize_test, IsZeroizedReturnsFalseForNonZeroizedBuffer)
{
    unsigned char buffer[8];
    memset(buffer, 0x00, sizeof(buffer));
    EXPECT_FALSE(is_zeroized(buffer, sizeof(buffer)));
}

TEST_F(zeroize_test, IsZeroizedReturnsTrueForZeroSize)
{
    unsigned char buffer[4];
    EXPECT_TRUE(is_zeroized(buffer, 0));
}

TEST_F(zeroize_test, IsZeroizedReturnsFalseOnNullPointer)
{
    EXPECT_FALSE(is_zeroized(nullptr, 4));
}
