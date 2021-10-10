#include "EngineUtilSaveLoad.h"

EngineUtilSaveLoad::EngineUtilSaveLoad()
{

}


int EngineUtilSaveLoad::SaveConfig(int worldSize) {

    std::ofstream fileSaveConfig (saveConfigLocation);
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
        std::ofstream fileChunkSave (saveChunksLocation);
        if (fileChunkSave.is_open()) {
            for (int c = 0; c < (worldSize*worldSize); ++c) {
                for (int i = 0; i < 511; ++i) {
                    std::string s = chunkMapToSave->vptrActiveChunks[c]->compileChunkToString(i);
                    fileChunkSave << s + ",";
                }
                fileChunkSave << "\n";
            }
            fileChunkSave.close();
        }
        return 1;
    }
    else {
        return -2;
    }
    return -1;
}

int EngineUtilSaveLoad::loadchunks(Maps* unloadedMap) {

    int worldsize = loadWorldSize();
    if (worldsize > 0) {
        //start loading chunks
        std::string sWholeChunkLine;

        std::ifstream fileChunks (saveChunksLocation);
        if(fileChunks.is_open()) {
            for(int c = 0; c < worldsize*worldsize; ++c) {
                std::getline(fileChunks, sWholeChunkLine);
                stringChunkToActiveChunk(sWholeChunkLine, unloadedMap);
            }
        }
    }

    return -1;
}

void EngineUtilSaveLoad::stringChunkToActiveChunk(std::string sWholeChunk, Maps* unloadedMap) {
    //start with an empty chunk
    std::vector<uint64_t> vSingleLoadedChunk = std::vector<uint64_t>(511,0);
    //seperate whole chunk string to pieces
    std::vector<std::string> vChunkPieces = wholeChunkToPieces(sWholeChunk);
    std::cout << "length: " << vChunkPieces.size();

}

std::vector<std::string> EngineUtilSaveLoad::wholeChunkToPieces(std::string my_str) {
    std::vector<std::string> result;
    //convert to stringstream to use in getline
    std::stringstream s_stream(my_str);
    while(s_stream.good()) {
        std::string substr;
        std::getline(s_stream,substr, ',');
        if(substr != "") {
            result.push_back(substr);
        }

    }
    return result;
}


int EngineUtilSaveLoad::loadWorldSize() {

    std::string sWorldSize;

    std::ifstream fileSaveConfig (saveConfigLocation);
    if(fileSaveConfig.is_open()) {
        std::getline(fileSaveConfig, sWorldSize);
        int parsed_num = extractIntegerWords(sWorldSize);
        if(parsed_num >= 0) {
              return parsed_num;
        }

    }else {
        //return -1 if open save config fails
        return -1;
    }
    //return -1 if if falls out of else?
    return -1;

}

int EngineUtilSaveLoad::extractIntegerWords(std::string str) {
    std::stringstream ss;

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    std::string temp;
    int found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (std::stringstream(temp) >> found) {
            return found;
        }
    }
    //return -1 if no int is found
    return -1;
}


// std::cout << "parsed Value : " << parsed_num <<"\n";

//ofstream myfile ("example.txt");
//  if (myfile.is_open())
//  {
//    myfile << "This is a line.\n";
//    myfile << "This is another line.\n";
//    myfile.close();
//  }
//  else cout << "Unable to open file";
