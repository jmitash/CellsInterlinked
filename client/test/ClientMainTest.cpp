
#include <spdlog/spdlog.h>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    spdlog::info("Test");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(ClientMainTest, TestsWork) {
    EXPECT_TRUE(FALSE);
}