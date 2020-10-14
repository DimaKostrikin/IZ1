#include "gtest/gtest.h"

extern "C" {
#include "HWRK/utils.h"
}

TEST(read_string, ok) {
    ASSERT_EQ(read_string(nullptr), nullptr);
}

TEST(filter, ok) {
    ASSERT_EQ(filter(nullptr, nullptr, nullptr), -1);
}
