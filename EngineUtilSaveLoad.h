#pragma once

#include <iostream>
#include <fstream>

#include "olcPixelGameEngine.h"
#include "mapFunctions/Maps.h"



class EngineUtilSaveLoad
{
private:

    std::string saveConfigLocation = "saves/saveconfig.txt";
    std::string saveChunksLocation = "saves/savedchunks.csv";
    bool bConfigSaved = false;
public:
    EngineUtilSaveLoad();

    //If -1 is returned, save function failed
    int SaveConfig(int worldSize);

    //Saves the cunks to savedchunks.csv
    //returns 1 if save was sucsessful
    //returns -1 if save failed
    //returns -2 if saveconfig flag was not set
    bool saveChunks(int worldSize, Maps* chunkMapToSave);

    bool loadchunks(Maps* unloadedMap);

    void stringChunkToActiveChunk(int chunkNum, int worldsize, std::string sWholeChunk, Maps* unloadedMap);

    std::vector<uint64_t> intToUint(std::vector<std::string> vect_s);

    //takes a whole string of comma deliminated values, and returns
    //a vector of strings that were seperated.
    std::vector<std::string> wholeChunkToPieces(std::string my_str);

    //function will open saveconfig and read the first line and retur
    //the intager saved there. When more config is added this will need
    //to be fixed.
    int loadWorldSize();
    //takes in a string, and returns the intager it finds in it.
    //used for returning config intager entries.
    int extractIntegerWords(std::string str);
};


