
file(GLOB_RECURSE termq_SOURCES "*.cpp")
file(GLOB_RECURSE termq_HEADERS "*.h")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_library(TERMQ_LIB
    directions.h
    game.h
    gameover.cpp
    gameover.h
    menu.h
    entities/Actor.cpp
    entities/Actor.h
    entities/Coin.cpp
    entities/Coin.h
    entities/Enemy.cpp
    entities/Enemy.h
    entities/Entity.cpp
    entities/Entity.h
    entities/Item.cpp
    entities/Item.h
    entities/Player.cpp
    entities/Player.h
    global/difficulty-levels.h
    global/Global.cpp
    global/Global.h
    windows/DiagWindow.cpp
    windows/DiagWindow.h
    windows/MenuWindow.cpp
    windows/MenuWindow.h
    windows/StatusBar.cpp
    windows/StatusBar.h
    windows/Window.cpp
    windows/Window.h
    world/Cell.cpp
    world/Cell.h
    world/Map.cpp
    world/Map.h
    world/World.cpp
    world/World.h
)

add_executable(termq ${termq_SOURCES})
target_link_libraries(termq PRIVATE ${NCURSES_LIBRARIES})
