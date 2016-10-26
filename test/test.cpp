
#include "gtest/gtest.h"

#include "../src/entities/Entity.h"
#include "../src/game.h"

TEST(vec2ui, equality) {
    Entity e;
    e.setPos({0,0});
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

// TODO separate these tests

TEST(Entity, pos) {
    Entity e;
    e.setPos({0,0});

    vec2ui expect = {0,0};
    vec2ui actual = e.getPos();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, disp_char) {
    Entity e;
    e.setChar('T');

    char expect = 'T';
    char actual = e.getDispChar();

    ASSERT_EQ( expect, actual );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


