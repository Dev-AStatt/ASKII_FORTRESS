TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

SOURCES += \
    EngineUtilSaveLoad.cpp \
    GameEngine.cpp \
    InfoDisplay.cpp \
    Main.cpp \
    entityFunctions/entities/Ent.cpp \
	entityFunctions/entitieshandler.cpp \
    mapFunctions/MapUtilChunkGen.cpp \
    mapFunctions/Maps.cpp \
    mapFunctions/cChunk.cpp \
    objectFunctions/objecthandler.cpp \
    olcPixelGameEngine.cpp \

HEADERS += \
    EngineUtilSaveLoad.h \
    GameEngine.h \
    InfoDisplay.h \
    InspectionCursor.h \
	entityFunctions/entities/Ent.h \
	entityFunctions/entities/EntHuman.h \
	entityFunctions/entitieshandler.h \
    mapFunctions/MapUtilChunkGen.h \
    mapFunctions/MapUtilTileIDList.h \
    mapFunctions/Maps.h \
    mapFunctions/Tiles.h \
    mapsFunctions/cChunk.h \
    objectFunctions/Object.h \
    objectFunctions/objecthandler.h \
    olcPixelGameEngine.h \

DISTFILES += \
    art/Phoebus_16x16_Next.png
