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

TEST(get_lexem, ok) {
    char test1[10] = "123456://";
    char test_dot[10] = "123456as.";
    char test_space[10] = "123456as ";
    char test_end[10] = "123456as\0";
    char test_nothing[10] = "123456aaa";
    ASSERT_EQ(get_lexem(test1), LEXEM_PROTOCOL);
    ASSERT_EQ(get_lexem(test_dot), LEXEM_DOT);
    ASSERT_EQ(get_lexem(test_space), LEXEM_SPACE);
    ASSERT_EQ(get_lexem(test_end), LEXEM_END_OF_STRING);
    ASSERT_EQ(get_lexem(test_nothing), LEXEM_NOTHING);
}
