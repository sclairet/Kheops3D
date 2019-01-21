

#include "core3.h"
#include <math.h>
#include <algorithm>
#include <assert.h>
#include "math3.h"


namespace KHEOPS
{



void Math::GetPolarCoordsFromXAxis( const Coord3D& inCoord, PolarCoord& outCoord, EBase inBase, EArgumentInterval inInterval, bool inIsDirectWorld)
{
	if (inIsDirectWorld)
	{
		if (inBase == eBaseYoZ)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetY(), 2) + pow( inCoord.GetZ(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetY(), inCoord.GetZ(), inInterval);
		}
		else if (inBase == eBaseZoY)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetZ(), 2) + pow( inCoord.GetY(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetZ(), -inCoord.GetY(), inInterval);
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		if (inBase == eBaseZoY)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetZ(), 2) + pow( inCoord.GetY(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetZ(), inCoord.GetY(), inInterval);
		}
		else if (inBase == eBaseYoZ)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetZ(), 2) + pow( inCoord.GetY(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetY(), -inCoord.GetZ(), inInterval);
		}
		else
		{
			assert(false);
		}
	}
}


void Math::GetPolarCoordsFromYAxis( const Coord3D& inCoord, PolarCoord& outCoord, EBase inBase, EArgumentInterval inInterval, bool inIsDirectWorld)
{
	if (inIsDirectWorld)
	{
		if (inBase == eBaseZoX)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetZ(), 2) + pow( inCoord.GetX(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetZ(), inCoord.GetX(), inInterval);
		}
		else if (inBase == eBaseXoZ)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetZ(), 2) + pow( inCoord.GetX(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetX(), -inCoord.GetZ(), inInterval);
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		if (inBase == eBaseXoZ)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetX(), 2) + pow( inCoord.GetZ(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetX(), inCoord.GetZ(), inInterval);
		}
		else if (inBase == eBaseZoX)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetX(), 2) + pow( inCoord.GetZ(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetZ(), -inCoord.GetX(), inInterval);
		}
		else
		{
			assert(false);
		}
	}
}


void Math::GetPolarCoordsFromZAxis( const Coord3D& inCoord, PolarCoord& outCoord, EBase inBase, EArgumentInterval inInterval, bool inIsDirectWorld)
{
	if (inIsDirectWorld)
	{
		if (inBase == eBaseXoY)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetX(), 2) + pow( inCoord.GetY(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetX(), inCoord.GetY(), inInterval);
		}
		else if (inBase == eBaseYoX)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetX(), 2) + pow( inCoord.GetY(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetY(), -inCoord.GetX(), inInterval);
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		if (inBase == eBaseYoX)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetY(), 2) + pow( inCoord.GetX(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetY(), inCoord.GetX(), inInterval);
		}
		else if (inBase == eBaseXoY)
		{
			outCoord.fModule = sqrt( pow( inCoord.GetY(), 2) + pow( inCoord.GetX(), 2));
			outCoord.fArgument = ArcTan( inCoord.GetX(), -inCoord.GetY(), inInterval);
		}
		else
		{
			assert(false);
		}
	}
}


void Math::GetPolarCoord( real3 inX, real3 inY, real3& outModule, real3& outArgument, EArgumentInterval inInterval)
{
    outModule = sqrt( pow( inX, 2) + pow( inY, 2));
    outArgument = ArcTan( inX, inY, inInterval);
}


