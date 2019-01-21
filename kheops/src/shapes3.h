// 08/02/2008


#ifndef __SHAPES3__
#define __SHAPES3__


using namespace std;



namespace KHEOPS
{



// ============================================================================
// TBD


// ============================================================================
// class declaration

// Segment
// Shape3D
// Shape3D_triangle
// Shape3D_rect
// Shape3D_circle


// ============================================================================
// typedef declaration

// ArrayOfSegment
// ArrayPtrOfShape3D



// ============================================================================


class Segment
{
public:

    Segment()                                 { fFrom = 0, fTo = 0; }
    Segment( size_t inFrom,size_t inTo)       { fFrom = inFrom; fTo = inTo; }
    Segment( const Segment& inSource)         { fFrom = inSource.fFrom; fTo = inSource.fTo; }
    virtual ~Segment()                        { ; }

			void                SetIndexes( size_t inFrom, size_t inTo) { fFrom = inFrom; fTo = inTo; }

			const size_t&       GetFrom() const             { return fFrom; }
			const size_t&       GetTo() const               { return fTo; }
			void                SetFrom( size_t inFrom)     { fFrom = inFrom; }
			void                SetTo( size_t inTo)         { fTo = inTo; }

            bool                operator<( const Segment& inSource) const;
            bool                operator==( const Segment& inSource) const;
            Segment&            operator=( const Segment& inSource);

    static  Segment             sNullSegment;

protected:
            size_t              fFrom;
            size_t              fTo;
};



// ============================================================================


typedef std::vector<Segment>                    ArrayOfSegment;
typedef std::vector<Segment>::iterator          ArrayOfSegment_iter;
typedef std::vector<Segment>::const_iterator    ArrayOfSegment_citer;


// ============================================================================


class Shape3D;

typedef std::vector<Shape3D*>                    ArrayPtrOfShape3D;
typedef std::vector<Shape3D*> ::iterator         ArrayPtrOfShape3D_iter;
typedef std::vector<Shape3D*> ::const_iterator   ArrayPtrOfShape3D_citer;




class Shape3DLightInfo
{
public:
			Shape3DLightInfo();
			Shape3DLightInfo( const Shape3DLightInfo& inInfo);
	virtual	~Shape3DLightInfo();

			void					SetLightness( const real3& inLightness);
			const real3&			GetLightness() const;
	
			void					SetNormalVector( const Vector3D& inNormalVector);
			const Vector3D&			GetNormalVector() const;

			Shape3DLightInfo&		operator=( const Shape3DLightInfo& inInfo);

private:
			Vector3D				fNormalVector;
			real3					fLightness;
};



class Shape3DCameraInfo
{
public:
			Shape3DCameraInfo();
			Shape3DCameraInfo( const Shape3DCameraInfo& inInfo);
	virtual ~Shape3DCameraInfo();

			void					SetVisible( const bool& inVisible);
			const bool&				IsVisible()  const;

			void					SetNormalVector( const Vector3D& inNormalVector);
			const Vector3D&			GetNormalVector() const;
				
			Shape3DCameraInfo&		operator=( const Shape3DCameraInfo& inInfo);

private:
			Vector3D				fNormalVector;
			bool					fVisible;
};



typedef std::map< slong3, Shape3DCameraInfo >					MapOfCameraInfo;
typedef std::map< slong3, Shape3DCameraInfo >::iterator			MapOfCameraInfo_iter;
typedef std::map< slong3, Shape3DCameraInfo >::const_iterator	MapOfCameraInfo_citer;

typedef std::map< slong3, Shape3DLightInfo >					MapOfLightInfo;
typedef std::map< slong3, Shape3DLightInfo >::iterator			MapOfLightInfo_iter;
typedef std::map< slong3, Shape3DLightInfo >::const_iterator	MapOfLightInfo_citer;



// ============================================================================
// 3d shape classes declaration



typedef std::vector<size_t>                    ArrayOfIndex;
typedef std::vector<size_t>::iterator          ArrayOfIndex_iter;
typedef std::vector<size_t>::const_iterator    ArrayOfIndex_citer;


class Shape3D
{
public:

