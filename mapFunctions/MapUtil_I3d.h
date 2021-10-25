#pragma once

namespace AKI {

struct I3d {
	int x;
	int y;
	int z;

	I3d(int nX, int nY, int nZ) {x = nX; y = nY; z = nZ;}
	I3d() : x(0), y(0), z(0) {}
	I3d I3d_XOffset(int i) {return I3d((this->x + i),this->y,this->z);}
	I3d I3d_YOffset(int i) {return I3d(this->x,(this->y + i),this->z);}
	I3d I3d_ZOffset(int i) {return I3d(this->x,this->y,(this->z + i));}

	I3d  operator +  (const I3d& rhs) const { return I3d(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }
	I3d  operator -  (const I3d& rhs) const { return I3d(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }
	I3d& operator += (const I3d& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
	I3d& operator -= (const I3d& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }

};

}
