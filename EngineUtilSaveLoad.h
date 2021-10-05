#pragma once

#include <iostream>
#include <fstream>
#include "olcPixelGameEngine.h"
#include "Maps.h"


class EngineUtilSaveLoad
{
private:
    bool bConfigSaved = false;

public:
    EngineUtilSaveLoad();

    //If -1 is returned, save function failed
    int SaveConfig(int worldSize);

    //Saves the cunks to savedchunks.csv
    //returns 1 if save was sucsessful
    //returns -1 if save failed
    //returns -2 if saveconfig flag was not set
    int saveChunks(int worldSize);
};