    Shape3D();
	Shape3D( const ArrayOfIndex& inIndexes);
    virtual ~Shape3D();

    virtual void                    SetVisible( bool inVisible)         { fVisible = inVisible; }
			bool                    IsVisible() const                   { return fVisible; }

            void                    SetColor( const Color& inColor);
			const Color*            GetColor() const                    { return fColor; }

			const vector<size_t>&   GetIndexes() const                  { return fIndexes; }

    virtual void                    GetSegments( ArrayOfSegment& outSegments) const;

			void					SetNormalVector( const Vector3D&  inNormalVector);
			const Vector3D&			GetNormalVector() const;

			// cameras handling
			void					SetNormalVectorByCamera( const Camera& inCamera, const Vector3D&  inNormalVector);
			bool					GetNormalVectorByCamera( const Camera& inCamera, Vector3D& outNormalVector) const;

			void					SetVisibleByCamera( const Camera& inCamera, bool inVisible);
			bool					IsVisibleByCamera( const Camera& inCamera) const;

			// lights handling
			void					SetNormalVectorByLight( const Light& inLight, const Vector3D&  inNormalVector);
			bool					GetNormalVectorByLight( const Light& inLight, Vector3D& outNormalVector) const;

			void					SetLightnessByLight( const Light& inLight, real3 inLightness);
			bool					GetLightnessByLight( const Light& inLight, real3& outLightness) const;

                                    // retourne le vecteur normal du polygon
	virtual	bool					GetNormalVector( const ArrayOfCoord3D& inCoords, Vector3D& outVector) const;
    virtual const Vector3D          GetNormalVector( const ArrayPtrOfCoord3D& inCoords) const;

									// retourne le point correspondant au centre de gravite du polygon
	virtual bool					GetGravityCenter( const ArrayOfCoord3D& inCoords, Coord3D& outCoord) const;
	virtual const Coord3D           GetGravityCenter( const ArrayPtrOfCoord3D& inCoords) const;

			// Factories
	static	Shape3D*				Create( const ArrayOfIndex& inIndexes, Vector3D *inNormal = NULL);
	static	Shape3D*				CreateTriangle( size_t inTop, size_t inLeft, size_t inRight, Vector3D *inNormal = NULL);
	static	Shape3D*				CreateRect( size_t inTopRight, size_t inTopLeft, size_t inBottomLeft, size_t inBottomRight, Vector3D *inNormal = NULL);
	static	Shape3D*				CreateCircle( size_t inFromCoord, ulong3 inCoordsCount, Vector3D *inNormal = NULL);

            // returns an array which contains all the rectangular shapes between the two shapes
            // the two shapes MUST have the same number of lines
    static  bool                    GetRectangularShapes( const Shape3D& inFrom,  const Shape3D& inTo, ArrayPtrOfShape3D& outShapes);

            // returns an array which contains all the triangular shapes between the coord inFrom and the shape
    static  bool                    GetTriangulareShapes( size_t inFrom, const Shape3D& inTo, ArrayPtrOfShape3D& outShapes);

protected:

            bool						fVisible;
			std::vector<size_t>			fIndexes;
            Color						*fColor;
			Vector3D					fNormalVector;
			MapOfCameraInfo				fCameraInfos;
			MapOfLightInfo				fLightInfos;
};



// ============================================================================
// triangulare shape



class Shape3D_triangle : public Shape3D
{
public:

    Shape3D_triangle( size_t inTop, size_t inLeft, size_t inRight);
    virtual ~Shape3D_triangle();
};



// ============================================================================
// rectangulare shape



class Shape3D_rect : public Shape3D
{
public:

    Shape3D_rect( size_t inTopRight, size_t inTopLeft, size_t inBottomLeft, size_t inBottomRight);
    virtual ~Shape3D_rect();
};



// ============================================================================
// circular shape



class Shape3D_circle : public Shape3D
{
public:

    Shape3D_circle( size_t inFromCoord, ulong3 inCoordsCount);
    virtual ~Shape3D_circle();
};



} // namespace KHEOPS



#endif // __SHAPES3__
