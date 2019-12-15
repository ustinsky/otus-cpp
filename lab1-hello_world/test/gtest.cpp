#include <gtest/gtest.h>
#include "../lib.h"

TEST(ExampleTests, DemonstrateGTestMacros) {
    EXPECT_TRUE( version() > 0 );
}