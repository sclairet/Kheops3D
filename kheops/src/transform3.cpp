
#include "core3.h"
#include "transform3.h"



namespace KHEOPS
{

	

Translation3D Translation3D::sNullTranslation3D;

Translation3D::Translation3D()
{
    fTx = 0.0;
	fTy = 0.0; 
	fTz = 0.0;
}


Translation3D::Translation3D( real3 inTx, real3 inTy, real3 inTz)
{
    fTx = inTx;
	fTy = inTy; 
	fTz = inTz;
}


Translation3D::Translation3D( const Translation3D& inSource)
{
    fTx = inSource.fTx;
	fTy = inSource.fTy; 
	fTz = inSource.fTz;
}


Translation3D::~Translation3D()
{
}


Translation3D& Translation3D::operator=(const Translation3D& inSource)
{
    fTx = inSource.fTx;
	fTy = inSource.fTy; 
	fTz = inSource.fTz;
    return *this;
}



// ============================================================================



Rotation3D::Rotation3D()
{
    _Init( 0.0, 0.0, 0.0);
}


Rotation3D::Rotation3D( real3 inRx, real3 inRy, real3 inRz)
{
    _Init( inRx, inRy, inRz);
}


Rotation3D::Rotation3D( const Rotation3D& inSource)
{
    _Init( inSource.fRx, inSource.fRy, inSource.fRz);
}


Rotation3D::~Rotation3D()
{
}


void Rotation3D::SetRx( real3 inRx)
{
    if (inRx != fRx)
    {
        fRx = inRx;
    }
}


void Rotation3D::SetRy( real3 inRy)
{
    if (inRy != fRy)
    {
        fRy = inRy;
    }
}


void Rotation3D::SetRz( real3 inRz)
{
    if (inRz != fRz)
    {
        fRz = inRz;
    }
}


Rotation3D& Rotation3D::operator=( const Rotation3D& inSource)
{
    _Init( inSource.fRx, inSource.fRy, inSource.fRz);
    return *this;
}


bool Rotation3D::operator==(const Rotation3D& inSource)
{
    return (fRx == inSource.fRx && fRy == inSource.fRy && fRz == inSource.fRz);
}


bool Rotation3D::operator!=(const Rotation3D& inSource)
{
    return (fRx != inSource.fRx || fRy != inSource.fRy || fRz != inSource.fRz);
}


void Rotation3D::_Init( real3 inRx, real3 inRy, real3 inRz)
{
    fRx = inRx;
    fRy = inRy;
    fRz = inRz;
}





} // namespace KHEOPS