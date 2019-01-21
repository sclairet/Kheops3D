
#include "core3.h"
#include <math.h>
#include <assert.h>
#include "world3.h"



namespace KHEOPS
{




World2D World2D::sRootWorld2D;

World2D::World2D()
{
    fParent = NULL;
}


World2D::World2D( const World2D* inParent, const Coord2D& inPos)
{
    fParent = NULL;
    fPos = inPos;
}


World2D::World2D( const World2D& inSource)
{
    fParent = NULL;
    fPos = inSource.fPos;
}


World2D::~World2D()
{
}


void World2D::Transform( Coord2D& inCoord, const World2D& inWorld) const
{
    real3 xOffset = fPos.GetX() - inWorld.GetPos().GetX();
    real3 yOffset = fPos.GetY() - inWorld.GetPos().GetY();
    inCoord.SetCoordsBy( xOffset, yOffset);
}


void World2D::Transform( ArrayOfCoord2D& inCoords, const World2D& inWorld) const
{
    real3 xOffset = fPos.GetX() - inWorld.GetPos().GetX();
    real3 yOffset = fPos.GetY() - inWorld.GetPos().GetY();

    for ( ArrayOfCoord2D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter )
    {
        (*iter).SetCoordsBy( xOffset, yOffset);
    }
}



// ============================================================================


Axis3D Axis3D::sXAxis( Vector3D( 1, 0, 0));
Axis3D Axis3D::sYAxis( Vector3D( 0, 1, 0));
Axis3D Axis3D::sZAxis( Vector3D( 0, 0, 1));

Axis3D::Axis3D()
{
}


Axis3D::Axis3D( const Vector3D& inVector)
: fVector( inVector)
{
}


Axis3D::Axis3D( const Coord3D& inFirstCoord, const Coord3D& inSecondCoord)
: fVector( inFirstCoord, inSecondCoord)
{
}


Axis3D::~Axis3D()
{
}



// ============================================================================



World3D World3D::sRootWorld3D( false);


World3D::World3D()
{
    fParent = NULL;
	fIsDirect = false;
	fOrientedAxis = eUndefinedAxis;
	fXAxisRotation = 0;
	fYAxisRotation = 0;
	fZAxisRotation = 0;
}


World3D::World3D( bool inIsDirect)
{
    fParent = NULL;
	fIsDirect = inIsDirect;
	fOrientedAxis = eUndefinedAxis;
	fXAxisRotation = 0;
	fYAxisRotation = 0;
	fZAxisRotation = 0;
}


World3D::World3D( bool inIsDirect, const Coord3D& inPos)
{
    fParent = NULL;
    fPos = inPos;
	fIsDirect = inIsDirect;
	fOrientedAxis = eUndefinedAxis;
	fXAxisRotation = 0;
	fYAxisRotation = 0;
	fZAxisRotation = 0;
}


World3D::World3D( const World3D& inSource)
{
    fParent = inSource.fParent;
    fPos = inSource.fPos;
	fIsDirect = inSource.fIsDirect;
	fOrientedAxis = inSource.fOrientedAxis;
	fAxisOrientation = inSource.fAxisOrientation;
	fXAxisRotation = inSource.fXAxisRotation;
	fYAxisRotation = inSource.fYAxisRotation;
	fZAxisRotation = inSource.fZAxisRotation;
}


World3D::~World3D()
{
}


void World3D::SetAxisOrientation( EAxis inAxis, const Vector3D& inVector)
{
	if (inVector.IsNull())
	{
		fOrientedAxis = eUndefinedAxis;
		fAxisOrientation = inVector;
		fXAxisRotation = 0;
		fYAxisRotation = 0;
		fZAxisRotation = 0;
	}
	else
	{
		assert(inAxis >= eFirstAxis && inAxis <= eLastAxis);

		fOrientedAxis = inAxis;
		fAxisOrientation = inVector;
		fAxisOrientation.Normalize();

		if (inAxis == eXAxis)
		{
			assert(false);
		}
		else if (inAxis == eYAxis)
		{
			assert(false);
		}
		else if (inAxis == eZAxis)
		{
			PolarCoord polarCoord;
			Vector3D vector( fAxisOrientation);

			Math::GetPolarCoordsFromYAxis( vector.GetCoords(), polarCoord, eBaseXoZ);
			fYAxisRotation = - (polarCoord.fArgument - kPI2);

			Math::RotateBy( vector, 0, fYAxisRotation, 0, fIsDirect);
			Math::GetPolarCoordsFromXAxis( vector.GetCoords(), polarCoord, eBaseZoY);
			fXAxisRotation = -polarCoord.fArgument;
			
			fZAxisRotation = 0;
		}
	}
}


bool World3D::GetAxisOrientation( EAxis& outAxis, Vector3D& outVector) const
{
	if (fOrientedAxis != eUndefinedAxis)
	{
		outAxis = fOrientedAxis;
		outVector = fAxisOrientation;
		return true;
	}
	else
	{
		return false;
	}
}


void World3D::SetAxisRotation( EAxis inAxis, real3 inRotation)
{
	assert(inAxis >= eFirstAxis && inAxis <= eLastAxis);

	if (inAxis >= eFirstAxis && inAxis <= eLastAxis)
	{
		if (fOrientedAxis != eUndefinedAxis)
			assert(inAxis == fOrientedAxis);

		if ((fOrientedAxis == eUndefinedAxis) || (inAxis == fOrientedAxis))
		{
			if (inAxis == eXAxis)
				fXAxisRotation = inRotation;
			else if (inAxis == eYAxis)
				fYAxisRotation = inRotation;
			else if (inAxis == eZAxis)
				fZAxisRotation = inRotation;
		}
	}
}


real3 World3D::GetAxisRotation( EAxis inAxis) const
{
	real3 result = 0;

	assert(inAxis >= eFirstAxis && inAxis <= eLastAxis);

	if (inAxis >= eFirstAxis && inAxis <= eLastAxis)
	{
		if (inAxis == eXAxis)
			result = fXAxisRotation;
		else if (inAxis == eYAxis)
			result = fYAxisRotation;
		else if (inAxis == eZAxis)
			result = fZAxisRotation;
	}

	return result;
}


void World3D::Transform( Coord3D& inCoord, const World3D& inWorld) const
{
	real3 x = inCoord.GetX() + fPos.GetX() - inWorld.GetPos().GetX();
    real3 y = inCoord.GetY() + fPos.GetY() - inWorld.GetPos().GetY();
    real3 z = inCoord.GetZ() + fPos.GetZ() - inWorld.GetPos().GetZ();

	inCoord.SetCoordsTo( x, y, z);

	if (inWorld.fOrientedAxis != eUndefinedAxis)
	{
		assert(fOrientedAxis == eUndefinedAxis);

		if (inWorld.fOrientedAxis == eXAxis)
		{
			assert(false);
		}
		else if (inWorld.fOrientedAxis == eYAxis)
		{
			assert(false);
		}
		else if (inWorld.fOrientedAxis == eZAxis)
		{
			Math::RotateBy( inCoord, 0, inWorld.fYAxisRotation, 0, inWorld.IsDirect());
			Math::RotateBy( inCoord, inWorld.fXAxisRotation, 0, 0, inWorld.IsDirect());
			Math::RotateBy( inCoord, 0, 0, inWorld.fZAxisRotation, inWorld.IsDirect());
		}
	}
	else if (fOrientedAxis != eUndefinedAxis)
	{
		if (fOrientedAxis == eXAxis)
		{
			assert(false);
		}
		else if (fOrientedAxis == eYAxis)
		{
			assert(false);
		}
		else if (fOrientedAxis == eZAxis)
		{
			Math::RotateBy( inCoord, 0, 0, -inWorld.fZAxisRotation, inWorld.IsDirect());
			Math::RotateBy( inCoord, -inWorld.fXAxisRotation, 0, 0, inWorld.IsDirect());
			Math::RotateBy( inCoord, 0, -inWorld.fYAxisRotation, 0, inWorld.IsDirect());
		}
	}
}


void World3D::Transform( ArrayOfCoord3D& inCoords, const World3D& inWorld) const
{
    for ( ArrayOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter )
    {
        Transform(  (*iter), inWorld);
    }
}


void World3D::Transform( ArrayPtrOfCoord3D& inCoords, const World3D& inWorld) const
{
    for ( ArrayPtrOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter )
    {
        Coord3D *coord = *iter;
        if (coord != NULL)
        {
            Transform( *coord, inWorld);
        }
    }

}


void World3D::Transform( Vector3D& inVector, const World3D& inWorld) const
{
	if (inWorld.fOrientedAxis != eUndefinedAxis)
	{
		assert(fOrientedAxis == eUndefinedAxis);

		if (inWorld.fOrientedAxis == eXAxis)
		{
			assert(false);
		}
		else if (inWorld.fOrientedAxis == eYAxis)
		{
			assert(false);
		}
		else if (inWorld.fOrientedAxis == eZAxis)
		{
			Math::RotateBy( inVector, 0, inWorld.fYAxisRotation, 0, inWorld.IsDirect());
			Math::RotateBy( inVector, inWorld.fXAxisRotation, 0, 0, inWorld.IsDirect());
			Math::RotateBy( inVector, 0, 0, inWorld.fZAxisRotation, inWorld.IsDirect());
		}
	}
	else if (fOrientedAxis != eUndefinedAxis)
	{
		if (fOrientedAxis == eXAxis)
		{
			assert(false);
		}
		else if (fOrientedAxis == eYAxis)
		{
			assert(false);
		}
		else if (fOrientedAxis == eZAxis)
		{
			Math::RotateBy( inVector, 0, 0, -fZAxisRotation, inWorld.IsDirect());
			Math::RotateBy( inVector, -fXAxisRotation, 0, 0, inWorld.IsDirect());
			Math::RotateBy( inVector, 0, -fYAxisRotation, 0, inWorld.IsDirect());
		}
	}
}


void World3D::Transform( ArrayOfVector3D& inVectors, const World3D& inWorld) const
{
    for ( ArrayOfVector3D_iter iter = inVectors.begin() ; iter != inVectors.end() ; ++iter )
    {
        Transform( (*iter), inWorld);
    }
}


void World3D::Transform( const Coord3D& inCoord, const World3D& inWorld, Coord3D &outCoord) const
{
	outCoord = inCoord;
	inWorld.Transform( outCoord, *this);
}


void World3D::Transform( const ArrayOfCoord3D& inCoords, const World3D& inWorld, ArrayOfCoord3D& outCoords) const
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


void World3D::Transform( const ArrayPtrOfCoord3D& inCoords, const World3D& inWorld, ArrayOfCoord3D& outCoords) const
{
    bool ok = (inCoords.size() == outCoords.size());

    assert(ok);

    if (ok)
    {
        for ( size_t pos = 0 ; pos < inCoords.size() ; ++pos )
        {
            const Coord3D *iCoord = inCoords[pos];

            if (iCoord != NULL)
            {
				Transform( *iCoord, inWorld, outCoords[pos]);
            }
        }
    }
}


void World3D::Transform( const ArrayPtrOfCoord3D& inCoords, const World3D& inWorld, ArrayPtrOfCoord3D& outCoords) const
{
    bool ok = (inCoords.size() == outCoords.size());

    assert(ok);

    if (ok)
    {
        for ( size_t pos = 0 ; pos < inCoords.size() ; ++pos )
        {
            const Coord3D *iCoord = inCoords[pos];
            Coord3D *oCoord = outCoords[pos];

            if (iCoord != NULL && oCoord != NULL)
            {
                Transform( *iCoord, inWorld, *oCoord);
            }
        }
    }
}



} // namespace KHEOPS