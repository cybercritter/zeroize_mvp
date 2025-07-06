#include <gtest/gtest.h>
#include "zeroize_test.h"
#include "zeroize.h"
#include <algorithm>
#include <iterator>

TEST_F(zeroize_test, ZeroizeFillsWithPattern)
{
    unsigned char buffer[16];
    memset(buffer, 0xFE, sizeof(buffer));
    ASSERT_EQ(zeroize(buffer, sizeof(buffer)), 0);

    for(size_t i = 0; i < sizeof(buffer); ++i)
    {
        EXPECT_EQ(buffer[i], ZEROIZE_PATTERN_REVERSE) << "Buffer not zeroized at index " << i;
    }
}

TEST_F(zeroize_test, ZeroizeReturnsNonZeroOnNullPointer)
{
    EXPECT_NE(zeroize(NULL, 10), 0);
}

TEST_F(zeroize_test, ZeroizeReturnsMinusOneOnZeroSize)
{
    unsigned char buffer[8];
    EXPECT_EQ(zeroize(buffer, 0), -1);
}

TEST_F(zeroize_test, IsZeroizedReturnsTrueForZeroizedBuffer)
{
    unsigned char buffer[8];
    memset(buffer, ZEROIZE_PATTERN_REVERSE, sizeof(buffer));
    EXPECT_TRUE(is_zeroized(buffer, sizeof(buffer)));
}

TEST_F(zeroize_test, IsZeroizedReturnsFalseForNonZeroizedBuffer)
{
    unsigned char buffer[8];
    memset(buffer, ZEROIZE_PATTERN, sizeof(buffer));
    EXPECT_FALSE(is_zeroized(buffer, sizeof(buffer)));
}

TEST_F(zeroize_test, IsZeroizedReturnsFalseForZeroSize)
{
    unsigned char buffer[4] = {};
    EXPECT_FALSE(is_zeroized(buffer, 0));
}
