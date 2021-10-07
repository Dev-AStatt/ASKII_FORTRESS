#include "EngineUtilSaveLoad.h"

EngineUtilSaveLoad::EngineUtilSaveLoad()
{

}


int EngineUtilSaveLoad::SaveConfig(int worldSize) {

    std::ofstream fileSaveConfig ("saves/saveconfig.txt");
    if(fileSaveConfig.is_open()) {
        fileSaveConfig << "World Size: " + std::to_string(worldSize) + "\n";

        fileSaveConfig.close();
        bConfigSaved = true;
        return 1;
    }
    else return -1;
}


int EngineUtilSaveLoad::saveChunks(int worldSize, Maps* chunkMapToSave) {
    if(bConfigSaved) {
        for (int c = 0; c < (worldSize*worldSize); ++c) {

        }


        return 1;
    }
    else {
        return -2;
    }
    return -1;
}



//ofstream myfile ("example.txt");
//  if (myfile.is_open())
//  {
//    myfile << "This is a line.\n";
//    myfile << "This is another line.\n";
//    myfile.close();
//  }
//  else cout << "Unable to open file";
