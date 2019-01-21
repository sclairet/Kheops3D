
#ifndef __MATH3__
#define __MATH3__



namespace KHEOPS
{



class Math
{
public:
			// polar coords utilities
	static	void		GetPolarCoordsFromXAxis( const Coord3D& inCoord, PolarCoord& outCoord, EBase inBase, EArgumentInterval inInterval = eInterval_mPI_PI, bool inIsDirectWorld = false);
	static	void		GetPolarCoordsFromYAxis( const Coord3D& inCoord, PolarCoord& outCoord, EBase inBase, EArgumentInterval inInterval = eInterval_mPI_PI, bool inIsDirectWorld = false);
	static	void		GetPolarCoordsFromZAxis( const Coord3D& inCoord, PolarCoord& outCoord, EBase inBase, EArgumentInterval inInterval = eInterval_mPI_PI, bool inIsDirectWorld = false);
    static  void        GetPolarCoord( real3 inX, real3 inY, real3& outModule, real3& outArgument, EArgumentInterval inInterval = eInterval_mPI_PI);

			// cartesian coords utilities
	static	void		GetCartesianCoord( Coord3D& outCoord, const PolarCoord& inCoord, EBase inBase, bool inIsDirectWorld = false);
	static	void		GetCartesianCoord( const PolarCoord& inCoord, real3& outX, real3& outY);
    static  void        GetCartesianCoord( real3 inModule, real3 inArgument, real3& outX, real3& outY);

			// basic utilities
	static  real3       DegreeToRadian( real3 inDegree);
    static  real3       RadianToDegree( real3 inRadian);

    static  real3       ArcTan( real3 inX, real3 inY, EArgumentInterval inInterval = eInterval_mPI_PI);

            // rotation utilities
    static  void        RotateBy( Coord3D& inCoord, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld = false);
    static  void        RotateBy( ArrayOfCoord3D& inCoords, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld = false);
    static  void        RotateBy( ArrayPtrOfCoord3D& inCoords, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld = false);
	static  void        RotateBy( Vector3D& inVector, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld = false);
	static  void        RotateBy( ArrayOfVector3D& inVectors, real3 inRx, real3 inRy, real3 inRz, bool inIsDirectWorld = false);

			// translation utilities
	static	void		TranslateBy( Coord3D& inCoord, real3 inTx, real3 inTy, real3 inTz);
	static	void		TranslateBy( ArrayOfCoord3D& inCoords, real3 inTx, real3 inTy, real3 inTz);
	static	void		TranslateBy( Coord3D& inCoord, const Vector3D& inVector);
	static	void		TranslateBy( ArrayOfCoord3D& inCoords, const Vector3D& inVector);

		     // object building utilities

			/*	returns the coordinnates for a circle arc. inFromAngle and in inToAngle are in [0 , 2Pi[ interval.
				inFromAngle must be smaller than inToAngle
			*/
	static	void		GetCoordsForArcPerpendicularToXAxis( ArrayOfCoord3D& outCoords, real3 inFromAngle, real3 inToAngle, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection = eAnticlockwiseRotation, bool inIsDirectWorld = false);
	static	void		GetCoordsForArcPerpendicularToYAxis( ArrayOfCoord3D& outCoords, real3 inFromAngle, real3 inToAngle, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection = eAnticlockwiseRotation, bool inIsDirectWorld = false);
	static	void		GetCoordsForArcPerpendicularToZAxis( ArrayOfCoord3D& outCoords, real3 inFromAngle, real3 inToAngle, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection = eAnticlockwiseRotation, bool inIsDirectWorld = false);

			/*	returns the coordinnates for a circle
			*/
	static	void		GetCoordsForCirclePerpendicularToXAxis( ArrayOfCoord3D& outCoords, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection = eAnticlockwiseRotation, bool inIsDirectWorld = false);
	static	void		GetCoordsForCirclePerpendicularToYAxis( ArrayOfCoord3D& outCoords, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection = eAnticlockwiseRotation, bool inIsDirectWorld = false);
	static	void		GetCoordsForCirclePerpendicularToZAxis( ArrayOfCoord3D& outCoords, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection = eAnticlockwiseRotation, bool inIsDirectWorld = false);

	static	void		GetCoordsForAstroidArcPerpendicularToXAxis( ArrayOfCoord3D& outCoords, real3 inFromAngle, real3 inToAngle, real3 inRadius, ulong3 inCoordsCount, EBase inBase, ERotationDirection inDirection = eAnticlockwiseRotation, bool inIsDirectWorld = false);

    static  ulong3      GetCoordsCountPerCircle( ulong3 inPrecision);
    static  void        GetCircleCoords( ArrayOfCoord2D& outCoords, real3 inDiameter, ulong3 inPrecision = kDefault);

			// the precision is calculated according to the coords array size
    static  void        GetArcCoords( real3 inFromAngle, real3 inToAngle, ArrayOfCoord2D& outCoords, real3 inDiameter);

	static	bool		GetBarycentre( const ArrayOfCoord3D& inCoords, Coord3D& outBarycentre);

            // rotation utilities
    static  void        RotateTo( Coord2D& inCoord, real3 inAngle);

    static  void        RotateBy( Coord2D& inCoord, real3 inAngle);

    static  void        RotateTo( Coord3D& inCoord, real3 *inRx, real3 *inRy, real3 *inRz);
    static  void        RotateTo( ArrayOfCoord3D& inCoords, real3 *inRx, real3 *inRy, real3 *inRz);
    static  void        RotateTo( ArrayPtrOfCoord3D& inCoords, real3 *inRx, real3 *inRy, real3 *inRz);

	static	void		SetPosBy( ArrayOfCoord3D& inCoords, real3 inTx, real3 inTy, real3 inTz);
};



} // namespace KHEOPS



#endif
