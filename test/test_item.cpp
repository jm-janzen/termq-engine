#include "gtest/gtest.h"
#include "../src/spdlog/spdlog.h"

#include "../src/entities/Item.h"

TEST(item, set_getValue) {
    Item item;
    item.setValue(0);

    int expect = 0;
    int actual = item.getValue();

    ASSERT_EQ( expect, actual );
}

TEST(item, set_getOwnership1) {
    Item item;
    item.setOwnership(WORLD);

    Ownership expect = WORLD;
    Ownership actual = item.getOwnership();

    ASSERT_EQ( expect, actual );
}

TEST(item, set_getOwnership2) {
    Item item;
    item.setOwnership(PLAYER);

    Ownership expect = WORLD;
    Ownership actual = item.getOwnership();

    ASSERT_NE( expect, actual );
}

int main(int argc, char **argv) {
    /*
     * NB: If this logger is not initialised, tests will fail.
     */
    auto daily_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/testing", "log", 1024 * 24, 0);
    auto logger = std::make_shared<spdlog::logger>("termq", daily_sink);
    spdlog::register_logger(logger);

    spdlog::get("termq")->info("START TESTING");

    testing::InitGoogleTest(&argc, argv);

    spdlog::get("termq")->info("DONE TESTING");
    return RUN_ALL_TESTS();
}


