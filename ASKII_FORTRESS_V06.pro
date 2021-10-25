TEMPLATE = app
CONFIG += console c++17
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
	libraries/olcPixelGameEngine.cpp \
    mapFunctions/MapUtilChunkGen.cpp \
    mapFunctions/Maps.cpp \
    mapFunctions/cChunk.cpp \
    objectFunctions/objecthandler.cpp \


HEADERS += \
    EngineUtilSaveLoad.h \
    GameEngine.h \
    InfoDisplay.h \
    InspectionCursor.h \
    Popup.h \
    Tilesets.h \
	entityFunctions/entities/Ent.h \
    entityFunctions/entities/EntDest.h \
	entityFunctions/entities/EntHuman.h \
	entityFunctions/entitieshandler.h \
	libraries/olcPixelGameEngine.h \
    mapFunctions/ChunkDataStruct.h \
    mapFunctions/MapUtilChunkGen.h \
    mapFunctions/MapUtilTileIDList.h \
    mapFunctions/MapUtil_I3d.h \
    mapFunctions/Maps.h \
    mapFunctions/TileFunctions/TileSlope.h \
    mapFunctions/TileFunctions/Tiles.h \
    mapFunctions/cChunk.h \
    objectFunctions/Object.h \
    objectFunctions/objecthandler.h \


DISTFILES += \
    art/Phoebus_16x16_Next.png
