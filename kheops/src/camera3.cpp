
#include "core3.h"
#include <assert.h>
#include "camera3.h"



namespace KHEOPS
{


Camera::Camera( slong3 inID)
: fID(inID)
{
    fStamp = 0;
}


Camera::Camera( slong3 inID, const Coord3D& inPos)
: World3D( false, inPos), fID(inID)
{
    fStamp = 0;
}


Camera::~Camera()
{
}


void Camera::SetPos( const Coord3D& inPos)
{
    if (fPos != inPos)
    {
        inherited::SetPos( inPos);
        Touch();
    }
}


void Camera::FocusOnCoord( const Coord3D& inCoord)
{
	// TBD
}



// ============================================================================



ScreenWorld::ScreenWorld()
{
    fZ = 0;
    fStamp = 0;
    fScreenWidth = 800;
    fScreenHeight = 600;
	fScreenX = 0;
	fScreenY = 0;
	fInvertYAxis = false;
}


ScreenWorld::ScreenWorld( const ScreenWorld& inSource)
: World2D( inSource)
{
    fZ = inSource.fZ;
    fStamp = 0;
    fScreenWidth = inSource.fScreenWidth;
    fScreenHeight = inSource.fScreenHeight;
	fScreenX = inSource.fScreenX;
	fScreenY = inSource.fScreenY;
	fInvertYAxis = inSource.fInvertYAxis;
}


ScreenWorld::~ScreenWorld()
{
}


void ScreenWorld::SetPos( const Coord2D& inPos)
{
    if (fPos != inPos)
    {
        inherited::SetPos( inPos);
        Touch();
    }
}


void ScreenWorld::SetZ( real3 inZ)
{
    if (fZ != inZ)
    {
        fZ = inZ;
        Touch();
    }
}


void ScreenWorld::SetScreenPos( slong3 inX, slong3 inY)
{
	fScreenX = inX;
	fScreenY = inY;
}


void ScreenWorld::SetScreenSize( slong3 inWidth, slong3 inHeight)
{
    if (inWidth != fScreenWidth || inHeight != fScreenHeight)
    {
        fScreenWidth = inWidth;
        fScreenHeight = inHeight;
        Touch();
    }
}


void ScreenWorld::GetScreenSize( slong3& outWidth, slong3& outHeight) const
{
	outWidth = fScreenWidth;
	outHeight = fScreenHeight;
}


void ScreenWorld::InvertYAxis( bool inSet)
{
	fInvertYAxis = inSet;
}


bool ScreenWorld::IsYAxisInverted() const
{
	return fInvertYAxis;
}


void ScreenWorld::Transform( const Coord3D& inCoord, const World3D& inWorld, Coord2D &outCoord) const
{
    if (inCoord.GetZ() != 0.0)
    {
		outCoord.SetX( (fZ * inCoord.GetX() / inCoord.GetZ()) + fScreenWidth / 2 + fScreenX);
		outCoord.SetY( (fZ * ((fInvertYAxis) ? -inCoord.GetY() : inCoord.GetY()) / inCoord.GetZ()) + fScreenHeight / 2 + fScreenY);
    //	outCoord.SetX( (fZ * inCoord.GetX() / inCoord.GetZ()) + fPos.GetX());
    //	outCoord.SetY( (fZ * inCoord.GetY() / inCoord.GetZ()) + fPos.GetY());
    }
}


void ScreenWorld::Transform( const ArrayOfCoord3D& inCoords, const World3D& inWorld, ArrayOfCoord2D& outCoords) const
{
    bool ok = (inCoords.size() == outCoords.size());

    assert(ok);

    if (ok)
    {
        for ( size_t pos = 0 ; pos < inCoords.size() ; ++pos )
        {
            Transform( inCoords[pos], inWorld, outCoords[pos]);
        }
    }
}


void ScreenWorld::Transform( const ArrayPtrOfCoord3D& inCoords, const World3D& inWorld, ArrayPtrOfCoord2D& outCoords) const
{
    bool ok = (inCoords.size() == outCoords.size());

    assert(ok);

    if (ok)
    {
        for ( size_t pos = 0 ; pos < inCoords.size() ; ++pos )
        {
            const Coord3D *iCoord = inCoords[pos];
			Coord2D *oCoord = outCoords[pos];

            if (iCoord != NULL && oCoord != NULL)
            {
                Transform( *iCoord, inWorld, *oCoord);
            }
        }
    }
}



} // namespace KHEOPS