
#include "gtest/gtest.h"

#include "Entity.h"
#include "game.h"

/*
 * Method tests
 */

TEST(Entity, equality) {
    Entity e1 = Entity();
    Entity e2 = Entity();
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
    Entity e1 = Entity();
    Entity e2 = Entity();
    e1.setPos({1,1}); // source
    e2.setPos({0,0}); // target

    // target is NorthWest of source
    bool expect = true;
    bool actual = (
           !e1.isNorth(e2)
        && !e1.isSouth(e2)
        && !e1.isEast(e2)
        && !e1.isWest(e2)
        && !e1.isNorthEast(e2)
        && !e1.isSouthEast(e2)
        && !e1.isSouthWest(e2)
        &&  e1.isNorthWest(e2)
    );

    ASSERT_EQ( expect, actual );
}

TEST(Entity, atop) {
    Entity e = Entity();
    e.setPos({0,0});
    vec2ui nextToEntity = {1,1};

    bool expect = true;
    bool actual = (e.isAdjacent(nextToEntity));

    ASSERT_EQ( expect, actual );
}

TEST(Entity, isAdjacent) {
    Entity e = Entity();
    e.setPos({0,0});
    vec2ui onEntity = {0,0};

    bool expect = true;
    bool actual = (e.atop(onEntity));

    ASSERT_EQ( expect, actual );
}

TEST(Entity, getDistance) {
    Entity e = Entity();
    e.setPos({0,0});
    vec2ui nearBy = {10,10};

    int_fast8_t expect = 14;  // square root of getDistanceX, getDistanceY
    int_fast8_t actual = e.getDistance(nearBy);

    ASSERT_EQ( expect, actual );
}

TEST(Entity, set_getPosRand) {
    Entity e = Entity();
    e.setPos({0,0});
    e.setPosRand();

    // Position must be within bounds of game_area rect
    bool expect = true;
    bool actual = (
           (e.getPos().x < game_area.right() && e.getPos().x > game_area.left())
        && (e.getPos().y < game_area.bot()   && e.getPos().y > game_area.top())
    );

    ASSERT_EQ( expect, actual );
}

TEST(Entity, getDirection) {
    Entity e1 = Entity();
    Entity e2 = Entity();
    e1.setPos({0,0});
    e2.setPos({5,0});

    Direction expect = E;  // Target is East of source
    Direction actual = e1.getDirection(e2);

    ASSERT_EQ( expect, actual );
}

TEST(Entity, render) {
    Entity e = Entity();
    Window w({{0,0},{10,10}});  // 10x10 Window in top-left position
    e.render(w);  // Void function - deprecated anyway
}

/*
 * Member get/set tests
 */

TEST(Entity, pos) {
    Entity e = Entity();
    e.setPos({0,0});

    vec2ui expect = {0,0};
    vec2ui actual = e.getPos();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, disp_char) {
    Entity e = Entity();
    e.setChar('T');

    char expect = 'T';
    char actual = e.getDispChar();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, disp_colo) {
    Entity e = Entity();
    init_pair(0, COLOR_WHITE, -1);
    e.setColo(COLOR_PAIR(0));

    int expect = COLOR_PAIR(0);
    int actual = e.getDispColo();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, name) {
    Entity e = Entity();
    e.setName("Yours truly");

    std::string expect = "Yours truly";
    std::string actual = e.getName();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, type) {
    Entity e = Entity();
    e.setName("Introvert");

    std::string expect = "Introvert";
    std::string actual = e.getName();

    ASSERT_EQ( expect, actual );
}

TEST(Entity, desc) {
    Entity e = Entity();
    e.setName("Just another dreamer");

    std::string expect = "Just another dreamer";
    std::string actual = e.getName();

    ASSERT_EQ( expect, actual );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


