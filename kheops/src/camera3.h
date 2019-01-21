
#ifndef __CAMERA3__
#define __CAMERA3__



namespace KHEOPS
{



class ScreenWorld : public World2D
{
typedef World2D inherited;

public:

    ScreenWorld();
    ScreenWorld( const ScreenWorld& inSource);
    virtual ~ScreenWorld();

			const real3&    GetZ() const                    { return fZ; }

    virtual void            SetPos( const Coord2D& inPos);
    virtual void            SetZ( real3 inZ);
	virtual void            SetScreenPos( slong3 inX, slong3 inY);
    
	virtual void            SetScreenSize( slong3 inWidth, slong3 inHeight);
			void			GetScreenSize( slong3& outWidth, slong3& outHeight) const;

			void			InvertYAxis( bool inSet);
			bool			IsYAxisInverted() const;

            // to transform the coord inCoord from the world inWorld into this world, result in outCoord
            void            Transform( const Coord3D& inCoord, const World3D& inWorld, Coord2D &outCoord) const;
            void            Transform( const ArrayOfCoord3D& inCoords, const World3D& inWorld, ArrayOfCoord2D& outCoords) const;
			void			Transform( const ArrayPtrOfCoord3D& inCoords, const World3D& inWorld, ArrayPtrOfCoord2D& outCoords) const;

			void            Touch()             { ++fStamp; }
			slong3          GetStamp() const    { return fStamp; }

protected:

            real3           fZ;         // z position in camera world
            slong3          fScreenWidth;
            slong3          fScreenHeight;
			slong3			fScreenX;
			slong3			fScreenY;
            slong3          fStamp;
			bool			fInvertYAxis;

};



// ============================================================================



class Camera : public World3D
{
typedef World3D inherited;

public:

	// first camera ID is 1
    Camera( slong3 inID);
    Camera( slong3 inID, const Coord3D& inPos);
    virtual ~Camera();

    virtual void                SetPos( const Coord3D& inPos);

	virtual	void				FocusOnCoord( const Coord3D& inCoord);

			void				SetID( slong3 inID)			{ fID = inID; }
			slong3              GetID() const               { return fID; }

			void                Touch()                     { ++fStamp; }
			slong3              GetStamp() const            { return fStamp; }

			const ScreenWorld&  GetScreenWorld() const      { return fScreenWorld; }
			ScreenWorld&        GetScreenWorld()            { return fScreenWorld; }

protected:

            slong3              fStamp;
            slong3              fID;
            ScreenWorld         fScreenWorld;
};



// ============================================================================



typedef std::map< slong3, Camera* >                    MapPtrOfCamera;
typedef std::map< slong3, Camera* >::iterator          MapPtrOfCamera_iter;
typedef std::map< slong3, Camera* >::const_iterator    MapPtrOfCamera_citer;


} // namespace KHEOPS



#endif
