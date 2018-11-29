#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Base64EncoderDecoder.h"

TEST(SimpleTest, YYY) {
    ASSERT_EQ(0, 0);
}
/*
TEST(BlockEncoderTest, NotFullBlock) {
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'w', 'Q', 0})), "d1E=");
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'!', '$', 0})), "ISQ=");
    ASSERT_EQ(encodeBuffer(std::array<char, 3>({'{', 0, 0})), "ew==");
}*/
