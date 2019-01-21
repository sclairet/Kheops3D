
// 07/02/2008


#ifndef __OBJECTS3__
#define __OBJECTS3__




namespace KHEOPS
{



// ============================================================================
// needed declarations
class Object3D;
class Camera;
class ScreenWorld;
class Scene3D;
class Modeler3D;
class Object3D_behaviour;



// ============================================================================
// 3d object container

typedef std::map< ulong3, Object3D* >                    MapOfObject3D;
typedef std::map< ulong3, Object3D* >::iterator          MapOfObject3D_iter;
typedef std::map< ulong3, Object3D* >::const_iterator    MapOfObject3D_citer;

typedef std::map< slong3, ArrayOfCoord3D* >						MapOfCameraCoords;
typedef std::map< slong3, ArrayOfCoord3D* >::iterator			MapOfCameraCoords_iter;
typedef std::map< slong3, ArrayOfCoord3D* >::const_iterator		MapOfCameraCoords_citer;

typedef std::map< slong3, ArrayOfCoord2D* >						MapOfScreenCoords;
typedef std::map< slong3, ArrayOfCoord2D* >::iterator			MapOfScreenCoords_iter;
typedef std::map< slong3, ArrayOfCoord2D* >::const_iterator		MapOfScreenCoords_citer;

typedef std::vector<Object3D*>                     ArrayPtrOfObject3D;
typedef std::vector<Object3D*>::iterator           ArrayPtrOfObject3D_iter;
typedef std::vector<Object3D*>::const_iterator     ArrayPtrOfObject3D_citer;


// ============================================================================
// 3d objects base class declaration


class Object3D
{
public:

	friend class Modeler3D;
	friend class Object3D_behaviour;

    Object3D();
	Object3D( Object3D_behaviour *inBehaviour);
    virtual ~Object3D();

				void						SetID( ulong3 inID);
				ulong3						GetID() const;

				Object3D*					GetParent()	const								{ return fParent; }

    virtual     void                        SetVisible( bool inVisible);
                bool                        IsVisible() const;

				void                        SetColor( const Color& inColor);
				void						SetColor( EColoringPattern inPattern, const Color& inFirstColor, const Color &inSecondColor);
                const Color*                GetColor() const                                { return fColor; }

				const Object3D_behaviour*	GetBehaviour() const							{ return fBehaviour; }
				Object3D_behaviour*			GetBehaviour()									{ return fBehaviour; }

				ulong3						GetCoordsCount() const;
				ulong3						GetShapesCount() const;

                // moving and rotate
    virtual      void                       SetPosTo( const Coord3D& inCoord)               { SetPosTo( inCoord.GetX(), inCoord.GetY(), inCoord.GetZ()); }
    virtual      void                       SetPosTo( real3 inX, real3 inY, real3 inZ);

    virtual      void                       SetPosBy( real3 inTx, real3 inTy, real3 inTz);

				const Coord3D&              GetPos() const { return fPos; }
				
				void						GetCenter( Coord3D& outCenter) const;

    virtual     void                        RotateBy( const World3D& inCenter, const Rotation3D& inRotation)                { RotateBy( inCenter, inRotation.GetRx(), inRotation.GetRy(), inRotation.GetRz()); }
    virtual     void                        RotateBy( const World3D& inCenter, real3 inRx, real3 inRy, real3 inRz);

                // cameras handling
	virtual		void						SynchronizeWithCamera( const Camera& inCamera);
    virtual     bool                        HasCameraCoords( const Camera& inCamera) const;
	virtual     const ArrayOfCoord3D*		GetCameraCoords( const Camera& inCamera) const;

				// lights handling
	virtual		void						SynchronizeWithLight( const Light& inLight);

                // drawing handling
    virtual     bool                        HasScreenCoords( const Camera& inCamera) const;
	virtual     const ArrayOfCoord2D*		GetScreenCoords( const Camera& inCamera) const;

                // rendering utilities methods
                // GetSegments() extract the segments from the object shapes, each segment of returned array is unique
    virtual     void                        GetSegments( ArrayOfSegment& outSegments, const Camera& inCamera) const;
    virtual     const ArrayPtrOfShape3D&    GetShapes() const           { return fShapes; }

				// Children utilities
				void						AddChild( Object3D *inObject);
				ulong3						GetChildrenCount() const;
				const Object3D*				GetNthChild( ulong3 inNth) const;
				Object3D*					GetNthChild( ulong3 inNth);
				void						RemoveChild( Object3D *inObject);
				void						RemoveNthChild( ulong3 inNth);


    virtual     const ArrayPtrOfObject3D&	GetChildren() const        { return fChildren; }

				// Private utilities for modeler
				ArrayOfCoord3D&				_coords()					{ return fCoords; }
				ArrayPtrOfShape3D&			_shapes()					{ return fShapes; }

protected:
				void						_SetParent( Object3D *inParent);

                ulong3						fID;
				bool                        fVisible;
                Color                       *fColor;
                long                        fStamp;
				Object3D_behaviour			*fBehaviour;

                Coord3D                     fPos;
                ArrayOfCoord3D				fCoords;            // 3D coordinates in parent world
                Object3D                    *fParent;
                ArrayPtrOfObject3D			fChildren;

                World3D                     *fWorld;            // parent world

                ArrayPtrOfShape3D           fShapes;            // filled shapes
	mutable		ArrayOfSegment				fSegments;			// shapes segments cache

				MapOfCameraCoords			fCameraCoords;
				MapOfScreenCoords			fScreenCoords;
};



} // namespace KHEOPS



#endif // __OBJECTS3__
