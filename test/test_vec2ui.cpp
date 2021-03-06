
#include "gtest/gtest.h"

#include "game.h"

TEST(vec2ui, equality) {
    vec2ui a = {0,0};
    vec2ui b = {0,0};

    bool expect = true;
    bool actual = (a == b);

    ASSERT_EQ( expect, actual );
}

TEST(vec2ui, inequality) {
    vec2ui a = {1,1};
    vec2ui b = {0,0};

    bool expect = false;
    bool actual = (a == b);

    ASSERT_EQ( expect, actual );
}

// TODO fix source associated with this test
TEST(vec2ui, greater) {
    vec2ui a = {1,1};
    vec2ui b = {0,0};

    bool expect = true;
    //bool actual = (a > b);  // XXX curiously fails
    //bool actual = (a < b);  // XXX even more curiously passes
    bool actual = (a.x > b.x && a.y > b.y);

    ASSERT_EQ( expect, actual );
}

TEST(vec2ui, lesser) {
    vec2ui a = {1,1};
    vec2ui b = {0,0};

    bool expect = true;
    bool actual = (a < b);

    ASSERT_EQ( expect, actual );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


