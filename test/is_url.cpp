#include "gtest/gtest.h"

extern "C" {
#include "HWRK/is_url.h"
}

TEST(is_url, ok) {
    ASSERT_EQ(is_url("https://vk.com"), true);
    ASSERT_EQ(is_url("https://vk.com/feed"), true);
    ASSERT_EQ(is_url("https://vk.com./feed"), true);
    ASSERT_EQ(is_url("https://ru.wikipedia.org/"), true);

    ASSERT_EQ(is_url("http://vkcom/feed"), false);
    ASSERT_EQ(is_url("af.dkjf.eakjfe.a//kjaefkj"), false);
    ASSERT_EQ(is_url("afdkjfeakjfeakjaefkj"), false);
    ASSERT_EQ(is_url("://vk.com"), false);
    ASSERT_EQ(is_url("https://vkcom"), false);
    ASSERT_EQ(is_url("https://vkcom."), false);
}
