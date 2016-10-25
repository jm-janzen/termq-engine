#include <gtest/gtest.h>
#include "../src/game.h"
#include "../src/entities/Entity.h"

TEST( Entity, Position ) {
    Entity e;
    e.setPos({0,0});

    vec2ui expect = {0,0};

    ASSERT_EQ(e.getPos(), expect);
}
TEST( b, b ) {
    ASSERT_EQ( "OINK", "OINK" );
}
TEST( b, a ) {
    ASSERT_EQ( "OINK", "OINK" );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
