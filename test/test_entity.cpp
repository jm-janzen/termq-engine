
#include "gtest/gtest.h"

#include "../src/entities/Entity.h"
#include "../src/game.h"

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


