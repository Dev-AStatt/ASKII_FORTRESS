#pragma once
#include <cstdint> // include this header for uint64_t
#include <vector>

struct ChunkDataStruct {
	std::vector<uint64_t> slabs = std::vector<uint64_t>(511,0);
	std::vector<uint64_t> inFill = std::vector<uint64_t>(511,0);

};
