#pragma once

namespace AKI {

struct I3d {
	int x;
	int y;
	int z;

	I3d(int nX, int nY, int nZ) {x = nX; y = nY; z = nZ;}
	I3d() : x(0), y(0), z(0) {}
};

}
