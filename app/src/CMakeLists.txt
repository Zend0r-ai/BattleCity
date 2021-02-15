set(RESOURCE_FILES ../resources/PlayerUP.TGA)

set(SOURCES engine.cpp ../inc/engine.h bullet.cpp player.cpp enemy.cpp eagle.cpp wall.cpp booster.cpp displayableObject.cpp Gui.cpp)

#include_directories(../inc)



add_library(src STATIC ${SOURCES})

set_target_properties(src PROPERTIES RESOURCE "${RESOURCE_FILES}")
