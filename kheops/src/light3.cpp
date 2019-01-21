
#include "core3.h"
#include "light3.h"



namespace KHEOPS
{



Light::Light( slong3 inID)
: fID(inID), fIntensity(100), fCameraBinding(0)
{
}


Light::Light( slong3 inID, const Coord3D& inPos)
: World3D( false, inPos), fID(inID), fIntensity(100), fCameraBinding(0)
{
}


Light::~Light()
{
}


void Light::SetIntensity( slong3 inIntensity)
{
	fIntensity = inIntensity;
}


slong3 Light::GetIntensity() const
{
	return fIntensity;
}



} // namespace KHEOPS