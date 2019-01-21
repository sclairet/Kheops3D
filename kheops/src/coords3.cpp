
#include "core3.h"
#include "coords3.h"



namespace KHEOPS
{



Coord2D Coord2D::sNullCoord2D;

Coord2D::Coord2D()
{
    fX = 0.0;
    fY = 0.0;
}


Coord2D::Coord2D( real3 inX, real3 inY)
{
    fX = inX;
    fY = inY;
}


Coord2D::Coord2D( const Coord2D& inSource)
{
    fX = inSource.fX;
    fY = inSource.fY;
}


Coord2D::~Coord2D()
{
}


Coord2D& Coord2D::operator=(const Coord2D& inSource)
{
    fX = inSource.fX;
    fY = inSource.fY;
    return *this;
}


bool Coord2D::operator==(const Coord2D& inSource)
{
    return (fX == inSource.fX && fY == inSource.fY);
}


bool Coord2D::operator!=(const Coord2D& inSource)
{
    return (fX != inSource.fX || fY != inSource.fY);
}






// ============================================================================



Coord3D Coord3D::sNullCoord3D;

Coord3D::Coord3D()
{
    fX = 0.0;
    fY = 0.0;
    fZ = 0.0;
}


Coord3D::Coord3D( real3 inX, real3 inY, real3 inZ)
{
    fX = inX;
    fY = inY;
    fZ = inZ;
}


Coord3D::Coord3D( const Coord3D& inSource)
{
    fX = inSource.fX;
    fY = inSource.fY;
    fZ = inSource.fZ;
}


Coord3D::~Coord3D()
{
}


void Coord3D::SetX( real3 inX)
{
    fX = inX;
}


void Coord3D::SetY( real3 inY)
{
    fY = inY;
}


void Coord3D::SetZ( real3 inZ)
{
    fZ = inZ;
}


void Coord3D::SetCoordsTo( real3 inX, real3 inY, real3 inZ)
{
    fX = inX;
    fY = inY;
    fZ = inZ;
}


void Coord3D::SetCoordsBy( real3 inTx, real3 inTy, real3 inTz)
{
    fX += inTx;
    fY += inTy;
    fZ += inTz;
}


Coord3D& Coord3D::operator=(const Coord3D& inSource)
{
    fX = inSource.fX;
    fY = inSource.fY;
    fZ = inSource.fZ;
    return *this;
}


bool Coord3D::operator==(const Coord3D& inSource)
{
    return (fX == inSource.fX && fY == fY && fZ == inSource.fZ);
}


bool Coord3D::operator!=(const Coord3D& inSource)
{
    return (fX != inSource.fX || fY != fY || fZ != inSource.fZ);
}


Coord3D& Coord3D::operator*( real3 inValue)
{
	fX *= inValue;
	fY *= inValue;
	fZ *= inValue;
	return *this;
}



} // namespace KHEOPS