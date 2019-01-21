
#include "core3.h"
#include <math.h>
#include "vector3.h"



namespace KHEOPS
{



Vector3D Vector3D::sNullVector( 0, 0, 0);


Vector3D::Vector3D()
{
    fVx = 0;
    fVy = 0;
    fVz = 0;
}


Vector3D::Vector3D( real3 inVx, real3 inVy, real3 inVz)
{
    fVx = inVx;
    fVy = inVy;
    fVz = inVz;
}


Vector3D::Vector3D( const Coord3D& inCoord)
{
	fVx = inCoord.GetX();
	fVy = inCoord.GetY();
	fVz = inCoord.GetZ();
}


Vector3D::Vector3D( const Coord3D& inFrom, const Coord3D& inTo)
{
	fVx = inTo.GetX() - inFrom.GetX();
	fVy = inTo.GetY() - inFrom.GetY();
	fVz = inTo.GetZ() - inFrom.GetZ();
}


Vector3D::Vector3D( const Vector3D& inSource)
{
    fVx = inSource.fVx;
    fVy = inSource.fVy;
    fVz = inSource.fVz;
}


Vector3D::~Vector3D()
{
}


bool Vector3D::IsNull() const
{
	return (fVx == 0) && (fVy == 0) && (fVz == 0);
}


void Vector3D::Normalize()
{
	real3 module = GetModule();
	fVx /= module;
	fVy /= module;
	fVz /= module;
}


Vector3D& Vector3D::operator=( const Vector3D& inSource)
{
    fVx = inSource.fVx;
    fVy = inSource.fVy;
    fVz = inSource.fVz;
    return *this;
}


Vector3D& Vector3D::operator+( const Vector3D& inSource)
{
    fVx += inSource.fVx;
    fVy += inSource.fVy;
    fVz += inSource.fVz;
    return *this;
}


Vector3D& Vector3D::operator-( const Vector3D& inSource)
{
    fVx -= inSource.fVx;
    fVy -= inSource.fVy;
    fVz -= inSource.fVz;
    return *this;
}


Vector3D& Vector3D::operator*( const real3& inValue)
{
	fVx *= inValue;
    fVy *= inValue;
    fVz *= inValue;
	return *this;
}


real3 Vector3D::operator*( const Vector3D& inVector) const
{
    return fVx * inVector.fVx + fVy * inVector.fVy + fVz * inVector.fVz;
}


const Vector3D Vector3D::operator^( const Vector3D& inVector) const
{
    Vector3D result;

    result.fVx = (fVy * inVector.fVz) - (fVz * inVector.fVy);
    result.fVy = (fVz * inVector.fVx) - (fVx * inVector.fVz);
    result.fVz = (fVx * inVector.fVy) - (fVy * inVector.fVx);
    return result;
}


const Vector3D Vector3D::CalcCrossProduct( const Vector3D& inFirst,  const Vector3D& inSecond, bool inIsDirectWorld)
{
    Vector3D result;

	if (inIsDirectWorld)
	{
		result.fVx = (inFirst.fVy * inSecond.fVz) - (inFirst.fVz * inSecond.fVy);
		result.fVy = (inFirst.fVz * inSecond.fVx) - (inFirst.fVx * inSecond.fVz);
		result.fVz = (inFirst.fVx * inSecond.fVy) - (inFirst.fVy * inSecond.fVx);
	}
	else
	{
		result.fVx = (- inFirst.fVy * inSecond.fVz) - (- inFirst.fVz * inSecond.fVy);
		result.fVy = (- inFirst.fVz * inSecond.fVx) - (- inFirst.fVx * inSecond.fVz);
		result.fVz = - ((inFirst.fVx * inSecond.fVy) - (inFirst.fVy * inSecond.fVx));
	}

    return result;
}


real3 Vector3D::GetModule() const
{
	return sqrt( pow( fVx, 2) + pow( fVy, 2) + pow( fVz, 2));
}


void Vector3D::SetModule( real3 inModule)
{
	real3 module = GetModule();
	fVx *= inModule/module;
	fVy *= inModule/module;
	fVz *= inModule/module;
}



} // namespace KHEOPS