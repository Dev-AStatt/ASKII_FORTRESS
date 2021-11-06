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
	engine/graphicsengine.cpp \
	entityFunctions/EntSight.cpp \
    entityFunctions/entities/Ent.cpp \
	entityFunctions/entitieshandler.cpp \
	libraries/olcPixelGameEngine.cpp \
    mapFunctions/MapUtilChunkGen.cpp \
    mapFunctions/Maps.cpp \
    mapFunctions/cChunk.cpp \
    objectFunctions/objecthandler.cpp \


HEADERS += \
    EngineUtilSaveLoad.h \
    GameConfig.h \
    GameEngine.h \
    InfoDisplay.h \
    InspectionCursor.h \
    Popup.h \
	engine/graphicsengine.h \
	entityFunctions/EntDest.h \
	entityFunctions/EntSight.h \
	entityFunctions/TreeDataStructure.h \
	entityFunctions/entities/Ent.h \
	entityFunctions/entities/EntHuman.h \
    entityFunctions/entities/TreeDataStructure.h \
	entityFunctions/entitieshandler.h \
	libraries/olcPixelGameEngine.h \
    mapFunctions/ChunkDataStruct.h \
    mapFunctions/MapUtilChunkGen.h \
    mapFunctions/MapUtilTileIDList.h \
    mapFunctions/Maps.h \
    mapFunctions/cChunk.h \
    objectFunctions/Object.h \
    objectFunctions/objecthandler.h \


DISTFILES += \
	art/Phoebus_16x16_Next.png
