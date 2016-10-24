#include <gtest/gtest.h>
#include "../entities/Entity.h"

TEST( a, b ) {
    ASSERT_EQ( "OINK", "OINK" );
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
