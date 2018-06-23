#include "gtest/gtest.h"

#include "Item.h"

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
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


