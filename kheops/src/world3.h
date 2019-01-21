
#ifndef __WORLD3__
#define __WORLD3__



namespace KHEOPS
{


class World2D
{
public:

    World2D();
    World2D( const World2D* inParent, const Coord2D& inPos);
    World2D( const World2D& inSource);
    virtual ~World2D();

    virtual void                SetPos( const Coord2D& inPos)   { fPos = inPos; }
			const Coord2D&      GetPos() const                  { return fPos; }
			const World2D*      GetParent() const               { return fParent; }

            // Transform() transform the coord from this world into the target world inWorld
            void                Transform( Coord2D& inCoord, const World2D& inWorld) const;
            void                Transform( ArrayOfCoord2D& inCoords, const World2D& inWorld) const;

    static  World2D             sRootWorld2D;

protected:

            Coord2D             fPos;       // this world position in parent world coords
            World2D             *fParent;
};



// ============================================================================



class Axis3D
{
public:
	Axis3D();
	Axis3D( const Vector3D& inVector);
	Axis3D( const Coord3D& inFirstCoord, const Coord3D& inSecondCoord);
	virtual ~Axis3D();

			Vector3D&			GetVector()				{ return fVector; }
			const Vector3D		GetVector() const		{ return fVector; }

	static	Axis3D		sXAxis;
	static	Axis3D		sYAxis;
	static	Axis3D		sZAxis;

private:
			Vector3D	fVector;
};



// ============================================================================



class World3D
{
public:

	World3D();
    World3D( bool inIsDirect);
    World3D( bool inIsDirect, const Coord3D& inPos);
    World3D( const World3D& inSource);
    virtual ~World3D();

    virtual void                SetPos( const Coord3D& inPos)                   { fPos = inPos; }
			const Coord3D&      GetPos() const                                  { return fPos; }

			// Use SetAxisOrientation() to change the orientation of the axis according to the vector.
			// The vector coordinnates are in root world coordss. Pass null vector to remove the axis orientation.
			void				SetAxisOrientation( EAxis inAxis, const Vector3D& inVector);

			// Returns false if none axis is oriented
			bool				GetAxisOrientation( EAxis& outAxis, Vector3D& outVector) const;

			// If an axis is oriented, only this axis rotation can be changed
			void				SetAxisRotation( EAxis inAxis, real3 inRotation);

			real3				GetAxisRotation( EAxis inAxis) const;

			const World3D*      GetParent() const                               { return fParent; }

			bool				IsDirect() const								{ return fIsDirect; }
			bool				SetIsDirect( bool inIsDirect)					{ fIsDirect = inIsDirect; }

            // Transform() transform the coord from this world into the target world inWorld
            void                Transform( Coord3D& inCoord, const World3D& inWorld) const;
            void                Transform( ArrayOfCoord3D& inCoords, const World3D& inWorld) const;
            void                Transform( ArrayPtrOfCoord3D& inCoords, const World3D& inWorld) const;
			
			void                Transform( Vector3D& inVector, const World3D& inWorld) const;
			void                Transform( ArrayOfVector3D& inVectors, const World3D& inWorld) const;

            // to transform the coord inCoord from the world inWorld into this world, result in outCoord
            void                Transform( const Coord3D& inCoord, const World3D& inWorld, Coord3D &outCoord) const;
            void                Transform( const ArrayOfCoord3D& inCoords, const World3D& inWorld, ArrayOfCoord3D& outCoords) const;
			void                Transform( const ArrayPtrOfCoord3D& inCoords, const World3D& inWorld, ArrayOfCoord3D& outCoords) const;
            void                Transform( const ArrayPtrOfCoord3D& inCoords, const World3D& inWorld, ArrayPtrOfCoord3D& outCoords) const;

    static  World3D             sRootWorld3D;

protected:

            Coord3D             fPos;       // this world position in root world coords
            World3D             *fParent;	// unused, always NULL
			bool				fIsDirect;

			// Axis orientation
			EAxis				fOrientedAxis;
			Vector3D			fAxisOrientation;	// orientation vector in root world coords

			// Axis rotation
			real3				fXAxisRotation;
			real3				fYAxisRotation;
			real3				fZAxisRotation;
};


} // namespace KHEOPS



#endif
