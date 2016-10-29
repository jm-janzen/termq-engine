
#include "gtest/gtest.h"

#include "../src/entities/Entity.h"
#include "../src/game.h"

/*
 * Method tests
 */

TEST(Entity, equality) {
    Entity e1;
    Entity e2;
    e1.setPos({0,0});
    e2.setPos({0,0});
    e1.setChar('&');
    e2.setChar('&');

    bool expect = true;
    bool actual = (e1 == e2);

    ASSERT_EQ( expect, actual );
}

/* Direction tests */
TEST(Entity, isDirection) {
    Entity e1;
    Entity e2;
    e1.setPos({1,1}); // source
    e2.setPos({0,0}); // target

    // target is NorthWest of source
    bool expect = (
           !e1.isNorth(e2)
        && !e1.isSouth(e2)
        && !e1.isEast(e2)
        && !e1.isWest(e2)
        && !e1.isNorthEast(e2)
        && !e1.isSouthEast(e2)
        && !e1.isSouthWest(e2)
        &&  e1.isNorthWest(e2)
    );
    bool actual = true;

    ASSERT_EQ( expect, actual );
}

/*
 * Member get/set tests
 */

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

TEST(Entity, disp_colo) {
    Entity e;
    init_pair(0, COLOR_WHITE, -1);
    e.setColo(COLOR_PAIR(0));

    int expect = COLOR_PAIR(0);
    int actual = e.getDispColo();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, name) {
    Entity e;
    e.setName("Yours truly");

    std::string expect = "Yours truly";
    std::string actual = e.getName();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, type) {
    Entity e;
    e.setName("Introvert");

    std::string expect = "Introvert";
    std::string actual = e.getName();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, desc) {
    Entity e;
    e.setName("Just another dreamer");

    std::string expect = "Just another dreamer";
    std::string actual = e.getName();

    ASSERT_EQ( expect, actual );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


