
// 03/06/2008

#include "core3.h"
#include "objects3.h"
#include "motion3.h"


namespace KHEOPS
{



// ============================================================================
// Motion3D base class definition


Motion3D::Motion3D()
{
}


Motion3D::~Motion3D()
{
    fObjects.clear();
}


void Motion3D::AddObject( Object3D *inObject)
{
    fObjects.push_back( inObject);
}



// ============================================================================



Motion3D_rotation::Motion3D_rotation()
{
}


Motion3D_rotation::Motion3D_rotation( const World3D& inCenter, const Rotation3D& inRotation)
{
    fCenter = inCenter;
    fRotation = inRotation;
}


Motion3D_rotation::~Motion3D_rotation()
{
}



} // namespace KHEOPS
