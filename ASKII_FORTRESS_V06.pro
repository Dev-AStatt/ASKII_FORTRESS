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
    MapUtilChunkGen.cpp \
    Maps.cpp \
    cChunk.cpp \
    olcPixelGameEngine.cpp

HEADERS += \
    EngineUtilSaveLoad.h \
    Ent.h \
    GameEngine.h \
    InfoDisplay.h \
    InspectionCursor.h \
    MapUtilChunkGen.h \
    MapUtilTileIDList.h \
    Maps.h \
    Tiles.h \
    cChunk.h \
    olcPixelGameEngine.h

DISTFILES += \
    art/Phoebus_16x16_Next.png
