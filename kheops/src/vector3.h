
#ifndef __VECTOR3__
#define __VECTOR3__



namespace KHEOPS
{



class Vector3D
{
public:

    Vector3D();
    Vector3D( real3 inVx, real3 inVy, real3 inVz);
	Vector3D( const Coord3D& inCoord);
	Vector3D( const Coord3D& inFrom, const Coord3D& inTo);
    Vector3D( const Vector3D& inVector);
    virtual ~Vector3D();

			void            SetVx( real3 inVx)  { fVx = inVx; }
			void            SetVy( real3 inVy)  { fVy = inVy; }
			void            SetVz( real3 inVz)  { fVz = inVz; }

			void			SetCoordsTo( real3 inVx, real3 inVy, real3 inVz)	{ fVx = inVx; fVy = inVy; fVz = inVz; }

			Coord3D			GetCoords() const	{ return Coord3D( fVx, fVy, fVz); }

			real3&          GetVx()             { return fVx; }
			real3&          GetVy()             { return fVy; }
			real3&          GetVz()             { return fVz; }

			const real3&	GetVx() const		{ return fVx; }
			const real3&	GetVy() const		{ return fVy; }
			const real3&	GetVz() const		{ return fVz; }

			bool			IsNull() const;

			void			Normalize();

            Vector3D&       operator=( const Vector3D& inVector);
            Vector3D&       operator+( const Vector3D& inVector);
            Vector3D&       operator-( const Vector3D& inVector);
			Vector3D&       operator*( const real3& inValue);
            // produit scalaire avec le vecteur inVector
            real3           operator*( const Vector3D& inVector) const;
            // produit vectoriel avec le vecteur inVector (dans un repere direct)
            const Vector3D  operator^( const Vector3D& inVector) const;

	static	const Vector3D  CalcCrossProduct( const Vector3D& inFirst,  const Vector3D& inSecond, bool inIsDirectWorld);

            // retourne la norme du vecteur
            real3           GetModule() const;
			void			SetModule( real3 inModule);

	static	Vector3D		sNullVector;

protected:

            real3           fVx;
            real3           fVy;
            real3           fVz;
};



typedef std::vector<Vector3D>                        ArrayOfVector3D;
typedef std::vector<Vector3D>::iterator              ArrayOfVector3D_iter;
typedef std::vector<Vector3D>::const_iterator        ArrayOfVector3D_citer;



} // namespace KHEOPS



#endif