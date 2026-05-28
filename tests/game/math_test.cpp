#include "game/math.h"

#include <gtest/gtest.h>

TEST(MathTest, Sum) {
    EXPECT_EQ(game::sum(2, 3), 5);
    EXPECT_EQ(game::sum(-1, 1), 0);
    EXPECT_EQ(game::sum(0, 0), 0);
}
