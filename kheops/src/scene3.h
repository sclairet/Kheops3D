
// 22/02/2008

#ifndef __SCENE3__
#define __SCENE3__



namespace KHEOPS
{



// ============================================================================
// needed declarations
class Object3D_container;
class GraphicContext;
class Scene3D;
class Renderer3D;



// ============================================================================







// ============================================================================



class Scene3D
{
public:

    Scene3D();
    Scene3D( Scene3D *inParent);
    virtual ~Scene3D();

            // returns never NULL
            Object3D*			            GetRootObject();
            const Object3D*					GetRootObject() const;

			// camera handling

            Camera*                         CreateCamera( const Coord3D& inPos);
			void							RemoveCamera( Camera *inCamera);

			bool							RegisterCamera( Camera *inCamera);
			bool							UnregisterCamera( Camera *inCamera);
			Camera*							GetCamera( slong3 inID);

			// light handling
			
			Light*							CreateLight( const Coord3D& inPos);
			void							RemoveLight( Light *inLight);

			bool							RegisterLight( Light *inLight);
			bool							UnregisterLight( Light *inLight);
			Light*							GetLight( slong3 inID);
			void							GetLightCollection( std::vector<Light*>& outLights) const;

			// objects handling

			bool							RegisterObject( Object3D *inObject);
			bool							UnregisterObject( Object3D *inObject);
			Object3D*						GetObjectByID( ulong3 inID) const;

			void							SetObjectLighted( const Light& inLight, const Object3D *inObject, bool inLighted);
			bool							IsObjectLighted( const Light& inLight, const Object3D *inObject) const;

            void                            BeginEdition();
            void                            EndEdition();

			void                            SetDrawingSettings( ulong3 inDrawingSettings);
            ulong3                          GetDrawingSettings() const;

            void                            UpdateViewCoords();
            void                            UpdateViewCoords( Camera *inCamera);

			void							UpdateLightness();
			void                            UpdateLightness( Light *inLight);

            void                            Draw( GraphicContext *inContext);
            void                            Draw( GraphicContext *inContext, Camera *inCamera);
            void                            Draw( Renderer3D *inRenderer, Camera *inCamera);

protected:

            Scene3D*                        fParent;
            ulong3                          fInEdition;
            ulong3                          fDrawingMode;
			ulong3							fDrawingSettings;

    mutable Object3D			            *fContainer;

            MapPtrOfCamera                  fCameras;
			ulong3							fNextCameraID;

			MapPtrOfLight					fLights;
			ulong3							fNextLightID;
			std::map< slong3, std::vector<const Object3D*> >	fUnlightedObjects;

			MapOfObject3D					fObjects;
			ulong3							fNextObjectID;
};



// ============================================================================



} // namespace KHEOPS



#endif // __SCENE3__
