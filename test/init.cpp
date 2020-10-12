#include "gtest/gtest.h"

extern "C" {
#include "HWRK/utils.h"
}

TEST(init, ok) {
    FILE *test_in = fopen("../../IZ1/test/test_is_url.test", "r");
    ASSERT_EQ(init(test_in), 1);
}
