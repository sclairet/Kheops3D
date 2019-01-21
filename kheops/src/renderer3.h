
#ifndef __RENDERER3__
#define __RENDERER3__



namespace KHEOPS
{


class Object3D;
class Scene3D;
class Camera;
class GraphicContext;



// ============================================================================



class RendererShape
{
public:
			RendererShape( const Object3D *inObject, const Shape3D *inShape, const Camera *inCamera);
	virtual	~RendererShape();

			const Object3D*		GetObject() const		{ return fObject; }
			const Shape3D*		GetShape() const		{ return fShape; }
	
			real3				GetMaxZCoord();

private:
			const Object3D						*fObject;
			const Shape3D						*fShape;
			const Camera						*fCamera;
			const ArrayOfCoord3D				*fCoords;
			real3								fMaxZCoord;
			bool								fMaxZCoordIsDirty;
};



typedef std::vector<RendererShape*>                        ArrayPtrOfRendererShape;
typedef std::vector<RendererShape*>::iterator              ArrayPtrOfRendererShape_iter;
typedef std::vector<RendererShape*>::const_iterator        ArrayPtrOfRendererShape_citer;



// ============================================================================
// class Renderer3D



class Renderer3D
{
public:

    Renderer3D( Scene3D *inScene, GraphicContext *inContext);
    virtual ~Renderer3D();


            void            DrawObjectSegments( const Object3D *inObject, Camera *inCamera) const;
            void            DrawShapesNormalVector( const Object3D *inObject, Camera *inCamera, bool inOnlyVisibleShape) const;
			void			DrawRootWorld( Camera *inCamera) const;

            void            DrawObjectPolygons( const Object3D *inObject, Camera *inCamera) const;

private:

            void            _DrawSegment( const Coord3D& inFrom, const Coord3D& inTo, const Color& inColor, Camera *inCamera) const;

            void            _DrawObjectPolygons( const Object3D *inObject, Camera *inCamera) const;
			void            _DrawFilledShape( const Shape3D *inShape, const Object3D *inObject, Camera *inCamera) const;

			void			_GetObjectRendererShapes( ArrayPtrOfRendererShape& outRendererShapes, const Object3D *inObject, const Camera *inCamera) const;

            Scene3D         *fScene;
            GraphicContext  *fContext;
};



} // namespace KHEOPS



#endif