void Math::GetCartesianCoord( Coord3D& outCoord, const PolarCoord& inCoord, EBase inBase, bool inIsDirectWorld)
{
	if (inIsDirectWorld)
	{
		switch (inBase)
		{
			case eBaseYoZ:
			{
				outCoord.SetY( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetZ( inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseZoY:
			{
				outCoord.SetZ( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetY( - inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseZoX:
			{
				outCoord.SetZ( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetX( inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseXoZ:
			{
				outCoord.SetX( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetZ( - inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseXoY:
			{
				outCoord.SetX( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetY( inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseYoX:
			{
				outCoord.SetY( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetX( - inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			default:
				assert(false);
				break;
		}
	}
	else
	{
		switch (inBase)
		{
			case eBaseYoZ:
			{
				outCoord.SetY( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetZ( - inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseZoY:
			{
				outCoord.SetZ( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetY( inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseZoX:
			{
				outCoord.SetZ( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetX( - inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseXoZ:
			{
				outCoord.SetX( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetZ( inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseXoY:
			{
				outCoord.SetX( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetY( - inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			case eBaseYoX:
			{
				outCoord.SetY( inCoord.fModule * cos( inCoord.fArgument));
				outCoord.SetX( inCoord.fModule * sin( inCoord.fArgument));
				break;
			}

			default:
				assert(false);
				break;
		}
	}
}


void Math::GetCartesianCoord( const PolarCoord& inCoord, real3& outX, real3& outY)
{
    outX = inCoord.fModule * cos( inCoord.fArgument);
    outY = inCoord.fModule * sin( inCoord.fArgument);
}


void Math::GetCartesianCoord( real3 inModule, real3 inArgument, real3& outX, real3& outY)
{
    outX = inModule * cos( inArgument);
    outY = inModule * sin( inArgument);
}


real3 Math::DegreeToRadian( real3 inDegree)
{
    return (inDegree * kPI) / 180;
}


real3 Math::RadianToDegree( real3 inRadian)
{
    return ((180 * inRadian) / kPI);
}


real3 Math::ArcTan( real3 inX, real3 inY, EArgumentInterval inInterval)
{
	if (inInterval == eInterval_mPI_PI)
	{
		if (inX > 0)
		{
			return atan( inY / inX);
		}
		else if (inX < 0)
		{
			if (inY >= 0)
				return atan( inY / inX) + kPI;
			else // inY < 0
				return atan( inY / inX) - kPI;
		}
		else // inX == 0
		{
			return (inY > 0) ? kPI2 : -kPI2;
		}
	}
	else if (inInterval == eInterval_0_2PI)
	{
		if (inX > 0)
		{
			if (inY >= 0)
				return atan( inY / inX);
			else // inY < 0
				return atan( inY / inX) + (2 * kPI);
		}
		else if (inX < 0)
		{
			return atan( inY / inX) + kPI;
		}
		else // inX == 0
		{
			return (inY > 0) ? kPI2 : 3 * kPI2;
		}
	}
	else
	{
		assert(false);
	}

	return 0;
}


void Math::RotateBy( Coord3D& inCoord, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld)
{
    real3 mod = 0.0, arg = 0.0;
    real3 x = inCoord.GetX();
    real3 y = inCoord.GetY();
    real3 z = inCoord.GetZ();

	if (inIsDirectWorld)
	{
		// rotation autour de l'axe x
		if (inRx != 0)
		{
			GetPolarCoord( y, z, mod, arg);	// Base YoZ
			y = mod * cos( arg + inRx);
			z = mod * sin( arg + inRx);
		}

		// rotation autour de l'axe y
		if (inRy != 0)
		{
			GetPolarCoord( z, x, mod, arg);	// Base ZoX
			z = mod * cos( arg + inRy);
			x = mod * sin( arg + inRy);
		}

		// rotation autour de l'axe z
		if (inRz != 0)
		{
			GetPolarCoord( x, y, mod, arg);	// Base XoY
			x = mod * cos( arg + inRz);
			y = mod * sin( arg + inRz);
		}
	}
	else
	{
		// rotation autour de l'axe x
		if (inRx != 0)
		{
			GetPolarCoord( z, y, mod, arg);	// Base ZoY
			z = mod * cos( arg + inRx);
			y = mod * sin( arg + inRx);
		}

		// rotation autour de l'axe y
		if (inRy != 0)
		{
			GetPolarCoord( x, z, mod, arg);	// Base XoZ
			x = mod * cos( arg + inRy);
			z = mod * sin( arg + inRy);
		}

		// rotation autour de l'axe z
		if (inRz != 0)
		{
			GetPolarCoord( y, x, mod, arg);	// Base YoX
			y = mod * cos( arg + inRz);
			x = mod * sin( arg + inRz);
		}
	}

    inCoord.SetCoordsTo( x, y, z);
}


void Math::RotateBy( ArrayOfCoord3D& inCoords, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld)
{
    for (ArrayOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter)
    {
        RotateBy( *iter, inRx, inRy, inRz, inIsDirectWorld);
    }
}


void Math::RotateBy( ArrayPtrOfCoord3D& inCoords, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld)
{
    for (ArrayPtrOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter)
    {
        Coord3D *coord = *iter;
        if (coord != NULL)
            RotateBy( *coord, inRx, inRy, inRz, inIsDirectWorld);
    }
}


void Math::RotateBy( Vector3D& inVector, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld)
{
	Coord3D coord( inVector.GetVx(), inVector.GetVy(), inVector.GetVz());

	RotateBy( coord, inRx, inRy, inRz, inIsDirectWorld);

	inVector.SetVx( coord.GetX());
	inVector.SetVy( coord.GetY());
	inVector.SetVz( coord.GetZ());
}


void Math::RotateBy( ArrayOfVector3D& inVectors, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld)
{
    for (ArrayOfVector3D_iter iter = inVectors.begin() ; iter != inVectors.end() ; ++iter)
    {
        RotateBy( *iter, inRx, inRy, inRz, inIsDirectWorld);
    }
}


void Math::GetCoordsForArcPerpendicularToXAxis( ArrayOfCoord3D& outCoords, real3 inFromAngle, real3 inToAngle, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection, bool inIsDirectWorld)
{
	assert(inToAngle >= inFromAngle);

	if (inToAngle >= inFromAngle)
	{
		assert(inDirection == eAnticlockwiseRotation || inDirection == eClockwiseRotation);

		if (inDirection != eAnticlockwiseRotation && inDirection != eClockwiseRotation)
			inDirection = eAnticlockwiseRotation;

		real3 delta = 0, alpha = 0;

		if (inDirection == eAnticlockwiseRotation)
		{
			delta = (inToAngle - inFromAngle) / (inCoordsCount - 1);
			alpha = inFromAngle;
		}
		else
		{
			delta = - (inToAngle - inFromAngle) / (inCoordsCount - 1);
			alpha = inToAngle;
		}

		outCoords.resize( (size_t)inCoordsCount);

		for( ArrayOfCoord3D_iter iter = outCoords.begin() ; iter != outCoords.end() ; ++iter )
		{
			(*iter).SetX( 0);
			
			if (inIsDirectWorld)
			{
				if (inBase == eBaseYoZ)
				{
					(*iter).SetY( inRadius * cos( alpha));
					(*iter).SetZ( inRadius * sin( alpha));
				}
				else if (inBase == eBaseZoY)
				{
					(*iter).SetZ( inRadius * cos( alpha));
					(*iter).SetY( - inRadius * sin( alpha));
				}
				else
				{
					assert(false);
				}
			}
			else
			{
				if (inBase == eBaseZoY)
				{
					(*iter).SetZ( inRadius * cos( alpha));
					(*iter).SetY( inRadius * sin( alpha));
				}
				else if (inBase == eBaseYoZ)
				{
					(*iter).SetY( inRadius * cos( alpha));
					(*iter).SetZ( - inRadius * sin( alpha));
				}
				else
				{
					assert(false);
				}
			}

			alpha += delta;
		}
	}
}


void Math::GetCoordsForArcPerpendicularToYAxis( ArrayOfCoord3D& outCoords, real3 inFromAngle, real3 inToAngle, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection, bool inIsDirectWorld)
{
	assert(inToAngle >= inFromAngle);

	if (inToAngle >= inFromAngle)
	{
		assert(inDirection == eAnticlockwiseRotation || inDirection == eClockwiseRotation);

		if (inDirection != eAnticlockwiseRotation && inDirection != eClockwiseRotation)
			inDirection = eAnticlockwiseRotation;

		real3 delta = 0, alpha = 0;

		if (inDirection == eAnticlockwiseRotation)
		{
			delta = (inToAngle - inFromAngle) / (inCoordsCount - 1);
			alpha = inFromAngle;
		}
		else
		{
			delta = - (inToAngle - inFromAngle) / (inCoordsCount - 1);
			alpha = inToAngle;
		}

		outCoords.resize( (size_t)inCoordsCount);

		for( ArrayOfCoord3D_iter iter = outCoords.begin() ; iter != outCoords.end() ; ++iter )
		{
			(*iter).SetY( 0);

			if (inIsDirectWorld)
			{
				if (inBase == eBaseZoX)
				{
					(*iter).SetZ( inRadius * cos( alpha));
					(*iter).SetX( inRadius * sin( alpha));
				}
				else if (inBase == eBaseXoZ)
				{
					(*iter).SetX( inRadius * cos( alpha));
					(*iter).SetZ( - inRadius * sin( alpha));
				}
				else
				{
					assert(false);
				}
			}
			else
			{
				if (inBase == eBaseXoZ)
				{
					(*iter).SetX( inRadius * cos( alpha));
					(*iter).SetZ( inRadius * sin( alpha));
				}
				else if (inBase == eBaseZoX)
				{
					(*iter).SetZ( inRadius * cos( alpha));
					(*iter).SetX( - inRadius * sin( alpha));
				}
				else
				{
					assert(false);
				}
			}

			alpha += delta;
		}
	}
}


void Math::GetCoordsForArcPerpendicularToZAxis( ArrayOfCoord3D& outCoords, real3 inFromAngle, real3 inToAngle, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection, bool inIsDirectWorld)
{
	assert(inToAngle >= inFromAngle);

	if (inToAngle >= inFromAngle)
	{
		assert(inDirection == eAnticlockwiseRotation || inDirection == eClockwiseRotation);

		if (inDirection != eAnticlockwiseRotation && inDirection != eClockwiseRotation)
			inDirection = eAnticlockwiseRotation;

		real3 delta = 0, alpha = 0;

		if (inDirection == eAnticlockwiseRotation)
		{
			delta = (inToAngle - inFromAngle) / (inCoordsCount - 1);
			alpha = inFromAngle;
		}
		else
		{
			delta = - (inToAngle - inFromAngle) / (inCoordsCount - 1);
			alpha = inToAngle;
		}

		outCoords.resize( (size_t)inCoordsCount);

		for( ArrayOfCoord3D_iter iter = outCoords.begin() ; iter != outCoords.end() ; ++iter )
		{
			(*iter).SetZ( 0);

			if (inIsDirectWorld)
			{
				if (inBase == eBaseXoY)
				{
					(*iter).SetX( inRadius * cos( alpha));
					(*iter).SetY( inRadius * sin( alpha));
				}
				else if (inBase == eBaseYoX)
				{
					(*iter).SetY( inRadius * cos( alpha));
					(*iter).SetX( - inRadius * sin( alpha));
				}
				else
				{
					assert(false);
				}
			}
			else
			{
				if (inBase == eBaseYoX)
				{
					(*iter).SetY( inRadius * cos( alpha));
					(*iter).SetX( inRadius * sin( alpha));
				}
				else if (inBase == eBaseXoY)
				{
					(*iter).SetX( inRadius * cos( alpha));
					(*iter).SetY( - inRadius * sin( alpha));
				}
				else
				{
					assert(false);
				}
			}

			alpha += delta;
		}
	}
}


void Math::GetCoordsForCirclePerpendicularToXAxis( ArrayOfCoord3D& outCoords, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection, bool inIsDirectWorld)
{
	GetCoordsForArcPerpendicularToXAxis( outCoords, 0, 2*kPI - (2*kPI / inCoordsCount), inRadius, inCoordsCount, inBase, inDirection, inIsDirectWorld);
}


void Math::GetCoordsForCirclePerpendicularToYAxis( ArrayOfCoord3D& outCoords, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection, bool inIsDirectWorld)
{
	GetCoordsForArcPerpendicularToYAxis( outCoords, 0, 2*kPI - (2*kPI / inCoordsCount), inRadius, inCoordsCount, inBase, inDirection, inIsDirectWorld);
}


void Math::GetCoordsForCirclePerpendicularToZAxis( ArrayOfCoord3D& outCoords, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection, bool inIsDirectWorld)
{
	GetCoordsForArcPerpendicularToZAxis( outCoords, 0, 2*kPI - (2*kPI / inCoordsCount), inRadius, inCoordsCount, inBase, inDirection, inIsDirectWorld);
}

void Math::GetCoordsForAstroidArcPerpendicularToXAxis( ArrayOfCoord3D& outCoords, real3 inFromAngle, real3 inToAngle, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection, bool inIsDirectWorld)
{
	assert(inToAngle >= inFromAngle);

	if (inToAngle >= inFromAngle)
	{
		assert(inDirection == eAnticlockwiseRotation || inDirection == eClockwiseRotation);

		if (inDirection != eAnticlockwiseRotation && inDirection != eClockwiseRotation)
			inDirection = eAnticlockwiseRotation;

		real3 delta = 0, alpha = 0;

		if (inDirection == eAnticlockwiseRotation)
		{
			delta = (inToAngle - inFromAngle) / (inCoordsCount - 1);
			alpha = inFromAngle;
		}
		else
		{
			delta = - (inToAngle - inFromAngle) / (inCoordsCount - 1);
			alpha = inToAngle;
		}

		outCoords.resize( (size_t)inCoordsCount);

		for( ArrayOfCoord3D_iter iter = outCoords.begin() ; iter != outCoords.end() ; ++iter )
		{
			(*iter).SetX( 0);
			
			if (inIsDirectWorld)
			{
				if (inBase == eBaseYoZ)
				{
					(*iter).SetY( inRadius * pow(cos( alpha),5));
					(*iter).SetZ( inRadius * pow(sin( alpha),5));
				}
				else if (inBase == eBaseZoY)
				{
					(*iter).SetZ( inRadius * pow(cos( alpha),5));
					(*iter).SetY( inRadius * pow(sin( alpha),5));
				}
				else
				{
					assert(false);
				}
			}
			else
			{
				if (inBase == eBaseZoY)
				{
					(*iter).SetZ( inRadius * pow(cos( alpha),5));
					(*iter).SetY( inRadius * pow(sin( alpha),5));
				}
				else if (inBase == eBaseYoZ)
				{
					(*iter).SetY( inRadius * pow(cos( alpha),5));
					(*iter).SetZ( inRadius * pow(sin( alpha),5));
				}
				else
				{
					assert(false);
				}
			}

			alpha += delta;
		}
	}
}


void Math::TranslateBy( Coord3D& inCoord, real3 inTx, real3 inTy, real3 inTz)
{
	inCoord.SetCoordsBy( inTx, inTy, inTz);
}


void Math::TranslateBy( ArrayOfCoord3D& inCoords, real3 inTx, real3 inTy, real3 inTz)
{
    for (ArrayOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter )
    {
        (*iter).SetCoordsBy( inTx, inTy, inTz);
    }
}


void Math::TranslateBy( Coord3D& inCoord, const Vector3D& inVector)
{
	inCoord.SetCoordsBy( inVector.GetVx(), inVector.GetVy(), inVector.GetVz());
}


void Math::TranslateBy( ArrayOfCoord3D& inCoords, const Vector3D& inVector)
{
    for (ArrayOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter )
    {
        (*iter).SetCoordsBy( inVector.GetVx(), inVector.GetVy(), inVector.GetVz());
    }
}



ulong3 Math::GetCoordsCountPerCircle( ulong3 inPrecision)
{
    ulong3 count = 0;

    switch (inPrecision)
    {
    case kLow:
        count = 12;
        break;

	case kDefault:
    case kMedium:
        count = 24;
        break;

    case kHigh:
		count = 36;
        break;

	default:
        count = inPrecision;
        break;
    }
    return count;
}


void Math::GetCircleCoords( ArrayOfCoord2D& outCoords, real3 inDiameter, ulong3 inPrecision)
{
    ulong3 count = GetCoordsCountPerCircle( inPrecision);
    real3 delta = 2 * kPI / count, alpha = 0;

    outCoords.resize( (size_t)count);
    for( ArrayOfCoord2D_iter iter = outCoords.begin() ; iter != outCoords.end() ; ++iter )
    {
        (*iter).SetX( inDiameter * cos( alpha));
        (*iter).SetY( inDiameter * sin( alpha));
        alpha += delta;
    }
}


void Math::GetArcCoords( real3 inFromAngle, real3 inToAngle, ArrayOfCoord2D& outCoords, real3 inDiameter)
{
    assert(inFromAngle > 0 && inToAngle > 0);
    real3 delta = 0, alpha = 0;

    if (inToAngle > inFromAngle)
    {
        delta = (inToAngle - inFromAngle) / (outCoords.size() - 1);
        alpha = inFromAngle;
    }
    else if(inFromAngle > inToAngle)
    {
        delta = -( 360 - inFromAngle + inToAngle) / (outCoords.size() - 1);
        alpha = inFromAngle;
    }

    for( ArrayOfCoord2D_iter iter = outCoords.begin() ; iter != outCoords.end() ; ++iter )
    {
        (*iter).SetX( inDiameter * cos( DegreeToRadian(alpha)));
        (*iter).SetY( inDiameter * sin( DegreeToRadian(alpha)));
        alpha += delta;
    }
}


bool Math::GetBarycentre( const ArrayOfCoord3D& inCoords, Coord3D& outBarycentre)
{
    // le centre de gravite n'est autre que le barycentre du polygon dans lequel tous les poids valent 1
    bool result = false;

    if (inCoords.size() >= 2)
    {
        size_t count = inCoords.size();
        real3 total_x = 0, total_y = 0, total_z = 0;

        for( size_t pos = 0 ; pos < count ; ++pos )
        {
            total_x += inCoords[pos].GetX();
            total_y += inCoords[pos].GetY();
            total_z += inCoords[pos].GetZ();
        }

        outBarycentre.SetX( total_x / count);
        outBarycentre.SetY( total_y / count);
        outBarycentre.SetZ( total_z / count);

		result = true;

    }
    return result;
}


void Math::RotateTo( Coord2D& inCoord, real3 inAngle)
{
    real3 rayon = sqrt( pow( inCoord.GetX(), 2) + pow( inCoord.GetY(), 2));
    inCoord.SetX( rayon * cos( inAngle));
    inCoord.SetY( rayon * sin( inAngle));
}


void Math::RotateBy( Coord2D& inCoord, real3 inAngle)
{
    real3 rayon = sqrt( pow( inCoord.GetY(), 2) + pow( inCoord.GetX(), 2));
    real3 angle = ArcTan( inCoord.GetX(), inCoord.GetY()) + inAngle;
    inCoord.SetX( rayon * cos( angle));
    inCoord.SetY( rayon * sin( angle));
}


void Math::RotateTo( Coord3D& inCoord, real3 *inRx, real3 *inRy, real3 *inRz)
{
    real3 rayon = 0;
    real3 x = inCoord.GetX();
    real3 y = inCoord.GetY();
    real3 z = inCoord.GetZ();

    if (inRx != NULL)
    {
        // rotation autour de l'axe x
        rayon = sqrt( pow( y, 2) + pow( z, 2));
        y = rayon * cos( *inRx);
        z = rayon * sin( *inRx);
    }

    if (inRy != NULL)
    {
        // rotation autour de l'axe y
        rayon = sqrt( pow( x, 2) + pow( z, 2));
        x = rayon * sin( *inRy);
        z = rayon * cos( *inRy);
    }

    if (inRz != NULL)
    {
        // rotation autour de l'axe z
        rayon = sqrt( pow( x, 2) + pow( y, 2));
        x = rayon * cos( *inRz);
        y = rayon * sin( *inRz);
    }

    inCoord.SetCoordsTo( x, y, z);
}


void Math::RotateTo( ArrayOfCoord3D& inCoords, real3 *inRx, real3 *inRy, real3 *inRz)
{
    for ( ArrayOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter )
    {
        RotateTo( *iter, inRx, inRy, inRz);
    }
}


void Math::RotateTo( ArrayPtrOfCoord3D& inCoords, real3 *inRx, real3 *inRy, real3 *inRz)
{
    for ( ArrayPtrOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter )
    {
        Coord3D *coord = *iter;
        if (coord != NULL)
            RotateTo( *coord, inRx, inRy, inRz);
    }
}


void Math::SetPosBy( ArrayOfCoord3D& inCoords, real3 inTx, real3 inTy, real3 inTz)
{
    for ( ArrayOfCoord3D_iter iter = inCoords.begin() ; iter != inCoords.end() ; ++iter )
    {
        (*iter).SetCoordsBy( inTx, inTy, inTz);
    }
}


} // namespace KHEOPS