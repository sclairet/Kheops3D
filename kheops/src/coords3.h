
#ifndef __COORDS3__
#define __COORDS3__



namespace KHEOPS
{



class Coord2D
{
public:

    Coord2D();
    Coord2D( real3 inX, real3 inY);
    Coord2D( const Coord2D& inSource);
    virtual ~Coord2D();

			void            SetX( real3 inX)        { fX = inX; }
			void            SetY( real3 inY)        { fY = inY; }

			const real3&    GetX() const            { return fX; }
			const real3&    GetY() const            { return fY; }

			void            SetCoordsTo( real3 inX, real3 inY)      { fX = inX; fY = inY; }
			void            SetCoordsBy( real3 inTx, real3 inTy)    { fX += inTx; fY += inTy; }

            Coord2D&        operator=(const Coord2D& inSource);
            bool            operator==(const Coord2D& inSource);
            bool            operator!=(const Coord2D& inSource);

    static  Coord2D         sNullCoord2D;

protected:

            real3           fX;
            real3           fY;

};



// ============================================================================


typedef std::vector<Coord2D>                        ArrayOfCoord2D;
typedef std::vector<Coord2D>::iterator              ArrayOfCoord2D_iter;
typedef std::vector<Coord2D>::const_iterator        ArrayOfCoord2D_citer;


typedef std::vector<Coord2D*>                     ArrayPtrOfCoord2D;
typedef std::vector<Coord2D*>::iterator           ArrayPtrOfCoord2D_iter;
typedef std::vector<Coord2D*>::const_iterator     ArrayPtrOfCoord2D_citer;



// ============================================================================



class Coord3D
{
public:

    Coord3D();
    Coord3D( real3 inX, real3 inY, real3 inZ);
    Coord3D( const Coord3D& inSource);
    virtual ~Coord3D();

            void                        SetX( real3 inX);
            void                        SetY( real3 inY);
            void                        SetZ( real3 inZ);

			const real3                 GetX() const        { return fX; }
			const real3                 GetY() const        { return fY; }
			const real3                 GetZ() const        { return fZ; }

            void                        SetCoordsTo( real3 inX, real3 inY, real3 inZ);
            void                        SetCoordsBy( real3 inTx, real3 inTy, real3 inTz);

            Coord3D&                    operator=(const Coord3D& inSource);
            bool                        operator==(const Coord3D& inSource);
            bool                        operator!=(const Coord3D& inSource);
			Coord3D&					operator*( real3 inValue);

    static  Coord3D                     sNullCoord3D;

protected:

            real3                       fX, fY, fZ;
};



// ============================================================================


typedef std::vector<Coord3D>                        ArrayOfCoord3D;
typedef std::vector<Coord3D>::iterator              ArrayOfCoord3D_iter;
typedef std::vector<Coord3D>::const_iterator        ArrayOfCoord3D_citer;

typedef std::vector<Coord3D*>                     ArrayPtrOfCoord3D;
typedef std::vector<Coord3D*>::iterator           ArrayPtrOfCoord3D_iter;
typedef std::vector<Coord3D*>::const_iterator     ArrayPtrOfCoord3D_citer;



// ============================================================================



class PolarCoord
{
public:
	PolarCoord() : fModule(0), fArgument(0) {;}
	PolarCoord( real3 inModule, real3 inArgument) : fModule(inModule), fArgument(inArgument) {;}
	virtual	~PolarCoord() {;}

			real3	fModule;
			real3	fArgument;
};



} // namespace KHEOPS






#endif
